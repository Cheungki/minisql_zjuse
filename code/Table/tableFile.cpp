//
// Created by 74096 on 2020/6/9.
//

#include "tableFile.h"

tableFile::tableFile(string name) /* 构造函数，初始化catalog和buffer。 */
{
    tableName = name;
    catalog = new catalogManager();
    buffer = new bufferManager();

    /* Initialize the original data structure. */
    table = catalog->getTable(tableName);
    sizeOfRecord = table->size;
    recordNumOfBlock = table->numPerBlock;

    /* Read header information from buffer. */
    singleBlock* headerOfBlock = buffer->getBlock(tableName, 0);
    char* data = headerOfBlock->data;
    fileManager::readInt(data, &emptyID);
    fileManager::readInt(data + 4, &blockNum);
    fileManager::readInt(data + 8, &recordNum);
    fileManager::readInt(data + 12, &maxID);
}

tableFile::~tableFile() /* 析构函数 */
{
    delete catalog;
    delete buffer;
}

int tableFile::recordInsert(vector<tableValue>* values)
{
    int blockID = (emptyID / recordNumOfBlock) + 1;
    int offset = (emptyID % recordNumOfBlock) * sizeOfRecord;
    int originID = emptyID;
    maxID = maxID > emptyID ? maxID : emptyID;
    singleBlock* block;

    /* Verify if the size of the blocks is enough. */
    if(blockID < blockNum) block = buffer->getBlock(tableName, blockID);
    else {
        buffer->appendNode(tableName);
        block = buffer->getBlock(tableName, blockNum++);
    }
    recordNum++;

    char* pointer = block->data + offset;
    if(recordNum == maxID + 1) emptyID++;
    else fileManager::readInt(pointer + 1, &emptyID);

    /* Store the data into the block. */
    fileManager::writeTableValue(pointer, values, table);
    buffer->writeBlock(block);
    updateHeader();
    return originID;
}

bool tableFile::recordDelete(int id, bool commit)
{
    int blockID = (id / recordNumOfBlock) + 1;
    int offset = (id % recordNumOfBlock) * sizeOfRecord;
    if(blockID > maxID) ; /* Here, the user is trying to access a non-existent record. */

    /* Find the block and the pointer. */
    singleBlock* block = buffer->getBlock(tableName, blockID);
    char* pointer = block->data + offset;
    char flag;

    /* Verify if the record is null. */
    memcpy(&flag, pointer, 1);
    if(!flag) ; /* Report that the record is non-existent. */

    /* Reset the variables. */
    *pointer = 0;
    pointer++;
    fileManager::writeInt(pointer, emptyID);
    emptyID = id;
    recordNum--;

    if(commit) { /* Committing a deletion is aviliable. */
        buffer->writeBlock(block);
        updateHeader();
    }
    else block->pin = true; /* To lock this block. */
    return true;
}

vector<tableValue>* tableFile::getRecord(int id, bool isNull)
{
    int blockID = (id / recordNumOfBlock) + 1;
    int offset = (id % recordNumOfBlock) * sizeOfRecord;

    if(blockID > maxID) ; /* Here, the user is trying to access a non-existent record. */
    else {
        /* Find the block and the pointer. */
        singleBlock* block = buffer->getBlock(tableName, blockID);
        char* pointer = block->data + offset;
        char flag;

        /* Verify if the record is null. */
        memcpy(&flag, pointer, 1);
        if(!flag && isNull) {
            /* Report that the record is non-existent. */
            return nullptr;
        }

        auto* recordsContents = new vector<tableValue>;
        if(fileManager::readTableValue(pointer, recordsContents, table)) return recordsContents;
    }
}

bool tableFile::updateHeader()
{
    singleBlock* headerOfBlock = buffer->getBlock(tableName, 0);
    char* data = headerOfBlock->data;
    fileManager::writeInt(data, emptyID);
    fileManager::writeInt(data + 4, blockNum);
    fileManager::writeInt(data + 8, recordNumOfBlock);
    fileManager::writeInt(data + 12, maxID);
    return buffer->writeBlock(headerOfBlock);
}

int tableFile::getByID(int id)
{
    return id / recordNumOfBlock + 1;
}

int tableFile::getMaxID()
{
    return maxID;
}