//
// Created by 74096 on 2020/5/24.
//

#include "Interpreter.h"

string Interpreter::getCMD()
{
    //这一段主要是从命令行读取一条完整的指令
    string cmd,temp;
    int flag=false;
    while(true)
    {
        if(!flag)
        {
            cout<<"miniSQL";
            flag=true;
        }
        else
            cout<<"       ";
        cout<<">";
        getline(cin,temp);
        StringProcessor::PreTrim(temp);
        if(temp.empty())
            continue;
        cmd+=temp;
        if(temp[temp.length()-1]==';')
            break;
    }
    for(int i=0;i<cmd.length();i++)
    {
        if(cmd[i] == '\t')
            cmd[i]=' ';
        if(cmd[i]>='A'&&cmd[i]<='X')
            cmd[i]+=32;
    }
    StringProcessor::PreTrim(cmd);
    cmd=cmd.substr(0,cmd.length()-1);
    StringProcessor::PreTrim(cmd);
    return cmd;
}

bool Interpreter::Execute(std::string cmd)
{
    //execute the cmd in a string
    cout<<cmd<<endl;
    //退出的情况
    if(cmd.find("quit")==0)
    {
        if(cmd.length()!=4)
        {
            cout<<"Syntax Error!Please try again!"<<endl;
            return true;
        }
        else
        {
            cout<<"Thank you for using such a sb system, see you next time!"<<endl;
            cout<<"-------------------------------------------"<<endl;
            exit(0);
            return false;
        }
    }

    return true;
}
