//
// Created by 74096 on 2020/6/1.
//

#include "indexManager.h"

indexManager::indexManager()
{
    buffer = new bufferManager();
}

void deleteFile(string filePath)
{
    remove(filePath.c_str());
}

int indexManager::find(const char* indexName, const char* key)
{
    BPTree* tree = new BPTree(("index/" + string(indexName)).c_str());
    int ret = tree->find(key);
    delete tree;
    return ret;
}

bool indexManager::insert(const char* indexName, const char* key, int value)
{
    BPTree* tree = new BPTree(("index/" + string(indexName)).c_str());
    bool ret = tree->add(key, value);
    if (!ret) cout<<"Insertion causes duplicate key in a B+ Tree"<<endl;
    delete tree;
    return ret;
}

bool indexManager::remove(const char* indexName, const char* key)
{
    BPTree* tree = new BPTree(("index/" + string(indexName)).c_str());
    bool ret = tree->remove(key);
    if (!ret) cout<<"B+ Tree does not have the key to be deleted"<<endl;
    delete tree;
    return ret;
}

bool indexManager::createIndex(const char* indexName)
{
    catalogManager* manager = new catalogManager();
    index* index = manager->getIndex(string(indexName));
    if (index == NULL)
        return false;
    Table* table = manager->getTable(string(index->getTableName()));
    if (table == NULL)
        return false;
    dataType* temp = table->searchAttribution(index->getColumnName());
    int keyLength = temp->getDataLength();
    int dataType = temp->n;
    BPTree::createFile(("index/" + string(indexName)).c_str(), keyLength, dataType);
    return true;
}

bool indexManager::dropIndex(const char* indexName)
{
    string filePath = string("data/") + string("index/") + string(indexName) + string(".mdb");
    deleteFile(filePath);
    buffer->clearBuffer();
    return true;
}

