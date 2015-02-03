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
struct idt_entry {
	uint16 base_lo;
	uint16 sel;
	uint8 always0;
	uint8 flags;
	uint16 base_hi;
}__attribute__((packed));
struct idt_ptr {

}__attribute__((packed));
#endif /* __KERN_TRAP_IDT_H__ */
