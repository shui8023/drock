/*
 * =====================================================================================
 *
 *       Filename:  idt.c
 *
 *    Description:  中断服务程序处理
 *
 *        Version:  1.0
 *        Created:  2015年02月03日 23时25分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include <defs.h>
#include <idt.h>
#include <stdio.h>
#include <string.h>

/* 定义中断处理函数表 */
struct idt_entry idt_table[256]; 

/* IDTR */
struct idt_ptr idt_ptrs;

/* 中断处理函数的中间部分 */
interrupt_handler interrupt_handlers[256];

/* 中断处理函数 */
void isr_handler(struct pt_regs * regs)
{

}


/* 设置中断向量表 */
static void set_interrupt_gate(uint8_t num, uin32_t base, uint16_t sel, uint8_t flags)
{
	idt_table[num].base_lo = base & 0xFFFF;
	idt_table[num].base_hi = (base >> 16) & 0xFFFF;
	idt_table[num].sel = sel;
	idt_table[num].always0 = 0;
	idt_table[num].flags = flags;
}
/* 初始化中断处理 */
void init_idt(void)
{
	bzero(interrupt_handlers, sizeof(interrupt_handler)*256);
	
	idt_ptrs.limit = sizeof(struct idt_entry) * 256 - 1;
	idt_ptrs.base = (uint32_t)idt_tables;
set_interrupt_gate(0,      	 0, 
set_interrupt_gate(1,            1,
set_interrupt_gate(2,            2,
set_interrupt_gate(3,            3,
set_interrupt_gate(4,            4,
set_interrupt_gate(5,            5,
set_interrupt_gate(6,            6,
set_interrupt_gate(7,            7,
set_interrupt_gate(8,            8,
set_interrupt_gate(9,            9,
set_interrupt_gate(10,   	10, 
set_interrupt_gate(11,   	11,
set_interrupt_gate(12,   	12,
set_interrupt_gate(13,   	13,
set_interrupt_gate(14,   	14,
set_interrupt_gate(15,   	15,
set_interrupt_gate(16,   	16,
set_interrupt_gate(17,   	17,
set_interrupt_gate(18,   	18,
set_interrupt_gate(19,   	19,
set_interrupt_gate(20,   	20,
set_interrupt_gate(21,   	21,
set_interrupt_gate(22,   	22,
set_interrupt_gate(23,   	23,
set_interrupt_gate(24,   	24,
set_interrupt_gate(25,   	25,
set_interrupt_gate(26,   	26,
set_interrupt_gate(27,   	27,
set_interrupt_gate(28,   	28,
set_interrupt_gate(29,   	29,
set_interrupt_gate(30,   	30,
set_interrupt_gate(31,   	31,
}

