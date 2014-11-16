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
#include <x86.h>

#define CGA_BUFFER 		0xb8000
#define CGA_BASE 		0x3D4
#define CRT_ROWS 		25
#define CRT_COLS 		80
#define CRT_SIZE 		(CRT_ROWS * CRT_COLS)

static uint16_t *crt_buff;
static uint16_t crt_pos;




/*
 *IO端口初始化的，
 *
 */
void console_init(void)
{
	crt_buff = (uint16_t *)CGA_BUFFER;

	outb();
}



