//
// Created by 74096 on 2020/6/1.
//

#include "recordManager.h"

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

}

bool recordManager::recordDeleteTable(string tableName, vector<int> *list)
{

}

bool recordManager::recordDropTable(string tableName)
{

}

vector<tableValue> * recordManager::recordGetByID(string tableName, int id)
{

}

int recordManager::recordInsertTable(string tableName, vector<tableValue> *value)
{

}

vector<int> recordManager::recordSelectTable(string tableName, vector<logicCompare> *conditions)
{

}

bool recordManager::recordCheck(Table *table, vector<tableValue> *record, vector<logicCompare> *conditions)
{

}

bool recordManager::recordCheckDuplicate(string tableName, vector<tableValue> *record)
{

}