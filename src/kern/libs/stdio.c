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
#include "console.h"

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

/*@getint 获得有符号类型的整型的值，从栈的列表中
 *
 *@ap： 栈的指针
 *@lfag：ap指向的数值的大小
 */
static long long getint(va_list *ap, int lflag) 
{
	if (lflag >= 2) {
		return va_arg(*ap, long long);
	} else if (lflag) {
		return va_arg(*ap, long);
	} else {
		return va_arg(*ap, int);
	}
}


/*@getuint 获得无符号类型的整型的值，从栈的列表中
 *
 *@ap： 栈的指针
 *@lfag：ap指向的数值的大小
 */
static long long getuint(va_list *ap, int lflag) 
{
	if (lflag >= 2) {
		return va_arg(*ap, unsigned long long);
	} else if (lflag) {
		return va_arg(*ap, unsigned long);
	} else {
		return va_arg(*ap, unsigned int);
	}
}



/*@vprintf：格式化输出函数调用的函数式
 *@fmt：格式化字符串
 *@ap指向函数的第二个参数的首地址
 *
 */

int vprintk(const char *fmt, va_list ap)
{
	int ch;
	int count;
	int base; 	//输出的机制
	char padc; 	
	unsigned long long num; 	//表示要打印的
	int width, lfag, altflag;
	int precison;
	while (true) {
		while ((ch = *(unsigned char *)fmt ++) != '%') {
			if (ch == '\0') {
				return ;
			}
			count++;
			putchar(ch);
		}
		padc = ' ';
		width = precison = -1;
		lfag = altflag = 0;
		while (true) {
			switch(ch = *(unsigned char *)fmt ++) {
			case '-':
				padc = '-';
				break;
			case '0':
				padc = '0';
				break;
			case '*':
				precison = va_arg(ap, int);
				if (width < 0) {
					width = precison;
					precison = -1;
				}
				break;
			case '1' ... '9':
				for (precison = 0; ; ++fmt) {
					precison = precison * 10 + ch - '0';
					ch = *fmt;
					if (ch < '0' || ch > '9') {
						break;
					}
				}
				if (width < 0) {
					width = precison;
					precison = -1;
				}
				break;
			case '#':
				altflag = 1;
				break;
			case '.':
				if (width < 0) {
					width = 0;
				}
				break;
			//long long int
			case 'l':
				lfag++;
				break;
			//character
			case 'c':
				putchar(va_arg(ap, int));
				break;
			}
			case 'd':
				num = getint(&ap, lfag);
				if ((long long)num < 0 ) {
					putchar('-');
					num = -(long long) num;
				}
				base = 10;
				;输出函数
				break;
			case 'u':
				num = getuint(&ap, lfag);
				base = 10;
				;输出函数
				break;
			case 'o':
				num = getuint(&ap, lfag);
				base = 8;
				;输出函数
				break;
			case 'x':
				putchar('0');
				putchar('x');
				num = getuint(&ap, lfag);
				;输出函数
				break;
			case 'p':
				putchar('0');
				putchar('x');
				num = (unsigned long long)va_arg(ap, void *);
				base = 16;
				;输出函数
				break;
			case '%':
				putchar(ch);
				break;
			default:
				putchar(ch);
				for (fmt--; fmt[-1] != '%'; --fmt) {
					putchar();
				}

		}
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
