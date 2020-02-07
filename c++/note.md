编译程序：

```
g++ -o prog1 prog1.cc
g++ -std=c++11
```

-Wall 选项：发出警告


```
#include <iostream>

cout, cin, cerr, clog
<< 输出
>> 输入
endl 操纵符，刷新缓冲区
:: 作用域运算符
```

当从键盘向程序输入数据时，对于如何指出文件结束，不同操作系统有不同的约定。在Windows 系统中，输入文件结束符的方法是敲Ctrl+Z（按住Ctrl 键的同时按Z 键），然后按Enter 或Return 键。在UNIX 系统中，包括Mac OS X 系统中，文件结束符输入是用Ctrl+D。

初始化

```c++
// 用花括号来初始化变量称为列表初始化
int a = 0;
int a = {0};
int a{0};
int a(0);
```

如果定义变量时没有指定初值，则变量被**默认初始化**。内置类型：定义于任何函数之外的变量被初始化为0，定义在函数内部的内置类型变量将**不被初始化**。

分离式编译：声明和定义区分开，声明使得名字为程序所知，一个文件如果想使用别处定义的名字则必须包含对那个名字的声明。而定义负责创建与名字关联的实体。

```c++
extern int i; // 声明i而非定义i
int j; // 声明并定义j
extern double pi = 3.1416; // 定义
```

建议：当你第一次使用变量的时候再定义它。



引用

```c++
int ival = 1024;
int &refVal = ival; // refVal 指向ival（是ival的另一个名字）
int &refVal2; // 报错：引用必须被初始化
```

引用并非对象，它只是为一个已经存在的对象所起的另外一个名字。

引用只能绑定在对象上，而不能与字面值或某个表达式的计算结果绑定在一起。



指针

指针也实现了对其他对象的间接访问。指针和引用的不同点：一，指针本身就是一个对象，允许对指针赋值和拷贝，而且在指针的生命周期内它可以先后指向几个不同的对象。二、指针无须在定义时赋值。和其他内置类型一样，在块作用域内定义的指针如果没有被初始化，也将拥有一个不确定的值。

指针值所属4种状态：
1. 指向一个对象
2. 指向紧邻对象所占空间的下一个位置
3. 空指针，意味着指针没有指向任何对象
4. 无效指针，也就是上述情况之外的其他值

生成空指针的方法：
```c++
int *p1 = nullptr;
int *p2 = 0;
int *p3 = NULL; // 需要首先 #include cstdlib
```

nullptr 是一种特殊类型的字面值，它可以被转换成任意其他的指针类型。



理解复合类型的声明

```c++
// i 是一个 int 型的数，p 是一个 int 型指针，r 是一个 int 型引用
int i = 1024, *p = &i, &r = i;

int* p1, p2; // p1 是指向 int 的指针，p2 是 int
int *p1, *p2; // p1 和 p2 都是指向 int 的指针

int ival = 1024;
int *pi = &ival; // pi 指向一个 int 型的数
int **ppi = &pi; // ppi 指向一个 int 型的指针
```

指向指针的引用

```c++
int i = 42;
int *p; // p 是一个 int 型指针
int *&r = p; // r 是一个对指针 p 的引用

r = &i; // r 引用了一个指针，因此给 r 赋值 &i 就是令 p 指向 i
*r = 0; // 解引用 r 得到 i，也就是 p 指向的对象，将 i 的值改为 0
```

const 限定符

const 对象一旦创建后其值就不能再改变，所以 const 对象必须初始化。

const 的引用

```c++
const int ci = 1024;
const int &r1 = ci; // 正确：引用及其对应的对象都是常量
r1 = 42; // 错误：r1 是对常量的引用
int &r2 = ci; // 错误：试图让一个非常量引用指向一个常量对象



int i = 42;
const int &r1 = i; // 允许将 const int& 绑定到一个普通 int 对象上
const int &r2 = 42; // 正确：r1 是一个常量引用
const int &r3 = r1 *2; // 正确：r3 是一个常量引用
int &r4 = r1 * 2; // 错误：r4 是一个普通的非常量引用



int i = 42;
int &r1 = i;
const int &r2 = i; // 不允许通过 r2 修改 i 的值
r1 = 0; // 正确
r2 = 0; // 错误
```

指针和 const

```c++
const double pi = 3.14;
double *ptr = &pi; // 错误
const double *cptr = &pi; // 正确
*cptr = 42; // 错误
```

const指针

```c++
int errNumb = 0;
int *const curErr = &errNumb; // curErr 将一直指向 errNumb
*curErr = 0; // 正确：把 curErr 所指的对象的值重置

const double pi = 3.14;
const double *const pip = &pi; // pip 是一个指向常量对象的常量指针
```

顶层const

指针本身是一个对象，它又可以指向另外一个对象。因此，指针本身是不是常量以及指针所指的是不是一个常量就是两个相互独立的问题。用名词**顶层 const**表示指针本身是个常量，而用名词**底层 const**表示指针所指的对象是一个常量。

顶层 const 可以表示任意的对象是常量，这一点对任何数据类型都适用。

