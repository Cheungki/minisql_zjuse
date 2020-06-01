

#ifndef CODE_CALLAPI_H
#define CODE_CALLAPI_H
#include<iostream>
#include<string>
#include<vector>
#include"../StringProcessor/StringProcessor.h"
using namespace std;

class callAPI {
public:
    static bool callDeleteAPI(const string& table, const string& condition){

    }

    static bool callDropTableAPI(const string& table){

    }
    static bool callDropIndexAPI(const string& index){

    }
    static bool callCreateTableAPI(const string& table, const string& element){
        //目前还是测试接口有没有通
        cout<<table<<endl;
        cout<<element<<endl;
        return true;
    }
    static bool callCreateIndexAPI(const string& index, const string& table, string& attribute){
        cout<<index<<endl;
        cout<<table<<endl;
        cout<<attribute<<endl;
        return true;
    }
    static bool callInsertAPI(const string& table, string& value){

    }

    static vector<tableValue*>* callSelectAPI(string& table, string& condition){
        stringProcessor::preTrim(table);
        stringProcessor::preTrim(condition);
        cout<<table<<endl;
        cout<<condition<<endl;
        return nullptr;
    }

};


#endif //CODE_CALLAPI_H
