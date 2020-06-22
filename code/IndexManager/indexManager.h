//
// Created by 74096 on 2020/6/1.
//

#ifndef CODE_INDEXMANAGER_H
#define CODE_INDEXMANAGER_H

#include <fstream>
#include"../BufferManager/bufferManager.h"
#include"../IndexManager/index.h"


class indexManager {
public:
    indexManager();
    int find(const char* indexName, const char* key);
    bool insert(const char* indexName, const char* key, int value);
    bool remove(const char* indexName, const char* key);
    bool createIndex(const char* indexName);
    bool dropIndex(const char* indexName);
private:
    bufferManager *buffer;
};


#endif //CODE_INDEXMANAGER_H
