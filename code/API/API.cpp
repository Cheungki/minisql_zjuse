//
// Created by 74096 on 2020/6/1.
//

#include "API.h"

API::API()
{
    buffer = new bufferManager();
    index = new indexManager();
    catalog = new catalogManager();
    record = new recordManager();
}

API::~API()
{
    delete buffer;
    delete index;
    delete catalog;
    delete record;
}

Table* API::getTable(const string &tableName)
{

}

bool API::createTable(const string& tableName, vector<dataType*>* attribution)
{
    return true;
}

bool API::createIndex(const string& indexName, const string& tableName, const string& attribution)
{

}

bool API::dropTable(const string& tableName)
{

}

bool API::dropIndex(const string& indexName)
{

}

bool API::insertValue(const string& tableName, vector<string> valueList)
{

}

int API::deleteValue(const string& tableName, vector<logicCompare>* conditions)
{

}

vector<vector<tableValue>*>* API::select(const string& tableName, vector<logicCompare>* condtions)
{

}

int API::findRecord(const string &tableName, vector<logicCompare> *conditions, vector<vector<tableValue> *> *results, vector<int> *ids)
{

}

void API::writeKey(dataType *attribution, char *key, tableValue v)
{

}