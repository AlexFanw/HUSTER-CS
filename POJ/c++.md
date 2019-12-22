# Alex Fan的C++学习笔记
本文基于读者已有c语言基础.

## 注释

```c++
/*
note something
*/

//note something
```

以上是两种常用的注释方法

甚至可以用这种方法来注释和调试代码·

```c++
#if 1
	code1
#else
	code2
#endif
```

此时只需要更改#if后面的1/0,即可选择执行哪一段代码,非常方便.



## 数据类型

1.typedef **type** *newdata_name*

newdata_name sth

```c++
typedef int newint;
newint alex = 1;//int alex =1;
```

2.枚举enum

```c++
enum 枚举名{ 
     标识符[=整型常数], 
     标识符[=整型常数], 
... 
    标识符[=整型常数]
} 枚举变量;
```



## 变量类型

变量可以在外部声明,再在内部定义.

```c++
#include <iostream>
using namespace std;
int func();//声明函数
// 变量声明
extern int a, b;
extern int c;
extern float f;
  
int main ()
{
  // 变量定义
  int a, b;
  int c;
  float f;
 
  // 实际初始化
  a = 10;
  b = 20;
  c = a + b;
 
  cout << c << endl ;
 
  f = 70.0/3.0;
  cout << f << endl ;
 
  return 0;
}
int func(){
  return 0;
}
```



## 常量定义

```c++
#define identifier value
#define length 10 //不需要加;号

const type variable = value;
const int length = 10;//同样也是函数定义
```





## 修饰符类型

C++ 允许在 **char、int 和 double** 数据类型前放置修饰符。修饰符用于改变基本类型的含义，所以它更能满足各种情境的需求。

下面列出了数据类型修饰符：

- signed
- unsigned
- long
- short

修饰符 **signed、unsigned、long 和 short** 可应用于整型，**signed** 和 **unsigned** 可应用于字符型，**long** 可应用于双精度型。

修饰符 **signed** 和 **unsigned** 也可以作为 **long** 或 **short** 修饰符的前缀。例如：**unsigned long int**。

C++ 允许使用速记符号来声明**无符号短整数**或**无符号长整数**。您可以不写 int，只写单词 **unsigned、short** 或 **unsigned、long**，int 是隐含的。例如，下面的两个语句都声明了无符号整型变量。

```c++
unsigned x;
unsigned int y;
```





## 存储类

* auto 存储类

	自 C++ 11 以来，**auto** 关键字用于两种情况：声明变量时根据初始化表达式自动推断该变量的类型、声明函数时函数返回值的占位符。

	```c++
	auto f=3.14;      //double
	auto s("hello");  //const char*
	auto z = new auto(9); // int*
	auto x1 = 5, x2 = 5.0, x3='r';//错误，必须是初始化为同一类型
	```

* register 存储类

	**register** 存储类用于定义存储在寄存器中而不是 RAM 中的局部变量。这意味着变量的最大尺寸等于寄存器的大小（通常是一个词），且不能对它应用一元的 '&' 运算符（因为它没有内存位置）。

* static 存储类

	**static** 存储类指示编译器在程序的生命周期内保持局部变量的存在，而不需要在每次它进入和离开作用域时进行创建和销毁。

	static 修饰符也可以应用于全局变量。当 static 修饰全局变量时，会使变量的作用域限制在声明它的文件内。

	```c++
	#include <iostream>
	 
	// 函数声明 
	void func(void);
	 
	static int count = 10; /* 全局变量 */
	 
	int main()
	{
	    while(count--)
	    {
	       func();
	    }
	    return 0;
	}
	// 函数定义
	void func( void )
	{
	    static int i = 5; // 局部静态变量
	    i++;
	    std::cout << "变量 i 为 " << i ;
	    std::cout << " , 变量 count 为 " << count << std::endl;
	}
	```

* extern 存储类

	**extern** 存储类用于提供一个全局变量的引用，全局变量对所有的程序文件都是可见的。

	```c++
	//第一个文件 main.cpp
	#include <iostream>
	using namespace std;
	int count = 1;
	extern void write_ex();
	
	//第二个文件 mai n.cpp
	#include <iostream>
	using namespace std;
	extern int count;
	void write_ex(void){
	  cout << "alexfan" << endl;
	}
	```

* mutable 存储类

	待补充;

* thread_local 存储类

	使用 thread_local 说明符声明的变量仅可在它在其上创建的线程上访问。 变量在创建线程时创建，并在销毁线程时销毁。 每个线程都有其自己的变量副本。





## 运算符

除了加、减、乘、除、与、或、非之外,还有一个赋值运算符

![image-20191129114235635](/Users/alexfan/Library/Application Support/typora-user-images/image-20191129114235635.png)



