//
// Created by 74096 on 2020/6/1.
//
#include<fstream>
#include "catalogManager.h"

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
                index* tmp = new index(indexName, tableName, columnName);
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
