//
// Created by 74096 on 2020/5/24.
//

#ifndef CODE_STRINGPROCESSOR_H
#define CODE_STRINGPROCESSOR_H
#include<iostream>
#include<vector>
#include<string>

using namespace std;


class StringProcessor {
public:
    static void PreTrim(string &s)
    {
        if(s.empty())
            return ;
        else
        {
            s.erase(0, s.find_first_not_of(" "));
            s.erase(s.find_last_not_of(" ") + 1);
            return ;
        }
    }
};

#endif //CODE_STRINGPROCESSOR_H
