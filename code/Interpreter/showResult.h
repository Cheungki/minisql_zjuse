//
// Created by 74096 on 2020/5/29.
//

#ifndef CODE_SHOWRESULT_H
#define CODE_SHOWRESULT_H


class showResult {
public:
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
    static void showDelete(bool flag, const string& table){
        if(flag){
            cout<<"Delete from table "<<table<<" Successfully!"<<endl;
        }
        else{
            cout<<"Deletion failed! Please try again!"<<endl;
        }
    }
    static void showSelect(string table){
        //待完成，这一部分需要和其他地方一起联动，先等等
        //
        //
        //
    }

};


#endif //CODE_SHOWRESULT_H
