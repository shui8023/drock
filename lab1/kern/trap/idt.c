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
#include <x86.h>

#define IRQ_IO1 0x20
#define IRQ_IO2 0xA1

/* 定义中断处理函数表 */
struct idt_entry idt_table[256]; 

/* IDTR */
struct idt_ptr idt_ptrs;

/* 中断处理函数的中间部分 */
interrupt_handler interrupt_handlers[256] = {0};

/* 加载IDT到寄存器IDTR中 */
extern void idt_flush(uint32_t ptr);

static void set_interrupt_gate(uint8_t , uint32_t, uint16_t, uint8_t);

/* 注册一个中断处理函数 */
void register_interrupt_handler(uint32_t n, interrupt_handler handler)
{
	interrupt_handlers[n] = handler;
}

void irq_handler(struct pt_regs *regs) 
{
	if (regs->int_nu >= 40) {
		outb(IRQ_IO2, 0x20);
	}
	outb(IRQ_IO1, 0x20);

	if (interrupt_handlers[regs->int_nu]) {
		interrupt_handlers[regs->int_nu](regs);
	}
}
/* 中断处理函数 */
void isr_handler(struct pt_regs *regs)
{
	
	printk("undefine interrput number:%d\n", regs->int_nu);

}


/* 设置中断向量表 */
static void set_interrupt_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
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
	
	idt_ptrs.limit = sizeof(struct idt_entry) * 256 - 1;
	idt_ptrs.base = (uint32_t)idt_table; 
	/* 初始化8259可编程芯片 */
	outb(IRQ_IO1, 0x11);
	outb(IRQ_IO2, 0x11);

	outb(IRQ_IO1 + 1, 0x20);
	outb(IRQ_IO2 + 1, 0x28);
	
	outb(IRQ_IO1 + 1, 0x04);
	outb(IRQ_IO2 + 1, 0x02);
	
	outb(IRQ_IO1 + 1, 0x01);
	outb(IRQ_IO2 + 1, 0x01);
	
	outb(IRQ_IO1 + 1, 0x0);
	outb(IRQ_IO2 + 1, 0x0);

	set_interrupt_gate(0,  (uint32_t)isr0,  0x08, 0x8E);  
	set_interrupt_gate(1,  (uint32_t)isr1,  0x08, 0x8E);
	set_interrupt_gate(2,  (uint32_t)isr2,  0x08, 0x8E);
	set_interrupt_gate(3,  (uint32_t)isr3,  0x08, 0x8E);
	set_interrupt_gate(4,  (uint32_t)isr4,  0x08, 0x8E);
	set_interrupt_gate(5,  (uint32_t)isr5,  0x08, 0x8E);
	set_interrupt_gate(6,  (uint32_t)isr6,  0x08, 0x8E);
	set_interrupt_gate(7,  (uint32_t)isr7,  0x08, 0x8E);
	set_interrupt_gate(8,  (uint32_t)isr8,  0x08, 0x8E);
	set_interrupt_gate(9,  (uint32_t)isr9,  0x08, 0x8E);
	set_interrupt_gate(10, (uint32_t)isr10, 0x08, 0x8E); 
	set_interrupt_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	set_interrupt_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	set_interrupt_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	set_interrupt_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	set_interrupt_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	set_interrupt_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	set_interrupt_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	set_interrupt_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	set_interrupt_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	set_interrupt_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	set_interrupt_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	set_interrupt_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	set_interrupt_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	set_interrupt_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	set_interrupt_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	set_interrupt_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	set_interrupt_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	set_interrupt_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	set_interrupt_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	set_interrupt_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	set_interrupt_gate(31, (uint32_t)isr31, 0x08, 0x8E);
	
	set_interrupt_gate(32, (uint32_t)irq0,   0x08, 0x8E);
	set_interrupt_gate(33, (uint32_t)irq1,   0x08, 0x8E);
	set_interrupt_gate(34, (uint32_t)irq2,   0x08, 0x8E);
	set_interrupt_gate(35, (uint32_t)irq3,   0x08, 0x8E);
	set_interrupt_gate(36, (uint32_t)irq4,   0x08, 0x8E);
	set_interrupt_gate(37, (uint32_t)irq5,   0x08, 0x8E);
	set_interrupt_gate(38, (uint32_t)irq6,   0x08, 0x8E);
	set_interrupt_gate(39, (uint32_t)irq7,   0x08, 0x8E);
	set_interrupt_gate(40, (uint32_t)irq8,   0x08, 0x8E);
	set_interrupt_gate(41, (uint32_t)irq9,   0x08, 0x8E);
	set_interrupt_gate(42, (uint32_t)irq10,  0x08, 0x8E);
	set_interrupt_gate(43, (uint32_t)irq11,  0x08, 0x8E);
	set_interrupt_gate(44, (uint32_t)irq12,  0x08, 0x8E);
	set_interrupt_gate(45, (uint32_t)irq13,  0x08, 0x8E);
	set_interrupt_gate(46, (uint32_t)irq14,  0x08, 0x8E);
	set_interrupt_gate(47, (uint32_t)irq15,  0x08, 0x8E);
	
	set_interrupt_gate(255, (uint32_t)isr255, 0x08, 0x8E);
	
	idt_flush((uint32_t)&idt_ptrs);
}

