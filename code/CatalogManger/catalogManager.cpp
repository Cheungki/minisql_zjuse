//
// Created by 74096 on 2020/6/1.
//

#include "catalogManager.h"
catalogManager::catalogManager()
{

}

catalogManager::~catalogManager()
{

}

bool catalogManager::catalogCreateTable(const string& tableName, vector<dataType *> *attributions)
{

}

bool catalogManager::catalogCreateIndex(const string& indexName, const string& tableName, const string& columnName)
{

}

bool catalogManager::catalogDropIndex(const string& indexName)
{

}

bool catalogManager::catalogDropIndex(const string& tableName, const string& columnName)
{

}

bool catalogManager::catalogDropTable(const string& tableName)
{

}

bool catalogManager::catalogUpdateTable(Table *table)
{

}

index * catalogManager::getIndex(const string& indexName)
{

}

index * catalogManager::getIndex(const string& tableName, const string& columnName)
{

}

void catalogManager::getIndexbyTable(const string& tableName, vector<index *> *indexVector)
{

}

Table * catalogManager::getTableName(const string& tableName)
{

}
