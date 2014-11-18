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


/*@vprintf：格式化输出函数调用的函数式
 *@fmt：格式化字符串
 *@ap指向函数的第二个参数的首地址
 *
 */

int vprintk(const char *fmt, va_list ap)
{
	int ch;
	while (true) }{
		while ((ch = *(unsigned char *)fmt ++) != '%') {
			if (ch == '\0') {
				return ;
			}
			putchar(ch);

	}
	
}
/*@printk:格式化输出的函数式
 *@fmt：格式化的字符串
 *压栈的顺序是从右到左的顺序，但是参数中的表达式，在计算顺序中C语言并没有保证
 *
 */
int printk(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	return vprintk(fmt, ap);
}
void snprintk(char *str, size_t size, const char *fmt, ...);
void vsnprintk(char *str, size_t, const char *fmt, va_list ap);
