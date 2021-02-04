# C运行库

从newlib-3.0.0.20180831移植。

编译后得到archive file，应用程序与libc和libos静态链接后即可执行。

## 裁剪与修改

* 移除了以下模块
  * iconv  machine  stdio64  sys  xdr
* 移除posix/目录下的execve.c, 解决execve()重复定义导致的链接不确定性问题(另一处定义在syscalls/sysexecve.c中)
  * 并将以下文件中的\_execve()调用改为execve(), 这样可以统一经过_execve_r()
    * execl.c  execle.c  exelp.c  execv.c  execvp.c  posix_spawn.c stdlib/system.c
* 移除posix/目录下的isatty.c, 解决isatty()重复定义的问题(另一处定义在syscalls/sysisatty.c中)
* 修改了部分头文件的包含方式与路径, 使其找到正确的文件
* 使用newlib/libc/sys/sysvi386/sys/目录下的头文件来获取正确的结构体和宏定义, 包括
  * dirent.h  stat.h  termios.h  utmp.h
* 将用于模板功能的.c文件后缀修改为.t, 避免被Navy-apps的Makefile编译脚本重复编译
  * posix/engine.c -> posix/engine.t
* 原版newlib Makefile.am中包含从一个模板.c文件编译出多个目标文件的若干规则, 为了模拟这些规则, 我们将模板.c文件的后缀修改为.t, 然后创建若干.c文件, 在其中定义相应的宏, 然后包含.t文件. 每个这样的.c文件将会被编译成相应的目标文件, 与Makefile.am中的规则对应. 具体请参考原版newlib中相应的Makefile.am文件. 这些改动有:
  * stdio/vfprintf.c -> stdio/vfprintf.t
    * 创建svfiprintf.c  svfprintf.c  vfiprintf.c  vfprintf.c
  * stdio/vfscanf.c -> stdio/vfscanf.t
    * 创建svfiscanf.c  svfscanf.c  vfiscanf.c  vfscanf.c
  * stdlib/mallocr.c -> stdlib/mallocr.t
    * 创建callocr.c  cfreer.c  freer.c  malignr.c  mallinfor.c  mallocr.c  malloptr.c  mallstatsr.c  msizer.c  pvallocr.c  reallor.c  vallocr.c
* 添加platform/crt0.c和platform/cpp.cpp
* 添加platform/setjmp/目录和支持的体系结构

## 与操作系统的接口

libc会使用系统调用实现自身无法完成的功能。系统调用在libos中定义：

```
_open()
_close()
_read()
_write()
_sbrk()
...
```

## Bug

目前能成功编译并运行pal, 但用到其它库函数时, 预计会发生链接错误.
