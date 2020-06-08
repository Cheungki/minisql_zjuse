//
// Created by 74096 on 2020/6/5.
//

#include "index.h"
index::index(string& self, string& table, string& column)
{
    name = self;
    tableName = table;
    columnName = column;
}


string index::getName() const
{
    return name.c_str();
}


string index::getTableName() const
{
    return tableName.c_str();
}

string index::getColumnName() const
{
    return columnName.c_str();
}