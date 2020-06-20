//
// Created by 74096 on 2020/6/1.
//

#include "recordManager.h"
#include "../CatalogManger/fileManager.h"
#include "../Table/tableFile.h"
#include "../GlobalVariable/GlobalVariable.h"


recordManager::recordManager()
{
    catalog = new catalogManager();
    buffer = new bufferManager();
}

recordManager::~recordManager()
{
    delete catalog;
    delete buffer;
}

bool recordManager::recordCreateTable(string tableName)
{
    string filePath = "data/" + tableName + ".mdb";
    if(!fopen(filePath.c_str(), "rb")) {
        FILE* dataFile = fopen(filePath.c_str(), "ab+");
        char* data = new char[blockSize];
        fileManager::writeInt(data, 0);
        fileManager::writeInt(data + 4, 1);
        fileManager::writeInt(data + 8, 0);
        fileManager::writeInt(data + 12, -1);
        fwrite(data, blockSize, 1, dataFile);
        fclose(dataFile);
        delete[] data;
    }
    return true;
}

bool recordManager::recordDeleteTable(string tableName, vector<int> *list)
{

}

bool recordManager::recordDropTable(string tableName)
{
    string filePath = "data/" + tableName + ".mdb";
//    buffer->clearBuffer();
    /* 清除buffer里面的内容。 */
    remove(filePath.c_str());
    return true;
}

vector<tableValue> * recordManager::recordGetByID(string tableName, int id)
{
    /* 需要联动'../Table/tableFile.h'中的函数，目前还不能用。 */
    auto* filename = new tableFile(tableName);
    vector<tableValue>* values = filename->getRecord(id);
    delete filename;
    return values;
}

int recordManager::recordInsertTable(string tableName, vector<tableValue> *value)
{
    auto* filename = new tableFile(tableName);
    int result = filename->recordInsert(value);
    delete filename;
    return result;
}

vector<int>* recordManager::recordSelectTable(string tableName, vector<logicCompare> *conditions)
{
    if(!conditions) conditions = new vector<logicCompare>;
    auto* result = new vector<int>;
    Table* table = catalog->getTable(tableName);
    auto* fileName = new tableFile(tableName);
    int maxID = fileName->getMaxID(), i;
    for(i = 0; i <= maxID; i++) {
        vector<tableValue>* records = fileName->getRecord(i, false);
        if(records) {
            if(recordCheck(table, records, conditions)) result->push_back(i);
        }
        else continue;
    }
    delete table;
    delete fileName;
    return result;
}

bool recordManager::recordCheck(Table *table, vector<tableValue> *record, vector<logicCompare> *conditions)
{

}

bool recordManager::recordCheckDuplicate(string tableName, vector<tableValue> *record)
{

}