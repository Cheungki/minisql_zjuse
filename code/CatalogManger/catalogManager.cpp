//
// Created by 74096 on 2020/6/1.
//
#include<fstream>
#include<iostream>
#include "catalogManager.h"
using namespace std;


set<string> catalogManager::tableNameList;
map<string, index*> catalogManager::indexMap;

catalogManager::catalogManager()
{
    if(tableNameList.empty())
    {
        const string catalogPath = "./tableNameList.db";
        ifstream fin;
        fin.open(catalogPath, ios::in);
        if(fin.fail()){
            cout<<"Run time error! Can't open catalog!"<<endl;
        }
        string table;
        while(fin >> table){
            tableNameList.insert(table);
        }
        fin.close();
    }

    if(indexMap.empty()){
        const string catalogPath = "./indexNameList.db";
        ifstream fin;
        fin.open(catalogPath, ios::in);
        if(!fin.fail()){
            string indexName, tableName, columnName;
            while(fin >> indexName >> tableName >> columnName){
                auto* tmp = new index(indexName, tableName, columnName);
                indexMap[indexName] = tmp;
            }
        }
        else{
            cout<<"Run time error! Can't open index table!"<<endl;
        }
    }
}

bool catalogManager::catalogCreateTable(const string& tableName, vector<dataType *> *attributions)
{
    if(tableNameList.count(tableName) >= 1){
        cout<<"Run time error! The table has already exist."<<endl;
        return false;
    }
    if(attributions->size() > maxAttributionSize){
        cout<<"Run time error! Too many attributions!"<<endl;
        return false;
    }
    int i, primaryCount = 0, length = attributions->size();
    dataType* temp;
    set<string> attributionSet;
    // 检查变量类型是否正确，主键是否为1个和属性的名称是否有重复
    for(i = 0; i < length; i ++){
        temp = (*attributions)[i];
        // 检查变量类型
        int kind = temp->type;
        // 非法的变量类型
        if(kind != miniSQL_INT && kind != miniSQL_FLOAT && kind != miniSQL_CHAR){
            cout<<"Run time error! Illegal data type!"<<endl;
            return false;
        }
        // 字符串长度溢出
        if(kind == miniSQL_CHAR || temp->n > maxCharSize){
            cout<<"Run time error! Char length is too large!"<<endl;
            return false;
        }

        // 检查属性名称是否有重复
        string name = temp->typeName;
        if(attributionSet.count(name) >=1){
            cout<<"Run time error! Duplicate attribution names!"<<endl;
            return false;
        }
        attributionSet.insert(name);
        // 统计主键的个数
        if(temp->isPrimaryKey){
            primaryCount++;
        }
        else if(!temp->isPrimaryKey && temp->hasIndex){
            cout<<"Run time error! Can't create non-primary index!"<<endl;
            return false;
        }
    }
    if(primaryCount < 1){
        cout<<"Run time error! No primary key when create table!"<<endl;
        return false;
    }
    else if(primaryCount >= 2){
        cout<<"Run time error! Too many primary keys when create table!"<<endl;
        return false;
    }
    string path = "./table_" + tableName + ".db";
    tableNameList.insert(tableName);
    ofstream fout;
    fout.open("./tableNameList.db", ios::app);
    fout<<tableName<<endl;
    fout.close();
    fout.open(path, ios::out);
    if(fout.fail()){
        cout<<"Run time error! Fail to open table file!"<<endl;
        return false;
    }
    for(i = 0; i < length ; i++){
        temp = (*attributions)[i];
        fout<<temp->type<<" "<<temp->n<<" "<<temp->typeName<<" "<<temp->isUnique<<" "<<temp->isPrimaryKey<<" "<<temp->hasIndex<<endl;
    }
    fout.close();
    return true;
}

bool catalogManager::catalogCreateIndex(const string& indexName, const string& tableName, const string& columnName)
{

}


// 两种方式删除对应的索引：根据索引名称和表明+列名，两个函数构成重载关系
bool catalogManager::catalogDropIndex(const string& indexName)
{
    if(indexMap.find(indexName) == indexMap.end()){
        cout<<"Run time error! No index with such index name!"<<endl;
        return false;
    }
    Table* table = getTable(indexMap[indexName]->getTableName());
    dataType* attribution = table->searchAttribution(indexMap[indexName]->getColumnName());
    if(!attribution->hasIndex){
        cout<<"Run time error! No index to drop!"<<endl;
        return false;
    }
    attribution->hasIndex = true;
    for(int i = 0; i < table->indexAttribution->size(); i ++){
        if((*table->indexAttribution)[i] == attribution->typeName){
            table->indexAttribution->erase(table->indexAttribution->begin() + i);
            break;
        }
    }
    catalogUpdateTable(table);
    //delete indexMap[indexName];
    indexMap.erase(indexName);
    ofstream fout;
    fout.open("./indexNameList.db", ios::out);
    map<string, index*>::iterator m;
    for(m = indexMap.begin(); m != indexMap.end(); m ++){
        fout<<m->second->getName()<<" "<<m->second->getTableName()<<" "<<m->second->getColumnName()<<endl;
    }
    fout.close();
    return true;
}

