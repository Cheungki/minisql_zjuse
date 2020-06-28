//
// Created by 74096 on 2020/6/1.
//

#include <sstream>
#include "API.h"

API::API()
{
    buffer = new bufferManager();
    Index = new indexManager();
    catalog = new catalogManager();
    record = new recordManager();
}

API::~API()
{
    delete buffer;
    delete Index;
    delete catalog;
    delete record;
}

Table* API::getTable(const string &tableName)
{
    return catalog->getTable(tableName);
}

bool API::createTable(const string& tableName, vector<dataType*>* attribution)
{
    if(!catalog->catalogCreateTable(tableName, attribution))
        return false;
    if(!record->recordCreateTable(tableName))
        return false;
    for(auto & i : *attribution){
        if(i->isPrimaryKey){
            string indexName = "primary_index_of_" + tableName;
            createIndex(indexName, tableName, i->typeName);
            return true;
        }
    }
    return false;
}

bool API::createIndex(string indexName, string tableName, string attribution)
{
    if(!catalog->catalogCreateIndex(indexName, tableName, attribution))
        return false;
    if(!Index->createIndex(indexName.c_str()))
        return false;
    Table* table = catalog->getTable(tableName);
    int pos = table->searchPosition(attribution);
    dataType* temp = table->tableAttribution->at(pos);
    char* key = new char[temp->getDataLength()];
    vector<int>* ids = record->recordSelectTable(tableName, nullptr);
    int i;
    for(i = 0; i < ids->size(); i++)
    {
        vector<tableValue>* record_value = record->recordGetByID(tableName, ids->at(i));
        writeKey(temp, key, record_value->at(pos));
        Index->insert(indexName.c_str(), key, ids->at(i));
    }
    return true;
}

bool API::dropTable(const string& tableName)
{
    Table *table = getTable(tableName);
    for(const auto& colName: *(table->indexAttribution))
    {
        index* temp = catalog->getIndex(tableName, colName);
        dropIndex(temp->getName());
    }
    if(!catalog->catalogDropIndex(tableName))return false;
    if(!record->recordDropTable(tableName))return false;

    delete table;
    return true;
}

bool API::dropIndex(const string& indexName)
{
    if(!catalog->catalogDropIndex(indexName))
        return false;
    return Index->dropIndex(indexName.c_str());
}

bool API::insertValue(const string& tableName, vector<string> valueList)
{
    Table* table = getTable(tableName);
    if(table == nullptr)
        return false;
    vector<dataType*>* attrList = table->tableAttribution;
    int i;
    for(i = 0; i < valueList.size(); i++){
        if(valueList[i].empty()){
            cout<<"Run time error! Empty Value!"<<endl;
            return false;
        }
    }
    bool allHaveIndex = true;
    for(i = 0; i < table->tableAttribution->size(); i++){
        dataType* attr = (*(table->tableAttribution))[i];
        if(!attr->isPrimaryKey && ! attr->isUnique)
            continue;
        index* temp_index = catalog->getIndex(tableName, attr->typeName);
        if(temp_index == nullptr)
            allHaveIndex = false;
    }
    tableValue x{};
    auto* value = new vector<tableValue>;
    int size = attrList->size();
    if(size != valueList.size()){
        cout<<"Run time error! Values not match"<<endl;
        return false;
    }
    for(i = 0; i < size; i++){
        x.CHAR = nullptr;
        if((*attrList)[i]->type == miniSQL_INT){
            if(!stringProcessor::intCheckAndChange(valueList[i]).first){
                cout<<"Run time error! Value type error!"<<endl;
                return false;
            }
            else{
                stringstream t;
                t<<valueList[i];
                t>>x.INT;
                value->push_back(x);
            }
        }
        else if((*attrList)[i]->type == miniSQL_FLOAT){
            if(!stringProcessor::floatCheckAndChange(valueList[i]).first){
                cout<<"Run time error! Value type error!"<<endl;
                return false;
            }
            else{
                stringstream t;
                t<<valueList[i];
                t>>x.FLOAT;
                value->push_back(x);
            }
        }
        else{
            if(!stringProcessor::charCheckAndChange(valueList[i])){
                cout<<"Run time error! Value type error!"<<endl;
                return false;
            }
            else{
                int maxLen = (*attrList)[i]->n;
                if(valueList[i].size() > maxLen){
                    cout<<"Run time error! Value is longer than the max len!"<<endl;
                }
                x.CHAR = new char[maxLen];
                memcpy(x.CHAR, valueList[i].c_str(), valueList[i].size()+1);
                value->push_back(x);
            }
        }
    }
    bool repeated = true; //是否有重复
    if(allHaveIndex){
        for(i = 0; i < table->tableAttribution->size(); i++){
            dataType* temp = table->tableAttribution->at(i);
            if(!temp->isPrimaryKey && ! temp->isUnique)
                continue;
            index* temp_index = catalog->getIndex(tableName, temp->typeName);
            char* key = new char[temp->getDataLength()];
            writeKey(temp, key, value->at(i));
            int pos = Index->find(temp_index->getName().c_str(), key);
            if(pos >= 0){
                repeated = false;
                break;
            }
        }
    }
    else
        repeated = record->recordCheckDuplicate(tableName, value);
    if(!repeated){
        cout<<"Run time error! Duplicate attibution!"<<endl;
        return false;
    }
    int id = record->recordInsertTable(tableName, value);
    for(i = 0; i < table->tableAttribution->size(); i++){
        dataType* temp = table->tableAttribution->at(i);
        if(!temp->isPrimaryKey && ! temp->isUnique)
            continue;
        index* temp_index = catalog->getIndex(tableName, temp->typeName);
        if(temp_index != nullptr){
            char* key = new char[temp->getDataLength()];
            writeKey(temp, key, value->at(i));
            Index->insert(temp_index->getName().c_str(), key, id);
        }
    }
    char *temp;
    for(i = 0; i < size; i++){
        temp = (*value)[i].CHAR;
        delete temp;
    }
    delete value;
    delete table;
    return id >= 0;
}

