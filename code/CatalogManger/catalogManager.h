//
// Created by 74096 on 2020/6/1.
//

#ifndef CODE_CATALOGMANAGER_H
#define CODE_CATALOGMANAGER_H
#include<string>
#include<map>
#include<set>
#include<vector>

#include"../GlobalVariable/GlobalVariable.h"
#include"../Table/Table.h"
#include"../IndexManager/index.h"


using namespace std;

class catalogManager {
private:
    static set<string> tableNameList;
    static map<string, index*> indexMap;
public:
    catalogManager();
    ~catalogManager();
    Table* getTableName(const string& tableName);
    bool catalogCreateTable(const string& tableName, vector<dataType*>* attributions);
    bool catalogDropTable(const string& tableName);
    bool catalogUpdateTable(Table* table);
    bool catalogDropIndex(const string& indexName);
    bool catalogDropIndex(const string& tableName, const string& columnName);
    bool catalogCreateIndex(const string& indexName, const string& tableName, const string& columnName);
    index* getIndex(const string& indexName);
    index* getIndex(const string& tableName, const string& columnName);
    void getIndexbyTable(const string& tableName, vector<index*>* indexVector);


};


#endif //CODE_CATALOGMANAGER_H
