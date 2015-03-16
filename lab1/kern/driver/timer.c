/*
 * =====================================================================================
 *
 *       Filename:  timer.c
 *
 *    Description:  初始化8254可编程芯片
 *
 *        Version:  1.0
 *        Created:  2015年02月14日 19时57分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include <idt.h>
#include <timer.h>
#include <x86.h>
#include <defs.h>
#include <stdio.h>

/* 定义时钟中断函数 */
void handler_timer(struct pt_regs *regs)
{
//	printk("hellow\n");
}

/* 初始化8354可编程芯片 */
void init_timer(uint32_t frequency)
{
	/* 注册时钟中断函数 */
	register_interrupt_handler(IRQ0, handler_timer);
	
	uint32_t divisor = 1193180 / frequency;

	outb(0x43, 0x36);
	
	uint8_t low = (uint8_t)(divisor & 0xFF);
	uint8_t hight = (uint8_t)((divisor >> 8) & 0xFF);

	outb(0x40, low);
	outb(0x40, hight);
}