int API::deleteValue(const string& tableName, vector<logicCompare>* conditions)
{
    return remove(tableName, conditions);
}

vector<vector<tableValue>*>* API::select(const string& tableName, vector<logicCompare>* condtions)
{
    Table* table = catalog->getTable(tableName);
    if(table == nullptr){
        cout<<"Run time error! There is no table!"<<endl;
        return nullptr;
    }
    for(auto logic: *condtions){
        if(table->searchAttribution(logic.getValueName()) == nullptr){
            cout<<"Run time error! Attribution not found!"<<endl;
            return nullptr;
        }
    }
    auto* result = new vector<vector<tableValue>*>;
    vector<int>* ids = new vector<int>;
    int selectNumber = findRecord(tableName, condtions, result, ids);
    return result;
}

int API::findRecord(const string &tableName, vector<logicCompare> *conditions, vector<vector<tableValue> *> *results, vector<int> *ids)
{
    Table* table = catalog->getTable(tableName);
    for(auto logic: *conditions){
        if(logic.operation != EQUAL)
            continue;
        index* temp_index = catalog->getIndex(tableName, logic.getValueName());
        if(temp_index == nullptr)
            continue;
        dataType* attr = table->searchAttribution(logic.getValueName());
        char* key = new char[attr->getDataLength()];
        if(attr->type == miniSQL_INT)
            fileManager::writeInt(key, logic.getImmediate().INT);
        else if(attr->type == miniSQL_FLOAT)
            fileManager::writeFloat(key, logic.getImmediate().FLOAT);
        else
            fileManager::writeChar(key, logic.getImmediate().CHAR, attr->n);
        if(key == nullptr)
            return 0;
        int id = Index->find(temp_index->getName().c_str(), key), ret;
        if(id < 0)
            ret = 0;
        else{
            vector<tableValue>* val = record->recordGetByID(tableName, id);
            if(record->recordCheck(table, val, conditions)){
                results->push_back(val);
                ids->push_back(id);
                ret = 1;
            }
            else ret = 0;
        }
        return ret;
    }
    auto* t = new vector<int>;
    t = record->recordSelectTable(tableName, conditions);
    for(auto id: *t){
        ids->push_back(id);
        results->push_back(record->recordGetByID(tableName, id));
    }
    return ids->size();
}

void API::writeKey(dataType *attribution, char *key, tableValue v)
{
    if(attribution->type == miniSQL_INT)
        fileManager::writeInt(key, v.INT);
    else if(attribution->type == miniSQL_FLOAT)
        fileManager::writeFloat(key, v.FLOAT);
    else
        fileManager::writeChar(key, v.CHAR, attribution->getDataLength());
}

int API::remove(string tableName, vector<logicCompare> *conditions)
{
    Table* table = getTable(tableName);
    if(table == nullptr){
        cout<<"Run time error! There is no table!"<<endl;
        return 0;
    }
    auto* result = new vector<vector<tableValue>*>;
    auto* ids = new vector<int>;
    int selectNumber = findRecord(tableName, conditions, result, ids);
    for(auto indexCol: *(table->indexAttribution)){
        int pos = table->searchPosition(indexCol);
        dataType* temp = (*(table->tableAttribution))[pos];
        char *key = new char[temp->getDataLength()];
        index* temp_index = catalog->getIndex(table->tableName, indexCol);
        for(auto t: *result){
            writeKey(temp, key, t->at(pos));
            Index->remove(temp_index->getName().c_str(), key);
        }
    }
    record->recordDeleteTable(tableName, ids);
    return selectNumber;
}