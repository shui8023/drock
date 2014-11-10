/*
 * =====================================================================================
 *
 *       Filename:  x86.h
 *
 *    Description:  一些汇编代码的封装
 *
 *        Version:  1.0
 *        Created:  2014年11月03日 17时03分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef X86_H
#define X86_H

#include "defs.h"

static inline uint8_t inb(uint16_t port) __attribute__((always_inline));
static inline void outb(uint16_t port, uint8_t data) __attribute__((always_inline));
static inline void insl(uint32_t port, void *addr, int cnt) __attribute__((always_inline));

/*封装了inb这个指令
 *
 */
static inline uint8_t
inb(uint16_t port) 
{
	uint8_t data;
	asm volatile ("inb %1, %0" : "=a" (data) : "d" (port));

	return data;
}

static inline void 
outb(uint16_t port, uint8_t data)
{
	asm volatile ("outb %0, %1" :: "a" (data), "d" (port));
}

static inline void 
insl(uint32_t port, void *addr, int cnt)
{
	asm volatile (
		"cld;"
		"repne; insl;"
		: "=D" (addr), "=c" (cnt)
		: "d" (port), "0" (addr), "1"(cnt)
		: "memory", "cc");
}

#endif //X86_H
