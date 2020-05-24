//
// Created by 74096 on 2020/5/24.
//

#include "Interpreter.h"

string Interpreter::getCMD()
{
    //这一段主要是从命令行读取一条完整的指令
    string cmd,temp;
    int flag = false;
    while(true)
    {
        if(!flag)
        {
            cout<<"miniSQL";
            flag = true;
        }
        else
            cout<<"       ";
        cout<<">";
        getline(cin,temp);
        StringProcessor::preTrim(temp);
        if(temp.empty())
            continue;
        cmd += temp;
        if(temp[temp.length()-1] == ';')
            break;
    }
    return StringProcessor::cmdOptimum(cmd);
}

bool Interpreter::execute(std::string cmd)
{
    //execute the cmd in a string
    cout<<cmd<<endl;
    //退出的情况
    if(cmd.find("quit") == 0)
    {
        if(cmd.length() != 4)
        {
            cout<<"Syntax Error!Please try again!"<<endl;
            return true;
        }
        else
        {
            cout<<"Thank you for using such a sb system, see you next time!"<<endl;
            cout<<"-------------------------------------------"<<endl;
            //exit(0);
            return false;
        }
    }
    else if(cmd.find("execfile") == 0)
    {
        string file_name = cmd.substr(8);
        StringProcessor::preTrim(file_name);
        // cout<<"file name: "<<file_name<<endl;
        //这里需要转换一下文件的路径，默认这个SQL文件是放在code文件夹下的，输入的时候输入的是文件名，不包含路径
        string path = "..\\" + file_name;
        // cout<<"file path: "<<path<<endl;
        exeFile(path);
        return true;
    }
    else //下面都是基本的SQL语句的语法分解
    {

        if(!StringProcessor::bracketProcessor(cmd))
            cout<<"Syntax Error! Please check your brackets in the SQL!"<<endl;
        else
        {
            cout<<cmd<<endl;
            int start = cmd.find_first_of('(');
            int end = cmd.find_last_of(')');
            //Kind 和 Val分别代表了进行的操作和表名，需要操作的数据
            string operateKind = cmd.substr(0, start);
            string operateVal = cmd.substr(start + 1, end - start - 1);
            cout<<operateKind<<endl;
            cout<<operateVal<<endl;
        }


        //此处可以添加一个能彻底去掉多余空格的处理函数，不过我这里先做最理想的情况就是每个刚好一个空格
        //vector<string> operation = StringProcessor::Split(cmd, " ");
        //StringProcessor::showOperation(operation);

    }

    return true;
}

void Interpreter::exeFile(const string &file)
{
    ifstream fin;
    fin.open(file, ios::in);
    if(fin.fail())
    {
        cout<<"Can't find the file on the path! Please try again!"<<endl;
        return ;
    }
    else
    {
        string cmd,temp;
        while(getline(fin,temp))
        {
            StringProcessor::preTrim(temp);
            if(temp.empty())
                continue;
            cmd += temp;
            if(temp[temp.length() - 1] == ';')
            {
                cmd = StringProcessor::cmdOptimum(cmd);
                execute(cmd);
                cmd = "";
            }
        }
        if(cmd != "")
        {
            cout<<"Syntax Error! Please try again!"<<endl;
        }
    }
}
