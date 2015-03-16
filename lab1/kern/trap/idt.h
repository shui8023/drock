/*
 * =====================================================================================
 *
 *       Filename:  idt.h
 *
 *    Description:  中断向量
 *
 *        Version:  1.0
 *        Created:  2015年02月03日 23时24分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef __KERN_TRAP_IDT_H__
#define __KERN_TRAP_IDT_H__

#include <defs.h>

/*中断描述符 */
struct idt_entry {
	uint16_t base_lo; 	//中断处理函数地址的0-15位
	uint16_t sel; 		//目标代码段段选择子
	uint8_t always0; 		//置0段
	uint8_t flags; 		//标志
	uint16_t base_hi; 	//中断处理函数地址的16-31位
}__attribute__((packed));

/*IDTR中断描述符表寄存器 */
struct idt_ptr {
	uint16_t limit; 		//限长
	uint32_t base;  		//基址
}__attribute__((packed));

/* 要保存的寄存器的值*/
struct pt_regs {
	uint32_t edi; 		//pusha 从edi到eax压栈
	uint32_t esi;
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
	uint32_t gs;
	uint32_t fs;
	uint32_t es;
	uint32_t ds;
	uint32_t int_nu; 		//中断号
	uint32_t err_code; 	//错误代码，由错误代码的中断会压入错误代码到栈中
	uint32_t eip; 		//ip, cs. flags 由系统自动压栈
	uint32_t cs;
	uint32_t eflags;
	uint32_t useresp; 
	uint32_t ss;
} __attribute__((packed));

/* 定义中断处理函数指针 */
typedef void (*interrupt_handler)(struct pt_regs *regs);

/* 注册一个中断处理函数 函数原型 */
void register_interrupt_handler(uint32_t n, interrupt_handler handler);

/* 调用中断处理函数 */
void isr_handler(struct pt_regs *regs);

void init_idt(void);
/* 中断处理函数 */
void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10(); 
void isr11();
void isr12();
void isr13();
void isr14();
void isr15();
void isr16();
void isr17();
void isr18();
void isr19();
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();

void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();

void isr255();

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47


#endif /* __KERN_TRAP_IDT_H__ */