## 循环

* while()

	和c语言相似

* for()

	除了c语言中的for循环的用法,在新标准中可以用类似于python中的

	for sth in array.:thumbsup:

	```c++
	int my_array[5] = {1, 2, 3, 4, 5};
	// 每个数组元素乘于 2
	for (int &x : my_array)
	{
	    x *= 2;
	    cout << x << endl;  
	}
	// auto 类型也是 C++11 新标准中的，用来自动获取变量的类型
	for (auto &x : my_array) {
	    x *= 2;
	    cout << x << endl;  
	}
	```

* do...while()

	```c++
	do
	   {
	       cout << "a 的值：" << a << endl;
	       a = a + 1;
	   }while( a < 20 );
	```

* 嵌套循环



## 判断

![image-20191129130041353](/Users/alexfan/Library/Application Support/typora-user-images/image-20191129130041353.png)



## 函数

同c语言

## 数字

![image-20191129132857119](/Users/alexfan/Library/Application Support/typora-user-images/image-20191129132857119.png)

**c语言随机数**

```c++
#include <iostream>
#include <ctime>
#include <cstdlib>
 
using namespace std;
 
int main ()
{
   int i,j;
 
   // 设置种子
   srand( (unsigned)time( NULL ) );
 
   /* 生成 10 个随机数 */
   for( i = 0; i < 10; i++ )
   {
      // 生成实际的随机数
      j= rand();
      cout <<"随机数： " << j << endl;
   }
 
   return 0;
}
```



## 数组

```c++
type arrayName [ arraySize ]; //c++数组的定义
```

```c++
double balance[5] = {1000.0, 2.0, 3.4, 7.0, 50.0};//实例
```

多维数组

指针数组

数组指针



## 字符串

C 风格的字符串起源于 C 语言，并在 C++ 中继续得到支持。字符串实际上是使用 **null** 字符 '\0' 终止的一维字符数组。因此，一个以 null 结尾的字符串，包含了组成字符串的字符。

<img src="/Users/alexfan/Library/Application Support/typora-user-images/image-20191129134348852.png" alt="image-20191129134348852" style="zoom:50%;" />



**c++的string类**

```c++
#include <iostream>
#include <string>
 
using namespace std;
 
int main ()
{
   string str1 = "Hello";
   string str2 = "World";
   string str3;
   int  len ;
 
   // 复制 str1 到 str3
   str3 = str1;
   cout << "str3 : " << str3 << endl;
 
   // 连接 str1 和 str2
   str3 = str1 + str2;
   cout << "str1 + str2 : " << str3 << endl;
 
   // 连接后，str3 的总长度
   len = str3.size();
   cout << "str3.size() :  " << len << endl;
 
   return 0;
}
```



## 指针&引用

int* int型指针,值为int型元素的地址.

*可以理解为从地址里面取值

&可以理解为取地址

```c++
int& y = a;//引用的意思是直接引用地址.但是y不是地址,a也不是地址,只是y和a的地址相同.
int* x = &a;//指针的意思是将a中的地址当成值传给x
```







## 日期&时间



## 基本输入输出

通过这些小实例，我们无法区分 cout、cerr 和 clog 的差异，但在编写和执行大型程序时，它们之间的差异就变得非常明显。所以良好的编程实践告诉我们，使用 cerr 流来显示错误消息，而其他的日志消息则使用 clog 流来输出。

```c++
#include <iostream>
 
using namespace std;
 
int main( )
{
   char str[] = "Hello C++";
 
   cout << "Value of str is : " << str << endl;
}
```

```c++
#include <iostream>
 
using namespace std;
 
int main( )
{
   char name[50];
 
   cout << "请输入您的名称： ";
   cin >> name;
   cout << "您的名称是： " << name << endl;
 
}
```

```c++
#include <iostream>
 
using namespace std;
 
int main( )
{
   char str[] = "Unable to read....";
 
   cerr << "Error message : " << str << endl;
}
```

```c++
#include <iostream>
 
using namespace std;
 
int main( )
{
   char str[] = "Unable to read....";
 
   clog << "Error message : " << str << endl;
}
```



## 数据结构

```c++
struct type_name {
member_type1 member_name1;
member_type2 member_name2;
member_type3 member_name3;
.
.
} object_names;//数据结构的定义.
```



# 类&对象



# Others

* memset(str,int n ,int a);

	> memset(结构体/数组名 , 用于替换的ASCII码对应字符 , 前n个字符 );
	>
	> 头文件 string

* memset(str,char n ,int a);

	> memset(结构体/数组名 , "用于替换的字符“ , 前n个字符 );
	>
	> 头文件 string