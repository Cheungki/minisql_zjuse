//
// Created by 74096 on 2020/6/1.
//

#ifndef CODE_CATALOGMANAGER_H
#define CODE_CATALOGMANAGER_H
#include<string>
#include<map>
#include<set>
#include<vector>
#include<string.h>

#include"../GlobalVariable/GlobalVariable.h"
#include"../Table/Table.h"
#include"../IndexManager/index.h"


using namespace std;

// 日志管理，各个member function的作用根据函数名就可以推测出来，今天晚上跑去吃鸡翅了所以更新的不是很多
class catalogManager {
private:
    static set<string> tableNameList;
    static map<string, index*> indexMap;
public:
    catalogManager();
    //~catalogManager();
    Table* getTable(const string& tableName);
    bool catalogCreateTable(const string& tableName, vector<dataType*>* attributions);
    bool catalogDropTable(const string& tableName);
    bool catalogUpdateTable(Table* table);
    bool catalogDropIndex(const string& indexName);
    bool catalogDropIndex(const string& tableName, const string& columnName);
    bool catalogCreateIndex(string& indexName, string& tableName, string& columnName);
    index* getIndex(const string& indexName);
    index* getIndex(const string& tableName, const string& columnName);
    void getIndexbyTable(const string& tableName, vector<index*>* indexVector);


};


#endif //CODE_CATALOGMANAGER_H
