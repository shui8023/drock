/*
 * =====================================================================================
 *
 *       Filename:  stdio.c
 *
 *    Description:  输入输出函数的定义与实现
 *
 *        Version:  1.0
 *        Created:  2014年11月17日 20时45分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include <stdarg.h>
#include <stdio.h>
#include <console.h>

/*@putchar:显示一个字符，默认颜色为黑底白字
 *@v， 要输出的字符
 *
 */
void putchar(int c)
{
	console_putc(c);
}
/*@puts：要输出一个字符串
 *@str, 要输出字符串的首地址
 *
 */
int puts(const char *str)
{
	int count = 0;
	char c;

	while ((c = *str ++) != '\0') {
		console_putc(c);
		count++;
	}

	return count;
}
int printk(const char *fmt, ...);
int vprintk(const char *fmt, va_list ap);
void snprintk(char *str, size_t size, const char *fmt, ...);
void vsnprintk(char *str, size_t, const char *fmt, va_list ap);
