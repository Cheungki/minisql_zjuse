//
// Created by 74096 on 2020/6/1.
//

#ifndef CODE_API_H
#define CODE_API_H

#include<string>
#include<vector>
#include<iostream>
using namespace std;

#include"../BufferManager/bufferManager.h"
#include"../RecordManager/recordManager.h"
#include"../CatalogManager/catalogManager.h"
#include"../IndexManager/indexManager.h"
#include"../GlobalVariable/GlobalVariable.h"
#include"../Table/Table.h"


// 系统调用的API类，集成了buffer manager，index manager，catalog manager和record manager的功能
class API {
public:
    API();
    ~API();
    bool createTable(const string& tableName, vector<dataType*>* attribution);
    bool createIndex(const string& indexName, const string& tableName, const string& attribution);
    bool dropTable(const string& tableName);
    bool dropIndex(const string& indexName);
    bool insertValue(const string& tableName, vector<string> valueList);
    int deleteValue(const string& tableName, vector<logicCompare>* conditions);
    vector<vector<tableValue>*>* select(const string& tableName, vector<logicCompare>* condtions);
    Table* getTable(const string& tableName);
private:
    bufferManager* buffer;
    indexManager* index;
    catalogManager* catalog;
    recordManager* record;

    int findRecord(const string& tableName, vector<logicCompare>* conditions, vector<vector<tableValue>*>* results, vector<int>* ids);
    void writeKey(dataType* attribution, char* key, tableValue v);
};


#endif //CODE_API_H
