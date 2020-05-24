//
// Created by 74096 on 2020/5/24.
//

#ifndef CODE_STRINGPROCESSOR_H
#define CODE_STRINGPROCESSOR_H
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;


class StringProcessor {
public:
    //去空格的处理函数，其实应该还需要一个把多个空格替换成一个空格的函数，不过这里先考虑最简单的情况先不写了
    static void preTrim(string &s)
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

    //把字符串按某个符号进行切分的处理函数
    //s 是要处理的长字符串, unit是切分的标志
    static vector<string> Split(const string &s, const string &unit)
    {
        int start,len=unit.length();
        vector<string> result;
        if(s == ""||s == unit)
            return result;
        string x = s;
        preTrim(x);
        start = x.find(unit);
        while(start != -1)
        {
            result.push_back(x.substr(0,start));
            x=x.substr(start+len);
            preTrim(x);
            start = x.find(unit);
        }
        if(x.length() >= 1)
            result.push_back(x);
        return result;
    }

    // 对cmd命令的优化，包括去首尾空格和全部转换成小写，卸载这个类里提高了代码的复用性
    static string cmdOptimum(string& cmd)
    {
        for(int i=0; i < cmd.length() ; i++)
        {
            if(cmd[i] == '\t')
                cmd[i] = ' ';
            if(cmd[i] >= 'A'&&cmd[i] <= 'Z')
                cmd[i] += 32;
        }
        preTrim(cmd);
        cmd = cmd.substr(0, cmd.length()-1);
        preTrim(cmd);
        return cmd;
    }

    static void showOperation(vector<string> op)
    {
        for(int i=0; i < op.size(); i++)
        {
            cout<<"Position "<<i<<" :"<<op[i]<<endl;
        }
    }

    //用来删除命令中的括号
    static bool bracketProcessor(string& cmd)
    {
        vector<int> left, right;
        for(int i = 0; i < cmd.length(); i++ )
        {
            if(cmd[i] == '(')
            {
                left.push_back(i);
            }
            else if(cmd[i] == ')')
            {
                right.push_back(i);
            }
        }
        //左右括号数量不相同，说明语法错误
        if(left.size() != right.size())
            return false;
        else
        {
            int len = left.size(); //共同的个数
            //这种情况下的括号是错位的
            return !(left[len - 1] >= right[len - 1] || right[0] <= left[0]);
        }

    }
};

#endif //CODE_STRINGPROCESSOR_H
