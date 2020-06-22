//
// Created by 15888 on 2020/6/22.
//

#ifndef CODE_BPTREENODE_H
#define CODE_BPTREENODE_H

#include <string>
#include <vector>
using namespace std;

class BPTreeNode {
public:
    // from file
    BPTreeNode(const char* _filename, int _id, int _keyLength, int _dataType);
    // empty
    BPTreeNode(const char* _filename, int _id, int _keyLength, int _dataType, bool _leaf, int firstPtr);

    ~BPTreeNode();

private:
    string filename;
    int id;
    int size;
    int keyLength;
    int dataType;
    bool leaf;
    bool dirty;
    bool removed;
    vector<char*> keys;
    vector<int> ptrs;
};


#endif //CODE_BPTREENODE_H
