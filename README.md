# miniSQL 开发日志	
#### 注：一些暂定的代码规范

- 大括号**不换行**
- Clion作为开发工具
- 每个模块要有一个文件夹，不然代码太乱
- 函数名小驼峰法，中间变量自己编



【zyc】2020.05.23 创建了开发日志，准备开始写miniSQL

【zyc】2020.05.23 又更新了一次试试git怎么使用

【zyc】2020.05.24 添加了一些Interpreter模块的功能，主要是读取输入的指令和一些字符串处理的功能，注释里都有，基本上都参考了https://github.com/Unispac/miniSQL  上面的内容，后面又加了一些处理函数，目前已经做到语义分割部分，刚开始，今天写了半天不想写了

【zyc】2020.05.25继续添加**语义分割**的相关功能，包括select，delete和drop，写了一些基本的SQL语法错误判断，但是正式调用API的部分还没有开始写，后面先继续完成create

【zyc】2020.05.26完成了create和insert语句的初步检查，修复了前面几天出现的一些bug，但可能还有不少bug存在，接下来的工作是要对语句进行进一步的语法分割

【zyc】2020.05.29 更新了二级语法处理的相关代码，下面可以开始写API调用了，同时我改掉了所有的括号换行，不过select部分由于比较麻烦先没有写，等以后慢慢补充，接下来可以先开始准备API调用的编写了，而且table的数据结构之类的东西需要注意一下，这个好像比较麻烦，要先写一个table的数据结构

【zyc】2020.05.30 添加一个table的数据结构，事实上基本都是照搬**参考文献**里的数据结构的，不得不说那个人是真的🐂

【zyc】2020.05.31添加了一个logic的模块，用于比较数据表中数据的大小

【zyc】2020.06.01 添加了几个文件夹，表示整个系统的基本结构，添加了API模块的基本结构，把interpreter中所有调用来调用去的接口全部调通了，**interpreter模块基本完成**，接下来需要写调用API的模块，这牵涉到其他更多的manager模块，非常麻烦，我已经被绕晕了，后面又加了一个block的模块

【zyc】2020.06.06 半夜更新了一点catalog manager的基本框架

【zyc】2020.06.07 晚上出去吃了一顿鸡翅，所以今天更新的不是很多，主要是catalog mamager里面写了几个函数

【zyc】2020.06.08 主要在写catalog Manager，注意table信息表和index信息表中的信息的顺序。应该是这样的

> table：由若干行table的属性组成，每一行中的属性的内容和顺序如下：属性的数据类型，数据长度(主要针对char*类型，数字型的都是4)，属性名，是否unique，是否为主键，是否有索引
>
> index：所有的表共享一个文件，里面每行写的内容是索引名+表名+属性名，文件名是indexNameList.db
>
> 此外所有的表名都写在文件tableNameList.db文件里

今天一天下来catalog模块基本完成，明天把最后一个函数写好应该就可以用了

【zyc】2020.06.09 写完了catalog manager，添加了一个file manager的模块，下属于buffer manager模块

【zyc】2020.06.13 写了一大堆bullshit code完成了一个delete语句的语法二次分解，感觉有点麻烦，语法分解的地方还差最后一个select的语法分解，不过select的地方代码可以复用，预计明天考完证券可以继续搞，问题是好像不容易进行测试，我也不知道有没有bug-free