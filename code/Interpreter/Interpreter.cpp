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

//这个函数的返回值其实是表示可以继续下一句SQL指令的读取和执行，不是说语法是否错误
//这里就算语法错误返回的也是true，因为要执行下一句，只有当需要退出的时候才会返回false，我暂时也想不出更好的设计了
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
    //此处可以添加一个能彻底去掉多余空格的处理函数，不过我这里先做最理想的情况就是每个刚好一个空格
    else //下面都是基本的SQL语句的语法分解
    {
        int checkBracket = StringProcessor::bracketProcessor(cmd);
        if(!checkBracket)
            cout<<"Syntax Error! Please check your brackets in the SQL!"<<endl;
        else if(checkBracket == 1)
        {
            //对create和insert语句进行初步的语义分割
            cout<<cmd<<endl;
            int start = cmd.find_first_of('(');
            int end = cmd.find_last_of(')');
            //Kind 和 Val分别代表了进行的操作和表名，需要操作的数据
            string operateKind = cmd.substr(0, start);
            string operateVal = cmd.substr(start + 1, end - start - 1);
            cout<<operateKind<<endl;
            cout<<operateVal<<endl;
            //继续进一步的处理
        }
        //这里涵盖的指令有drop，delete，insert，select，
        else if(checkBracket == -1)
        {
            //对其他类型的语句进行初步语义分割
            vector<string> operate = StringProcessor::Split(cmd, " ");
            for(int i=0; i < operate.size(); i++)
            {
                //再一次去括号，防止有多余的括号
                StringProcessor::preTrim(operate[i]);
            }
            if(operate.empty())
            {
                cout<<"Syntax Error! No executable SQL command!"<<endl;
                return true; //继续下一句SQL命令
            }
            StringProcessor::showOperation(operate);
            if(operate[0] == "drop")
            {
                if(operate[1] == "table")
                {
                    if(operate.size() != 3)
                    {
                        //参数个数错误
                        cout<<"Syntax Error! Extra parameters in drop table!"<<endl;
                    }
                    else
                    {
                        //进行drop table的语法分解，并调用API
                    }
                }
                else if(operate[1] == "index")
                {
                    if(operate.size() != 3)
                    {
                        cout<<"Syntax Error! Extra parameters in drop index!"<<endl;
                    }
                    else
                    {
                        //进行drop index的语法分解
                    }
                }
                else
                {
                    //drop了table和index以外的东西
                    cout<<"Syntax Error! No such drop operation!"<<endl;
                }
            }
            else if(operate[0] == "delete")
            {
                if(operate[1] != "from")
                {
                    cout<<"Syntax Error! No such delete operation!"<<endl;
                }
                else
                {
                    if(operate.size() <= 4)
                    {
                        cout<<"Syntax Error! Lack of parameters."<<endl;
                    }
                    else if(operate[3] != "where")
                    {
                        cout<<"Syntax Error! Key word Error!"<<endl;
                    }
                    else
                    {
                        //进行进一步的delete类型的语句分解
                    }
                }
            }
            /*这一部分应该是前面的，明天再继续改
            else if(operate[0] == "insert")
            {
                if(operate[1] != "into")
                {
                    //不是into 语法错误
                    cout<<"Syntax Error! Key Word Error!"<<endl;
                }
                else
                {
                    if(operate.size() > 4)
                    {
                        cout<<"Syntax Error! Extra parameters in insert!"<<endl;
                    }
                    else if(operate.size() <= 3)
                    {
                        cout<<"Syntax Error! Lack of parameters."<<endl;
                    }
                    else
                    {
                        //正常执行insert语句
                    }
                }
            }
             */
            else if(operate[0] == "select")
            {
                if(operate.size() <= 5)
                {
                    cout<<"Syntax Error! Lack of parameters."<<endl;
                }
                else if(operate[2] != "from" || operate[4] != "where")
                {
                    cout<<"Syntax Error! Key Word Error!"<<endl;
                }
                else
                {
                    //正常执行select语句的分割
                }
            }
        }


    }

    return true;
}

void Interpreter::exeFile(const string &file)
{
    ifstream fin;
    fin.open(file, ios::in);
    if(fin.fail())
    {
        cout<<"Error! Can't find the file on the path! Please try again!"<<endl;
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
        if(!cmd.empty())
        {
            cout<<"Syntax Error! Please try again!"<<endl;
        }
    }
}
