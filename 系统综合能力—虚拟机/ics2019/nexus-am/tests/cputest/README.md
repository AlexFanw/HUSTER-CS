# CPUTest

批量编译大量独立的测试小程序。

约定：**程序最终执行到`_halt(0)`为正确，其他情况为错误**。

用途：

* 配合一键仿真程序在CPU实现修改后快速进行回归测试。
* 为一键上板提供可运行的ELF binary。

## 编译测试程序

使用`make ARCH=native`用`native`体系结构编译所有测试程序。

如果需要单独编译一个程序，可以使用`make ARCH=mips32-minimal ALL=sum`，单独编译`sum`。

可以通过`make ARCH=x86-nemu run`进行批量测试，需要相应arch中的run脚本在一个测试成功后可以自动退出。

## 添加新的测试程序

每个测试程序只能有一个C文件，放在`tests/`目录下。

`trap.h`里有一些可以使用的函数，比如`nemu_assert`。



