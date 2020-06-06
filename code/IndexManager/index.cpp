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


const char * index::getName() const
{
    return name.c_str();
}


const char * index::getTableName() const
{
    return tableName.c_str();
}

const char * index::getColumnName() const
{
    return columnName.c_str();
}