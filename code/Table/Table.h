//
// Created by 74096 on 2020/5/30.
//

#ifndef CODE_TABLE_H
#define CODE_TABLE_H
#include<iostream>
#include<string>
#include<vector>

#include"../GlobalVariable/GlobalVariable.h"
using namespace std;


struct tableValue{
public:
    int INT;
    float FLOAT;
    char* CHAR;
};

// 表示数据类型的类，成员变量的含义根据变量名很好理解
class dataType{
public:
    int type, n;
    string typeName;
    bool isUnique, isPrimaryKey, hasIndex;
    dataType(int input_type, int input_n, string input_typeName, bool input_isUnique, bool input_isPrimaryKey, bool input_hasIndex);
    //获取数据长度的方法
    int getDataLength();
private:
};

//表示一张表的类
class Table{
public:
    string tableName;
    //这里primaryKey表示对应的主键的属性的下标
    int columnCount, primaryKey, numPerBlock, size;
    vector<dataType*>* tableAttribution;
    vector<string>* indexAttribution;
    Table(string name, vector<dataType*>* attribute, vector<string>* index);
    //这里好像也可以改成引用
    dataType* searchAttribution(const string& name);
    dataType* searchAttribution(const char* name);
    int searchPosition(const string& name);
    int searchPosition(const char* name);
    void dropIndex(const string& indexName);
};


#endif //CODE_TABLE_H
