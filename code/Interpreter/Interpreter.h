//
// Created by 74096 on 2020/5/24.
//

#ifndef CODE_INTERPRETER_H
#define CODE_INTERPRETER_H
#include<iostream>
#include<vector>
#include<string>

#include "../StringProcessor/StringProcessor.h"
using namespace std;


class Interpreter {
public:
    //这里本来想写成static 类型的，但是后来发现static类型需要定义在类的内部，就改成了普通的成员函数类型
    string getCMD();
    bool Execute(string cmd);

};


#endif //CODE_INTERPRETER_H
