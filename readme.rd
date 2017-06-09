说明：
nbench是一个开源CPU benchmark工具，通过运算如下的10个项目，
考察CPU单任务下的整数，浮点和内存性能。通过这个测试，可以很
好的反映出CPU的单核心性能。

由于现在的CPU大多是多核心多线程的，并且我们使用的服务器大多
是多路CPU的，为了测试系统的总处理能力，便于做比较，我在nbench
的基础上开发了nbench_mt (multi-task).  把nbench的各种算法
函数改为可以支持多线程运行的方式，在改的过程中发现Neural Net
依赖太多的全局变量，所以丢掉了这个项目，余下的9个项目做了保留，
并按照测试项目考察的是整数，浮点还是内存性能重新排了顺序。

nbench计算成绩的方式比较严谨，是调用clock()函数的，这样获得的
时间是进程真正占用CPU的时间，对于计算单核心CPU的性能比较准确。
nbench_mt由于是多线程方式运行的，所以用的是gettimeofday方式，
获得的是客观流逝的时间，这样做的理由是多个线程一起工作，我们
要考察的是在单位客观时间内一共能做多少事情。

发现编译器的版本对测试结果有比较明显的影响，另外-O3优化编译的
测试结果几乎是没有-O3的2倍。
为了测试的公平，建议用同一个编译版本的程序的结果做比较才有可比性。



Compile:
make nbench_mt

Usage: 
./nbench_mt [thread count] [duration per algorithm] {specified algorithm 0~8}

Example1:
$ ./nbench_mt 1 10
=====================  Benchmark  ======================
Number of Threads   : 1
---------------------  Progress   ----------------------
Algorithm           : Iterations/sec  : Time Elapse     
--------------------------------------------------------
NUMERIC SORT        :          600.319:           11.351
FP EMULATION        :          130.375:           10.048
IDEA                :         1997.352:           10.005
HUFFMAN             :          961.942:           10.084
FOURIER             :         6576.814:           10.105
LU DECOMPOSITION    :          394.288:           10.196
STRING SORT         :           66.593:           10.452
BITFIELD            :    199293839.268:           10.302
ASSIGNMENT          :           10.438:           19.161
----------------------   INDEX   -----------------------
INTEGER INDEX       :            0.415
FLOATING-POINT INDEX:            0.243
MEMORY INDEX        :            0.245
OVERALL INDEX       :            0.309
--------------------- CPU INFO -------------------------
CPU                 : 4 CPU ARMv7 Processor rev 4 (v7l)
L2 Cache            : 
OS                  : Linux 4.4.50-v7+
========================================================

Example2:
$ ./nbench_mt 4 10
=====================  Benchmark  ======================
Number of Threads   : 4
---------------------  Progress   ----------------------
Algorithm           : Iterations/sec  : Time Elapse     
--------------------------------------------------------
NUMERIC SORT        :         2403.674:           11.392
FP EMULATION        :          518.685:           10.102
IDEA                :         7959.877:           10.018
HUFFMAN             :         3827.147:           10.086
FOURIER             :        26141.814:           10.169
LU DECOMPOSITION    :         1491.533:           10.305
STRING SORT         :          267.288:           10.461
BITFIELD            :    793959503.459:           10.338
ASSIGNMENT          :           36.379:           19.242
----------------------   INDEX   -----------------------
INTEGER INDEX       :            1.654
FLOATING-POINT INDEX:            0.943
MEMORY INDEX        :            0.935
OVERALL INDEX       :            1.207
--------------------- CPU INFO -------------------------
CPU                 : 4 CPU ARMv7 Processor rev 4 (v7l)
L2 Cache            : 
OS                  : Linux 4.4.50-v7+
========================================================

