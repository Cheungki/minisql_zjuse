//
// Created by 74096 on 2020/6/5.
//

#ifndef CODE_INDEX_H
#define CODE_INDEX_H
#include<string>

using namespace std;

class index {
public:
    index(string& self, string& table, string& column);
    const char* getName() const;
    const char* getTableName() const;
    const char* getColumnName() const;

private:
    string name, tableName, columnName;
};


#endif //CODE_INDEX_H
