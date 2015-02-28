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

#include <console.h>
#include <defs.h>
#include <x86.h>
#include <kbdreg.h>
#include <idt.h>


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
	crt_buff = (int16_t *)CGA_BUFFER;
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



#define NO 	0

#define SHIFT  		(1<<0)
#define CTL 		(1<<1)
#define ALT 		(1<<2)

#define CAPSLOCK 	(1<<3)
#define NUMLOCK 	(1<<4)
#define SCROLLLOCK 	(1<<5)

#define EOESC  		(1<<6)

static uint8_t shiftcode[256] = {
	[0x1D] CTL,
	[0x2A] SHIFT,
	[0x36] SHIFT,
	[0x38] ALT,
	[0x9D] CTL,
	[0xB8] ALT
};

static uint8_t togglecode[256] = {
	[0x3A] CAPSLOCK,
	[0x45] NUMLOCK,
	[0x46] SCROLLLOCK
};


static uint8_t normalmap[256] = {
    NO,   0x1B, '1',  '2',  '3',  '4',  '5',  '6',  // 0x00
    '7',  '8',  '9',  '0',  '-',  '=',  '\b', '\t',
    'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',  // 0x10
    'o',  'p',  '[',  ']',  '\n', NO,   'a',  's',
    'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  // 0x20
    '\'', '`',  NO,   '\\', 'z',  'x',  'c',  'v',
    'b',  'n',  'm',  ',',  '.',  '/',  NO,   '*',  // 0x30
    NO,   ' ',  NO,   NO,   NO,   NO,   NO,   NO,
    NO,   NO,   NO,   NO,   NO,   NO,   NO,   '7',  // 0x40
    '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
    '2',  '3',  '0',  '.',  NO,   NO,   NO,   NO,   // 0x50
    [0xC7] KEY_HOME,    [0x9C] '\n' /*KP_Enter*/,
    [0xB5] '/' /*KP_Div*/,  [0xC8] KEY_UP,
    [0xC9] KEY_PGUP,    [0xCB] KEY_LF,
    [0xCD] KEY_RT,      [0xCF] KEY_END,
    [0xD0] KEY_DN,      [0xD1] KEY_PGDN,
    [0xD2] KEY_INS,     [0xD3] KEY_DEL
};

static uint8_t shiftmap[256] = {
    NO,   033,  '!',  '@',  '#',  '$',  '%',  '^',  // 0x00
    '&',  '*',  '(',  ')',  '_',  '+',  '\b', '\t',
    'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',  // 0x10
    'O',  'P',  '{',  '}',  '\n', NO,   'A',  'S',
    'D',  'F',  'G',  'H',  'J',  'K',  'L',  ':',  // 0x20
    '"',  '~',  NO,   '|',  'Z',  'X',  'C',  'V',
    'B',  'N',  'M',  '<',  '>',  '?',  NO,   '*',  // 0x30
    NO,   ' ',  NO,   NO,   NO,   NO,   NO,   NO,
    NO,   NO,   NO,   NO,   NO,   NO,   NO,   '7',  // 0x40
    '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
    '2',  '3',  '0',  '.',  NO,   NO,   NO,   NO,   // 0x50
    [0xC7] KEY_HOME,    [0x9C] '\n' /*KP_Enter*/,
    [0xB5] '/' /*KP_Div*/,  [0xC8] KEY_UP,
    [0xC9] KEY_PGUP,    [0xCB] KEY_LF,
    [0xCD] KEY_RT,      [0xCF] KEY_END,
    [0xD0] KEY_DN,      [0xD1] KEY_PGDN,
    [0xD2] KEY_INS,     [0xD3] KEY_DEL
};

#define C(x) (x - '@')

static uint8_t ctlmap[256] = {
    NO,      NO,      NO,      NO,      NO,      NO,      NO,      NO,
    NO,      NO,      NO,      NO,      NO,      NO,      NO,      NO,
    C('Q'),  C('W'),  C('E'),  C('R'),  C('T'),  C('Y'),  C('U'),  C('I'),
    C('O'),  C('P'),  NO,      NO,      '\r',    NO,      C('A'),  C('S'),
    C('D'),  C('F'),  C('G'),  C('H'),  C('J'),  C('K'),  C('L'),  NO,
    NO,      NO,      NO,      C('\\'), C('Z'),  C('X'),  C('C'),  C('V'),
    C('B'),  C('N'),  C('M'),  NO,      NO,      C('/'),  NO,      NO,
    [0x97] KEY_HOME,
    [0xB5] C('/'),      [0xC8] KEY_UP,
    [0xC9] KEY_PGUP,    [0xCB] KEY_LF,
    [0xCD] KEY_RT,      [0xCF] KEY_END,
    [0xD0] KEY_DN,      [0xD1] KEY_PGDN,
    [0xD2] KEY_INS,     [0xD3] KEY_DEL
};

static uint8_t *charcode[4] = {
    normalmap,
    shiftmap,
    ctlmap,
    ctlmap
};


 
void init_input()
{
	register_interrupt_handler(IRQ1, console_getc);
}
void console_getc(struct pt_regs * regs) 
{
	
}
