# Navy Application Framework

使用`make ISA=xxx`编译整个框架。更换ISA时需要`make clean`。默认ISA=native，编译到本地可执行的二进制文件。

框架编译成功后，`fsimg/`目录会包含初始文件系统的镜像。

```
bin/ -- 二进制文件
etc/ -- 配置文件
  init -- 系统启动后加载的第一个程序
share/  -- 平台无关文件
  fonts/ -- 字体文件
  games/ -- 游戏数据
    nes/ -- NES Roms
    pal/ -- 仙剑奇侠传相关数据文件
```

## 支持的ISA/操作系统

### native (编译到本地Linux执行)

编译在本地时不链接libc和libos，使用本地的glibc/glibstdc++ (用g++不带参数链接)。

使用`LD_PRELOAD`实现了本地模拟的`/dev/events`, `/dev/fb`和其他一些设备文件(必须使用ANSI C中的fopen打开)。此外可以模拟nwm的行为。项目中实现了与Nanos兼容的模拟环境，使用以下命令运行native程序：

`make run 参数1 参数2 …`

### x86 (i386, Nanos)

TBD: 静态/动态链接？

### mips32 (小端mips32, Nanos)

TBD: 静态/动态链接？

## 运行库

C运行库: newlib 1.6.1

C++运行库: 最小的手写运行库。(TODO) 添加runtime、全局初始化等。

## 应用程序编写指南

### ANSI C应用程序

原则上，ANSI C程序可以直接编译运行。`stdin`可以读取输入, `stdout`, `stderr`能接受输出。

#### 终端应用程序

向`stdout`, `stderr`输出字符序列显示在终端上，接受ANSI escape sequences (`#`表示数字)：

* `\033[s`：保存光标状态
* `\033[u`：恢复上次保存的光标状态
* `\033[J`/`\033[2J`：清除屏幕
* `\033[K`：清除光标后到行末的字符（含光标处的字符）
* `\033[#;#H`/`\033[#;#f]`：移动光标到数字所在行/列（行/列从1开始编号）。`\033[H`/`\033[f`将移动光标到左上角。
* `\033[#A`：光标向上移动数字行。
* `\033[#B`：光标向下移动数字行。
* `\033[#C`：光标向右移动数字列。
* `\033[#D`：光标向左移动数字列。
* `\033[#;#;...;#m`：设置显示模式。只提供部分ANSI escape sequence的支持。

nterm-specific:

* `\033[1t`: cookmode
* `\033[2t`: rawmode

#### NWM图形程序

nwm创建的图形应用程序通过环境变量`WIDTH`和`HEIGHT`得知自身绘图区域的宽度和高度。

nwm和应用程序通过管道通信。读取`stdin`会得到与`/dev/events`格式一致的事件（包含发送给这个进程的按键和时钟）。向`stdout`写入如下格式的escape sequence实现绘图效果：

* `\033[X@x;@ys` (set)：设置屏幕宽度为`@x`像素、高度为 `@y`像素。
* `\033[X@x;@y;@px1;@px2;...d` (draw) : 将光标移动到第`@x`列、第 `@y`行，然后开始逐个像素绘制(`@px1`, `@px2`, …，直到遇到`X`停止)。每个像素是连续的四个字节，表示按小端存储的整数`00rrggbb `(第一个字节为`bb`，第二个字节为`gg`，以此类推)。左上角第一个像素为(0, 0)。**这个表示目前比较浪费，应该会被改成若干个escape sequences，分别负责光标控制、调色板控制、像素绘制。**

### 调用操作系统功能

navy app假设实现了一部分POSIX系统调用。实现的系统调用越多则能开启越多的功能（调用不支持系统调用时会触发assertion fail）。

此外，navy假设操作系统提供以下设备文件的支持：

1. 设备文件

    * `/dev/null`、`/dev/zero`: 永远返回空，和永远返回0的虚拟设备。
    * `/dev/fb`: 只可写的设备。看起来是一个W * H * 4字节的数组，按行优先存储所有像素的颜色值(32位)。每个像素是00rrggbb的形式，8位颜色。该设备支持lseek。屏幕大小从`/proc/dispinfo`文件中获得。
    * `/dev/tty`: 调试用的控制台(可选)。
    * `/dev/events`: 只可读的系统设备，从中读取系统内的输入事件。应用程序能从中读出以下事件(事件之间以换行符分隔)：
        * `t 1234`: 如果系统时间较上次读时发生变化(1/30s)，则返回系统启动后的时间，单位为毫秒。
        * `kd RETURN`: 按下按键，`ku A`: 松开按键。按键名称全部大写，名字同SDL扫描码名(参考nwm/native中的实现)。

2. Procfs文件系统: 所有的文件都是key-value pair，格式为` [key] : [value]`，冒号左右可以有任意多(0个或多个)的空白字符(whitespace)。

    * `/proc/cpuinfo`: CPU信息，用来显示。
    * `/proc/meminfo`: 内存信息，用来显示。
    * `/proc/dispinfo`: 屏幕信息，包含的keys：`WIDTH`，宽度，`HEIGHT`高度。


例如一个合法的 `/proc/dispinfo`文件的例子：

```
WIDTH : 640
HEIGHT:480
```
