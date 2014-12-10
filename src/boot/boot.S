#
# From the real mode to the protected mode 

#include "asm.h" 				
							# 主要包含了全局段描述符表
.set PROT_MODE_CSEG,        0x8                     	# kernel code segment selector
.globl start
start:
.code16
	cli 						# disable the interrupt
	cld 						# 消除符号位标志
	xorw %ax, %ax 					# 将ax置为0
	movw %ax, %es 					# 将es段地址设为0，主要是现在是实模式只能访问到1M的内存空间
	movw %ax, %ds 					# 将ds段地址设为0
	movw %ax, %ss 					# 将栈的基地址设为0


	inb $0x92, %al 					#
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
