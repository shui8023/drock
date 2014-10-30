#
# From the real mode to the protected mode 

#include "asm.h"

.set PROT_MODE_CSEG,        0x8                     # kernel code segment selector
.globl start
start:
.code16
	cli 			#disable the interrupt
	cld
	xorw %ax, %ax
	movw %ax, %es
	movw %ax, %ds
	movw %ax, %ss


	inb $0x92, %al
	or  2, %al
	outb  %al, $0x92                                                                              
	
	lgdt gdt_ptr 	
	# set lgdt register 
	
	mov %cr0, %eax
	or $0x1, %eax
	mov %eax, %cr0
# 进行跳转，不进行跳转，会出错
    	ljmp $PROT_MODE_CSEG, $protcseg
.code32
protcseg:
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	
	movl $0x0, %ebp
	movl $start, %esp
	call start_main

.p2align 2                                          # force 4 byte alignment
gdt:
    SEG_NULLASM
    SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)
    SEG_ASM(STA_W, 0x0, 0xffffffff)
gdt_ptr:
    .word 0x17                                      # sizeof(gdt) - 1
    .long gdt                                       # address gdt
