<head><meta charset="UTF-8"></head>
<style>
h1 {
    text-align: center;
    border-left: 5px solid #e86422;
    border-right: 5px solid #e86422;
}
h2 {
    border-left: 5px solid #ff7f00;
    padding-left: 10px;
}
h3 {
    border-left: 5px solid #e86422;
    padding-left: 8px;
}
h4 {
    border-left: 3px solid #f0a000;
    padding-left: 5px;
}
</style>

Release log:

本文参考: https://blog.csdn.net/niyaozuozuihao/article/details/91802994  
在此基础上有些删减

# gdb 使用方法整理(基础篇)
最近想要学习 Linux 内核，但是如果单纯的通过看书和代码来学习，会显得很枯燥，并且有些地方不容易理解。所以决定使用 qemu + gdb 的方式来跟进内核代码流程。关于怎么使用 qemu + gdb，可以 [点击这里](https://blog.csdn.net/weixin_40407199/article/details/115808274?spm=1001.2014.3001.5502)

为了能够更高效的使用 gdb 跟进代码，需要重新整理一下 gdb 的使用方法。因为本人之前对 gdb 有一定了解，这里的主要目标是做一个知识的整理方便以后查询，不会细讲。新手请忽略本文


## 程序断点设置
设置断点的常规用法: `b(break 的简写) + 行号` 或者 `b + 函数名`(同名函数会被同时标记)  
如果有多个文件，可以使用: `b + 文件名:行号` 或者 `b + 文件名:函数名` 或者 `b + 函数名:行号`  
查看断点信息: `info breakpoints`  
删除断点: `d(delete 的简写) num` 或者 `d num1-num2` 或者 `d breakpoints`  
删除某行的断点: `clear + 行号`  
删除某个函数的所有断点: `clear + 函数名`  
暂停/开启某个断点: `disable/enable + num`  

## 程序的执行
run(简写为 r): 执行程序直到遇到断点或结束  
continue(简写为 c): 继续执行，直到遇到下一个断点或结束  
next(简写为 n): 单步跟踪程序，当遇到函数调用时，不进入此函数体  
step(简写为 s): 单步跟踪程序，当遇到函数调用时，进入函数  
until: 运行程序直到退出循环体  
until + 行号:  运行至某行  
finish: 运行程序，直到当前函数完成返回，并打印函数返回时的堆栈地址和返回值及参数值等信息  
call 函数(参数): 调用程序中可见的函数，并传递“参数”，如：call gdb_test(55)  
quit(简写为 q): 退出gdb  

## 查看源码
查看源码的常用命令: `l` 或者 `l + 行号` 或者 `l + 函数名`

## 查看运行信息
print + 表达式: 简写为 p，表达式可以是任何有效表达式，比如变量、函数调用等  
display + 表达式: 在单步运行时将非常有用，使用display命令设置一个表达式后，它将在每次单步进行指令后，紧接着输出被设置的表达式及值  
watch 表达式: 设置一个监视点，一旦被监视的“表达式”的值改变，gdb 将强行终止正在被调试的程序。如： watch a  
whatis: 查询变量或函数  
info function: 查询函数  
info locals: 显示当前堆栈页的所有变量  

where/bt: 当前运行的堆栈列表  
bt backtrace: 显示当前调用堆栈  
up/down: 改变堆栈显示的深度  
set args 参数: 指定运行时的参数  
show args: 查看设置好的参数  
info program: 来查看程序的是否在运行，进程号，被暂停的原因  

## 分割窗口
layout: 用于分割窗口，可以一边查看代码，一边测试  
layout src: 显示源代码窗口  
layout asm: 显示反汇编窗口  
layout regs: 显示源代码/反汇编和CPU寄存器窗口  
layout split: 显示源代码和反汇编窗口  

Ctrl + L: 刷新窗口  
Ctrl + x，再按 1: 单窗口模式，显示一个窗口  
Ctrl + x，再按 2: 双窗口模式，显示两个窗口  
Ctrl + x，再按 a: 回到传统模式，即退出 layout  

## cgdb强大工具
cgdb主要功能是在调试时进行代码的同步显示，这无疑增加了调试的方便性，提高了调试效率。界面类似vi，符合unix/linux下开发人员习惯;如果熟悉gdb和vi，几乎可以立即使用cgdb

## 远程调试
在目标设备上运行: $ gdbserver 192.168.0.123:6666 ./test  
在调试机器上运行 gdb，并在 gdb 命令行中建立连接: (gdb) gdb remote 192.168.0.123:6666  
必要的时候需要指定符号表和目标系统库文件  
```
(gdb) file ./test
(gdb) set solib-search-path /home/oem/tools/arm-linux-gnueabi/libc/lib/

```


## 未讲的
对于一些复杂的程序，通常会涉及到多线程或者子进程。对于这些情况后续待补充

