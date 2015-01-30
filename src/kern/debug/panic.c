/*
 * =====================================================================================
 *
 *       Filename:  panic.c
 *
 *    Description:  打印出错误的处理函数
 *
 *        Version:  1.0
 *        Created:  2015年01月27日 19时46分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include <assert.h>
#include <stdio.h>
#include <defs.h>
#include <stdarg.h>


void __panic(const char *filename, int line, const char *fmt, ...) 
{
	va_list ap;
	va_start(ap, fmt);
	printk("kernel panic %s:%d:\n", filename, line);
	vprintk(fmt, ap);
	printk("\n");
	va_end(ap);
}
