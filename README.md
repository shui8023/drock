drock
=====

###the simple X86 os


   
 - lab1：基本的输入输出,打印栈信息，中断，物理内存管理
 
     关于该项目的**目录**
	>>doc:项目中遇见的一些问题的记录和解决问题的方法

    >boot/
    >>kernel的bootloader，从实模式到保护模式，用于引导加载drock到内存中。

    >kern/
    >>实现基本的输入输出，打印栈信息，中断处理，物理内存管理
    
    >lib/
    >>相关的库函数头文件
    
    >Makefile
    >>用于编译链接执行drock
    
    >tool/
    >>链接脚本，bootloader的辅助生成文件
    
