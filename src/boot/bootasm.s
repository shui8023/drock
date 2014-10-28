#
# From the real mode to the protected mode 
#

.globl start
start:
.code16
	cli 			#disable the interrupt
	xorw %ax, %ax
	movw %ax, %es
	movw %ax, %ds
	movw %ax, %ss

	lgdt gdt_size 		# set lgdt register 

	inb $0x92, %al
	or  $0xdf, %al
	outb %al, $0x92

	mov %cr0, %eax
	or 1, %eax
	mov %eax, %cr0
.code32
	movw 0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	
	movl $0x0, %ebp
	movl $start, %esp
	call start_main

gdt:
	.word 	0,0,0,0
	.word 	0x006F,0x7C00,0,0xFFFF 	# set  the cs segment
	.word 	0x006F,0x7C00,0,0xFFFF 	# set  the ds segment
gdt_size:
	.word 	0x17
	.long 	gdt

