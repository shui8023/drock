/*
 * =====================================================================================
 *
 *       Filename:  console.c
 *
 *    Description:  IO端口的输入输出设置
 *
 *        Version:  1.0
 *        Created:  2014年11月14日 21时31分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include "console.h"
#include "defs.h"
#include "x86.h"

#define CGA_BUFFER 		0xb8000
#define CGA_BASE 		0x3D4
#define CRT_ROWS 		25
#define CRT_COLS 		80
#define CRT_SIZE 		(CRT_ROWS * CRT_COLS)

static int16_t *crt_buff;
static int16_t crt_pos;

/*@cga_init:输出端口的初始化
 *
 *
 */
static void cga_init (void)
{
	crt_buff = (uint16_t *)CGA_BUFFER;
	int i = 0;

	for (i = 0; i < CRT_SIZE; ++i) {
		crt_buff[i] = 0x700 | ' ';
	}

	outb(CGA_BASE, 14); 			//告诉VGA，我们要设置光标的高字节
	outb(CGA_BASE + 1, crt_pos >> 8); 	//发送高8位
	outb(CGA_BASE, 15); 			//告诉VGA，我们要设置光标的低字节
	outb(CGA_BASE + 1, crt_pos); 		//发送低8位
}

static void cga_putc(int c)
{
	crt_buff = (uint16_t *)CGA_BUFFER;
	if (!(c & ~ 0xFF)) {
		c |= 0x700;
	}

	switch (c & 0xFF) {
	case '\b':
		if (crt_pos > 0) {
			crt_pos --;
			crt_buff[crt_pos] = (c & 0xFF) | ' ';
		}
		break;
	case '\t': 
		crt_pos += 8;
		break;
	case '\n':
		crt_pos += CRT_COLS; 			//换行符，就是回到一行的开头
	case '\r':
		crt_pos -= (crt_pos % CRT_COLS);
		break;
	default:
		crt_buff[crt_pos++] = c;
		break;
	}
	//满屏的处理的方法,滚屏
	if (crt_pos >= CRT_SIZE) {
		int i = 0;
		for (i = 0; i <= CRT_COLS * (CRT_ROWS - 1); ++i) {
			crt_buff[i] = crt_buff[i + CRT_COLS];
		}

		for (i = (CRT_ROWS - 1) * CRT_COLS; i <= CRT_COLS * CRT_COLS; ++i) {
			crt_buff[i] = 0x700 |' ';
		}
		crt_pos -= CRT_COLS;
	}

	outb(CGA_BASE, 14); 			//告诉VGA，我们要设置光标的高字节
	outb(CGA_BASE + 1, crt_pos >> 8); 	//发送高8位
	outb(CGA_BASE, 15); 			//告诉VGA，我们要设置光标的低字节
	outb(CGA_BASE + 1, crt_pos); 		//发送低8位
	
}

/*@console_init:进行输入输出的初始化
 *
 *
 */
void console_init(void)
{
	cga_init();
}

/*@console_putc：输出一个字符
 *@c：要输出的字符c
 *@c：为什么要用整型，要存储这个字符的前景色和背景色
 */
void console_putc(int c)
{
	cga_putc(c);
}
