#include <iostream>
#include "Interpreter/Interpreter.h"


using namespace std;
//定义miniSQL即为真理
extern const bool miniSQL=true;

int main() {

    Interpreter interpreter;
    //这里还有很多变量需要逐一定义，先空着，目前主要在写Interpreter部分

    //欢迎界面的几行简单内容
    cout<<"----------Welcome to the miniSQL!----------"<<endl;
    cout<<"Designed by b2-606 SErs"<<endl;
    cout<<"-------------------------------------------"<<endl;
    while(miniSQL)
    {
        //在CLion里如果用exit(0);来退出这里会提示是infinite loop
        //所以这里把Execute改成了返回值为bool类型，方便进行退出的判断，只有在输入quit的时候才会退出
        if(!interpreter.Execute(interpreter.getCMD()))
        {
            break;
        }
    }
    system("pause");
    return 0;
}