// 两种方式删除对应的索引：根据索引名称和表明+列名，两个函数构成重载关系
bool catalogManager::catalogDropIndex(const string& tableName, const string& columnName)
{
    index* temp = getIndex(tableName, columnName);
    if(temp == nullptr){
        cout<<"Run time error! No index in the table column!"<<endl;
        return false;
    }
    else{
        catalogDropIndex(temp->getName());
        delete temp;
        return true;
    }
}

bool catalogManager::catalogDropTable(const string& tableName)
{
    if(tableNameList.count(tableName) <= 0){
        cout<<"Run time error! Table doesn't exist!"<<endl;
        return false;
    }
    else{
        tableNameList.erase(tableName);
        string path = "./table_" + tableName + ".db";
        if(remove(path.c_str()) == EOF){
            cout<<"Run time error! Fail to delete table file!"<<endl;
            return false;
        }
        ofstream fout;
        fout.open(path, ios::out);
        set<string>::iterator m;
        for(m = tableNameList.begin(); m != tableNameList.end(); m++){
            fout<<(*m)<<endl;
        }
        fout.close();
        return true;
    }
}

// 更新一张table数据表中的table信息
bool catalogManager::catalogUpdateTable(Table *table)
{
    string tableName = table->tableName;
    string path = "./table_" + tableName + ".db";
    ofstream fout;
    fout.open(path, ios::out);
    if(fout.fail()){
        cout<<"Run time error! Fail to open the table file!"<<endl;
        return false;
    }
    dataType* tmp;
    //要注意文件中写入的table相关的属性的顺序
    for(int i = 0; i < table->size; i ++){
        tmp = (*(table->tableAttribution))[i];
        fout<<tmp->type<<" "<<tmp->n<<" "<<tmp->typeName<<" "<<tmp->isUnique<<" "<<tmp->isPrimaryKey<<" "<<tmp->hasIndex<<endl;
    }
    fout.close();
    return true;
}

// 根据查找对应的index并将其作为结果返回
index * catalogManager::getIndex(const string& indexName)
{
    if(indexMap.find(indexName) == indexMap.end()){
        cout<<"Run time error! No such index!"<<endl;
        return nullptr;
    }
    return indexMap[indexName];
}

// 根据table和属性名查找对应的index并将其作为结果返回
index * catalogManager::getIndex(const string& tableName, const string& columnName)
{
    map<string, index*>::iterator m;
    for(m = indexMap.begin(); m != indexMap.end(); m++){
        if(m->second->getTableName() == tableName && m->second->getColumnName() == columnName){
            return m->second;
        }
    }
    cout<<"Run time error! No such index!"<<endl;
    return nullptr;
}

// 查找某个table下面所有的index，将信息存储在vector中
void catalogManager::getIndexbyTable(const string& tableName, vector<index*> *indexVector)
{
    map<string, index*>::iterator m;
    for(m = indexMap.begin(); m != indexMap.end(); m++){
        if(m->second->getTableName() == tableName){
            indexVector->push_back(m->second);
        }
    }
}


// 打开catalog中对应的数据表文件，把table的信息作为返回值
Table * catalogManager::getTable(const string& tableName)
{
    if(tableNameList.count(tableName) <= 0){
        cout<<"Run time error! Table doesn't exist!"<<endl;
        return nullptr;
    }
    else{
        string path = "./table_" + tableName + ".db";
        ifstream fin;
        fin.open(path, ios::in);
        if(fin.fail()){
            cout<<"Run time error! Can't open catalog!"<<endl;
            return nullptr;
        }

        //读取数据表文件中记录的数据表的信息
        auto* attribution = new vector<dataType*>;
        auto* index = new vector<string>;
        int type, n, unique, primary, hasIndex;
        string attrName;
        while(fin >> type)
        {
            fin >> n >> attrName >> unique >> primary >> hasIndex;
            auto tmp = new dataType(type, n, attrName, unique, primary, hasIndex);
            attribution->push_back(tmp);
            if(hasIndex == 1){
                index->push_back(attrName);
            }
        }
        fin.close();
        auto* result = new Table(tableName, attribution, index);
        return result;
    }
}
