/*
 * =====================================================================================
 *
 *       Filename:  stdio.h
 *
 *    Description:  标准io的库函数
 *
 *        Version:  1.0
 *        Created:  2014年11月13日 23时25分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef STDIO_H
#define STDIO_H

#include <defs.h>
#include <stdarg.h>

/* kern/libs/stdio.c 输出的部分*/
int printk(const char *fmt, ...);
int vprintk(const char *fmt, va_list ap);
void putchar(int c);
int puts(const char *str);
void snprintk(char *str, size_t size, const char *fmt, ...);
void vsnprintk(char *str, size_t, const char *fmt, va_list ap);


#endif //STDIO_H

