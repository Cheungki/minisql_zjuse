//
// Created by 15888 on 2020/6/22.
//
#include <iostream>
#include <cstring>
#include <algorithm>
#include "../BufferManager/bufferManager.h"
#include "BPTreeNode.h"

BPTreeNode::BPTreeNode(const char *_filename, int _id, int _keyLength, int _dataType)
    :filename(_filename), id(_id), keyLength(_keyLength), dataType(_dataType)
{
    bufferManager* manager = new bufferManager();
    Block* block = manager->getBlock(_filename, _id);
    char* data = block->data;

    size = *(reinterpret_cast<int*>(data));
    keys.push_back(NULL);
    ptrs.push_back(*(reinterpret_cast<int*>(data + 4)));
    leaf = ptrs[0] < 0 ? true : false;
    removed = dirty = false;
    for (int i = 1, bias = 8; i <= size; i++, bias += keyLength + 4)
    {
        char* k = new char[keyLength];
        memcpy(k, data + bias, keyLength);
        keys.push_back(k);
        ptrs.push_back(*(reinterpret_cast<int*>(data + bias + keyLength)));
    }
}
