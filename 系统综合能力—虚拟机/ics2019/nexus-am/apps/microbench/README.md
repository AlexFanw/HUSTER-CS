# MicroBench

CPU正确性和性能测试用基准程序。对AbstractMachine的要求：

1. 需要实现TRM和IOE的API。
2. 在IOE的全部实现均留空的情况下仍可运行。如果有正确实现的`_uptime()`，可以输出正确的统计时间。若这个函数没有实现(返回`0`)，仍可进行正确性测试。
3. 使用`_putc(ch)`输出。
4. 堆区`_heap`必须初始化(堆区可为空)。如果`_heap.start == _heap.end`，即分配了空的堆区，只能运行不使用堆区的测试程序。每个基准程序会预先指定堆区的大小，堆区不足的基准程序将被忽略。

## 使用方法

同一组程序分成三组：test，train和ref。
test数据规模很小，作为测试用，不计时不评分。
train数据规模中等，可用于在仿真环境研究微结构行为，计时不评分。
ref数据规模较大，作为衡量CPU性能用，计时并评分。

默认运行ref数据规模，使用`make run mainargs=test`运行test数据规模，使用`make run mainargs=train`运行train数据规模。

## 评分根据

每个benchmark都记录以`REF_CPU`为基础测得的运行时间微秒数。每个benchmark的评分是相对于`REF_CPU`的运行速度，与基准处理器一样快的得分为`REF_SCORE=100000`。

所有benchmark的平均得分是整体得分。

## 已有的基准程序

| 名称    | 描述                                   | ref堆区使用  |
| ----- | ------------------------------------ | ----- |
| qsort | 快速排序随机整数数组                           | 640KB |
| queen | 位运算实现的n皇后问题                          | 0     |
| bf    | Brainf**k解释器，快速排序输入的字符串              | 32KB  |
| fib   | Fibonacci数列f(n)=f(n-1)+…+f(n-m)的矩阵求解 | 256KB |
| sieve | Eratosthenes筛法求素数                    | 2MB   |
| 15pz  | A*算法求解4x4数码问题                        | 2MB   |
| dinic | Dinic算法求解二分图最大流                      | 1MB   |
| lzip  | Lzip数据压缩                             | 4MB   |
| ssort | Skew算法后缀排序                           | 4MB   |
| md5   | 计算长随机字符串的MD5校验和                      | 16MB  |

## 增加一个基准程序`foo`

在`src/`目录下建立名为`foo`的目录，将源代码文件放入。

每个基准程序需要实现三个函数：

* `void bench_foo_prepare();`：进行准备工作，如初始化随机数种子、为数组分配内存等。运行时环境不保证全局变量和堆区的初始值，因此基准程序使用的全局数据必须全部初始化。
* `void bench_foo_run();`：实际运行基准程序。只有这个函数会被计时。
* `int bench_foo_validate();`：验证基准程序运行结果。正确返回1，错误返回0。

在`benchmark.h`的`BENCHMARK_LIST`中增加相应的`def`项，格式参考已有的benchmark。

## 基准程序可以使用的库函数

虽然klib中提供了一些函数，但使用它们可能会导致在不同平台上的性能不准确。

* `bench_memcpy(void *dst, const void *src, size_t n)`: 内存复制。
* `bench_srand(uint seed)`：用seed初始化随机数种子。
* `bench_rand()`：返回一个0..32767之间的随机数。
* `bench_alloc`/`bench_free`：内存分配/回收。目前回收是空操作。

