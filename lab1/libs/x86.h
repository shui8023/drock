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

#define do_div(n, base) ({  					\
	unsigned long __upper, __low, __high, __mod, __base; 	\
	__base = (base); 					\
	asm("" :"=a" (__low), "=d" (__high) : "A" (n)); 	\
	__upper = __high; 					\
	if (__high != 0) { 					\
		__upper = __high % __base; 			\
		__high = __high / __base; 			\
	} 							\
	asm("divl %2" : "=a" (__low), "=d" (__mod) 		\
	    : "rm" (__base), "0" (__low), "1" (__upper)); 	\
	asm("" : "=A" (n): "a" (__low), "d" (__high)); 		\
	__mod; 							\
	})

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
