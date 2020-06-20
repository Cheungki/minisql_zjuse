//
// Created by 74096 on 2020/6/1.
//

#ifndef CODE_BUFFERMANAGER_H
#define CODE_BUFFERMANAGER_H
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include"fileManager.h"


using namespace std;

class singleBlock{
public:
    string fileName;
    int blockID;
    //pin表示一个block被锁了，不能被删除
    //is changed代表这个block是否被进行了修改
    bool pin, isChanged;
    char data[blockSize];
    singleBlock(const string& name, const int& id){
        fileName = name;
        blockID = id;
        pin = false;
        isChanged = false;
    }
};

// 其实是一个由单个block 组合而成的链表
struct bufferNode{
    singleBlock* block;
    bufferNode *last, *next;
    explicit bufferNode(singleBlock* temp){
        block = temp;
        last = next = nullptr;
    }
    ~bufferNode(){
        remove();
    }
    void remove(){
        if(next != nullptr)
            last->next = next;
        if(last != nullptr)
            next->last = last;
    }
};


class bufferManager {
private:
    static int blockCount;
    static bufferNode *head, *tail;
    static map<string, bufferNode*> nodeMap;
    singleBlock* loadBlock(const string& fileName, int id);
    bool deleteNode(bufferNode *node);
public:
    static const int maxBlockNumber;
    bufferManager();
    singleBlock* getBlock(const string& fileName, int id);
    bool writeBlock(const string& fileName, int id);
    bool writeBlock(singleBlock* block);
    bool accessNode(bufferNode* node);
    bool appendNode(const string& fileName);
    bool clearBuffer();
};


#endif //CODE_BUFFERMANAGER_H
