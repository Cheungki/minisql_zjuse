//
// Created by 74096 on 2020/6/13.
//

#include "callAPI.h"
// 这两个分别调用drop表和索引的API，比较容易写
bool callAPI::callDropTableAPI(const string& tableName){
    return api->dropTable(tableName);
}
bool callAPI::callDropIndexAPI(const string& indexName){
    return api->dropIndex(indexName);
}

bool callAPI::callCreateIndexAPI(const string& index, const string& table, const string& attribute){
    /*
    cout<<index<<endl;
    cout<<table<<endl;
    cout<<attribute<<endl;
    */
    return api->createIndex(index, table, attribute);
}

bool callAPI::callInsertAPI(const string& table, string& value){
    return true;
}

bool callAPI::callCreateTableAPI(const string& table, const string& element){
    //目前还是测试接口有没有通
    cout<<table<<endl;
    cout<<element<<endl;
    return true;
}

vector<tableValue*>* callAPI::callSelectAPI(string& table, string& condition){
    stringProcessor::preTrim(table);
    stringProcessor::preTrim(condition);
    cout<<table<<endl;
    cout<<condition<<endl;
    return nullptr;
}

// 调用delete API的静态成员函数，condition是where后面的全部内容
// 1表示成功，0表示失败，-1表示异常
int callAPI::callDeleteAPI(string& tableName, string& condition){
    //cout<<table<<endl;
    //cout<<condition<<endl;
    // 先去掉空格
    stringProcessor::preTrim(tableName);
    stringProcessor::preTrim(condition);
    cout<<tableName<<endl;
    cout<<condition<<endl;
    // 条件为空则不能删除，返回0表示失败
    if(condition.empty()){
        return 0;
    }
    Table* table = api->getTable(tableName);
    if(table == nullptr)
        return -1;
    vector<dataType*>* attribution = table->tableAttribution;
    auto* logicCondition = new vector<logicCompare>;
    vector<string> singleCondition = stringProcessor::Split(condition, "and");
    logicCompare* t;
    // 关于and进行切分之后再对每一个条件子句进行逻辑分析
    for(auto & i : singleCondition)
    {
        int logicType = stringProcessor::getCompareType(i);
        if(logicType == -1)
            return -1;
        t = stringProcessor::getLogic(i, logicType, attribution);
        if(t == nullptr){
            cout<<"Run time error! Illegal logic expression!"<<endl;
            delete logicCondition;
            return -1;
        }
        logicCondition->push_back(*t);
        delete t;
    }

    return api->deleteValue(tableName, logicCondition);
}