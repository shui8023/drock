/*
 * =====================================================================================
 *
 *       Filename:  debug.c
 *
 *    Description:  打印kernel函数栈的信息和kernel的基本信息
 *
 *        Version:  1.0
 *        Created:  2015年01月25日 12时46分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include <debug.h>
#include <assert.h>
#include <elf.h>
#include <stdio.h>



/*function：打印内核的基本信息
 *计算kernel在内存的大小
 *
 */
void inline print_kerninfo(void)
{
	extern char end[], edata[], kern_start[], etext[];
	printk("    start:\t%x(phys)\n", kern_start);
	printk("    etext:\t%x(phys)\n", etext);
	printk("    edata:\t%x(phys)\n", edata);
	printk("      end:\t%x(phys)\n", end);
	/* 加上1023是为了向上取整 */
	printk("the kernel  memory in used: %d KB\n", (end - kern_start + 1023) / 1024);
}



/*打印drock的栈信息
 *
 *
 */
void print_stackframe(void)
{

}
