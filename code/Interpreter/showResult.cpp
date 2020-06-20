//
// Created by 74096 on 2020/6/15.
//

#include "showResult.h"
void showResult::showDropTable(bool flag, const string& table){
    if(flag){
        cout<<"Drop Table "<<table<<" Successfully!"<<endl;
    }
    else{
        cout<<"Failed in dropping table "<<table<<". Please try again!"<<endl;
    }
}
void showResult::showDropIndex(bool flag, const string& index){
    if(flag){
        cout<<"Drop Index "<<index<<" Successfully!"<<endl;
    }
    else{
        cout<<"Failed in dropping index "<<index<<". Please try again!"<<endl;
    }
}
void showResult::showCreateTable(bool flag, const string& table){
    if(flag){
        cout<<"Create Table "<<table<<" Successfully!"<<endl;
    }
    else{
        cout<<"Failed when creating table "<<table<<". Please try again!"<<endl;
    }
}
void showResult::showCreateIndex(bool flag, const string& index){
    if(flag){
        cout<<"Create Index on "<<index<<" Successfully!"<<endl;
    }
    else{
        cout<<"Failed when creating table "<<index<<". Please try again!"<<endl;
    }
}
void showResult::showInsert(bool flag, const string& table){
    if(flag){
        cout<<"Insert into table "<<table<<" Successfully!"<<endl;
    }
    else{
        cout<<"Insertion failed! Please try again!"<<endl;
    }
}
void showResult::showDelete(int flag, const string& table){
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


void showResult::showSelect(vector<vector<tableValue>*>* result, string tableName){
    //待完成，需要展示select到的结果
    //经过测试，接口已经调通了
    cout<<"---------Selected Results----------"<<endl;
    if(result == nullptr){
        cout<<"No selected result at all!"<<endl;
        return;
    }
    Table* table = api->getTable(tableName);
    vector<dataType*>* attribution = table->tableAttribution;
    vector<tableValue>* tempLine;
    dataType* temp;
    int i, j, len = 0, size = attribution->size();
    /*
    for(i = 0; i < size; i++){
        temp = (*attribution)[i];
        if(temp->type == miniSQL_CHAR)
            len += temp->getDataLength() + 1;
        else
            len += int(temp->typeName.size()) + 10 + 1;
    }
     */
    // 打印第一行属性栏
    for(i = 0; i < size; i++){
        cout<<(*attribution)[i]->typeName;
        if(!i){
            cout<<" | ";
        }
    }
    cout<<endl;
    // 打印后面的每一档
    for(i = 0; i < result->size(); i++)
    {
        tempLine = (*result)[i];
        for(j = 0; j < size; j++)
        {
            temp = (*attribution)[j];
            if(temp->type == miniSQL_INT)
                cout<<(*tempLine)[j].INT;
            else if(temp->type == miniSQL_FLOAT)
                cout<<(*tempLine)[j].FLOAT;
            else
                cout<<(*tempLine)[j].CHAR;
            if(!j)
                cout<<" | ";
        }
        cout<<endl;
    }
    cout<<"----------------End----------------"<<endl;
}
