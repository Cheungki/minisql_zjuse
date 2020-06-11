//
// Created by 74096 on 2020/5/29.
//

#ifndef CODE_SHOWRESULT_H
#define CODE_SHOWRESULT_H
#include "../Table/Table.h"
#include"../GlobalVariable/GlobalVariable.h"

class showResult {
public:
    // 一些用来显示结果的static成员函数
    static void showDropTable(bool flag, const string& table){
        if(flag){
            cout<<"Drop Table "<<table<<" Successfully!"<<endl;
        }
        else{
            cout<<"Failed in dropping table "<<table<<". Please try again!"<<endl;
        }
    }
    static void showDropIndex(bool flag, const string& index){
        if(flag){
            cout<<"Drop Index "<<index<<" Successfully!"<<endl;
        }
        else{
            cout<<"Failed in dropping index "<<index<<". Please try again!"<<endl;
        }
    }
    static void showCreateTable(bool flag, const string& table){
        if(flag){
            cout<<"Create Table "<<table<<" Successfully!"<<endl;
        }
        else{
            cout<<"Failed when creating table "<<table<<". Please try again!"<<endl;
        }
    }
    static void showCreateIndex(bool flag, const string& index){
        if(flag){
            cout<<"Create Index on "<<index<<" Successfully!"<<endl;
        }
        else{
            cout<<"Failed when creating table "<<index<<". Please try again!"<<endl;
        }
    }
    static void showInsert(bool flag, const string& table){
        if(flag){
            cout<<"Insert into table "<<table<<" Successfully!"<<endl;
        }
        else{
            cout<<"Insertion failed! Please try again!"<<endl;
        }
    }
    static void showDelete(int flag, const string& table){
        if(flag == 1){
            cout<<"Delete from table "<<table<<" Successfully!"<<endl;
        }
        else if(!flag){
            cout<<"Deletion failed! Please try again!"<<endl;
        }
        else{
            cout<<"Run time error! Table doesn't exist!"<<endl;
        }
    }
    static void showSelect(vector<tableValue*>* result, string table){
        //待完成，需要展示select到的结果
        //经过测试，接口已经调通了
        if(result == nullptr){
            cout<<endl;
            cout<<table<<endl;
        }
        else{
            cout<<"error!"<<endl;
        }
    }

};


#endif //CODE_SHOWRESULT_H
