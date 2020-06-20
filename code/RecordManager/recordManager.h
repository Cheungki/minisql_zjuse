//
// Created by 74096 on 2020/6/1.
//

#ifndef CODE_RECORDMANAGER_H
#define CODE_RECORDMANAGER_H
#include<fstream>
#include<vector>
#include<string>
#include<set>
#include"../CatalogManger/catalogManager.h"
#include"../BufferManager/bufferManager.h"

using namespace std;

class recordManager {
public:
    recordManager();
    ~recordManager();
    bool static recordCreateTable(string tableName);
    bool recordDropTable(string tableName);
    bool recordDeleteTable(string tableName, vector<int>* list);
    int recordInsertTable(string tableName, vector<tableValue>* value);
    bool recordCheck(Table* table, vector<tableValue>* record, vector<logicCompare>* conditions);
    bool recordCheckDuplicate(string tableName, vector<tableValue>* record);
    vector<int>* recordSelectTable(string tableName, vector<logicCompare>* conditions);
    vector<tableValue>* recordGetByID(string tableName, int id);
private:
    catalogManager* catalog;
    bufferManager* buffer;
};


#endif //CODE_RECORDMANAGER_H