```c++
int i = 0;
int *const p1 = &i; // 不能改变p1的值，顶层const
const int ci = 42; // 不能改变ci的值，顶层const
const int *p2 = &ci; // 允许改变p2的值，底层const
const int *const p3 = p2; // 靠右的const是顶层const，靠左的是底层const
const int &r = ci; // 用于声明引用的const都是底层const

i = ci; // 正确：拷贝ci的值，ci是一个顶层const，对此操作无影响
p2 = p3; // 正确：p2和p3指向的对象类型相同，p3顶层const的部分不影响

int *p = p3; // 错误：p3包含底层const的定义，而p没有
p2 = &i; // 正确：int* 能转换成 const int*
int &r = ci; // 错误：普通的 int& 不能绑定到int常量上
const int &r2 = i; // 正确：const int& 可以绑定到一个普通 int上
```



类型别名

```c++
typedef double wages; // wages 是 double 的同义词
typedef wages base, *p; // base 是 double 的同义词， p 是 double* 的同义词

using SI = Sales_item; // SI 是 Sales_item 的同义词
```

auto 类型说明符

```c++
auto item = val1 +val1;

auto i = 0, *p = &i; // 正确：i是整数，p是整型指针
auto sz = 0, pi = 3.14; // 错误：sz和pi的类型不一致
```

decltype 类型指示符

```c++
decltype(f()) sum = x; // sum 的类型就是函数f的返回类型
```


using

using namespace::name;

头文件不应包含using声明


string

```c++
#include <string>
using std::string;
```

初始化

```c++
string s1;
string s2(s1);
string s2 = s1;
string s3("value");
string s3 = "value";
string s4(n, 'c');


string s5 = "hiya"; // 拷贝初始化
string s6("hiya"); // 直接初始化
stirng s7(10, 'c'); // 直接初始化 cccccccccc
```

stirng 操作

```
os<<s 输出
is>>s 输入
getline(is, s) 从is中读取一行赋给s，返回is
s.empty()
s.size()
s[n]
s1+s2
s1=s2
s1==s2
s1!=s2
<, <=, >, >=
```


cctype 头文件

```
isalnum
isalpha
iscntrl
isdigit
isgraph
islower
isprint
ispunct
isspace
isupper
isxdigit
tolower
toupper
```

基于范围的for语句

```
for (declaration : expression)
  statement
```


vector

```c++
#include <vector>
using std::vector;
```

```c++
vector<int> ivec;
vector<Sales_item> Sales_vec;
vector<vector<string>> file;
```

不存在包含引用的vector

初始化vector对象的方法

```
vector<T> v1
vector<T> v2(v1)
vector<T> v2 = v1
vector<T> v3(n, val)
vector<T> v4(n)
vector<T> v5{a,b,c...}
vector<T> v5={a,b,c...}
```

```c++
vector<int> ivec;
vector<int> ivec2(ivec);
vector<int> ivec3 = ivec;
```


vector 操作

```
v.empty()
v.size()
v.push_back(t)
v[n]
v1 = v2
v1 = {a,b,c...}
v1 == v2
v1 != v2
<, <=, >, >=
```


迭代器

```c++
// b表示v的第一个元素，e表示v尾元素的下一位置
// end成员返回的迭代器被称为尾后迭代器
// 如果容器为空，则begin和end返回的是同一个迭代器
auto b = v.begin(), e = v.end();
```

迭代器运算符

```
*iter
iter->mem
++iter
--iter
iter1 == iter2
iter1 != iter2
```

cbegin, cend

vector 和 string 迭代器支持的运算

```
iter + n
iter - n
iter1 += n
iter1 -= n
iter1 - iter2
> >= < <=
```

difference_type




命名的强制类型转换

```
cast-name<type>(expression);

cast-name: static_cast, dynamic_cast, const_cast, reinterpret_cast
```

标准异常

```
// <stdexcept> 定义的异常类
exception
runtime_error
range_error
overflow_error
underflow_error
logic_error
domain_error
invalid_argument
length_error
out_of_range
```

IO

IO库类型和头文件

```
iostream:
istream, wistream
ostream, wostream
iostream, wiostream

fstream:
ifstream, wifstream
ofstream, wofstream
fstream, wfstream

sstream:
istringstream, wistringstream
ostringstream, wostringstream
stringstream, wstringstream
```

刷新输出缓冲区：endl, flush, ends


fstream

```
fstream fstrm;
fstream fstrm(s);
fstream fstrm(s, mode);
fstrm.open(s);
fstrm.close();
fstrm.is_open();
```

文件模式
```
in
out
app
ate
trunc
binary
```



顺序容器

```
vector 可变大小数组
deque 双端队列
list 双向链表
forward_list 单向链表
array 固定大小数组
string
```

向顺序容器添加元素

```
c.push_back(t)
c.emplace_back(args)
c.push_front(t)
c.emplace_front(args)
c.insert(p, t)
c.emplace(p, args)
c.insert(p, n, t)
c.insert(p,b,e)
c.insert(p, il)
```

容器适配器：stack, queue, priority_queue



动态内存

shared_ptr, unique_ptr, weak_ptr

析构函数：控制对象销毁时做什么操作

直接管理内存：new 分配内存，delete 释放new分配的内存
