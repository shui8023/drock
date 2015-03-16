# ------------------------------------------------------------------------
# 定义中断处理函数
#-------------------------------------------------------------------------

.macro ISR_NOERRCODE args
.GLOBAL isr\args
isr\args:
	cli
	push  $0
	push  $\args
	jmp isr_save_register
.endm

.macro ISR_ERRCODE args
.GLOBAL isr\args
isr\args:
	cli
	push $\args
	jmp isr_save_register
.endm
.macro IRQ  argc, args
.GLOBAL irq\argc
irq\argc:
	cli
	push $0
	push $\args
	jmp irq_save_register
.endm

ISR_NOERRCODE		0
ISR_NOERRCODE		1
ISR_NOERRCODE		2
ISR_NOERRCODE		3
ISR_NOERRCODE		4
ISR_NOERRCODE		5
ISR_NOERRCODE		6
ISR_NOERRCODE		7
ISR_ERRCODE		8
ISR_NOERRCODE		9
ISR_ERRCODE		10
ISR_ERRCODE		11
ISR_ERRCODE		12
ISR_ERRCODE		13
ISR_ERRCODE		14
ISR_NOERRCODE		15
ISR_NOERRCODE		16
ISR_ERRCODE		17
ISR_NOERRCODE		18
ISR_NOERRCODE		19
ISR_NOERRCODE		20
ISR_NOERRCODE		21
ISR_NOERRCODE		22
ISR_NOERRCODE		23
ISR_NOERRCODE		24
ISR_NOERRCODE		25
ISR_NOERRCODE		26
ISR_NOERRCODE		27
ISR_NOERRCODE		28
ISR_NOERRCODE		29
ISR_NOERRCODE		30
ISR_NOERRCODE		31
ISR_NOERRCODE		255

IRQ 	 0, 32
IRQ 	 1, 33
IRQ 	 2, 34
IRQ 	 3, 35
IRQ 	 4, 36
IRQ 	 5, 37
IRQ 	 6, 38
IRQ 	 7, 39
IRQ 	 8, 40
IRQ 	 9, 41
IRQ 	10, 42
IRQ 	11, 43
IRQ 	12, 44
IRQ 	13, 45
IRQ 	14, 46
IRQ 	15, 47

.GLOBAL isr_save_register
.EXTERN isr_handler
isr_save_register:
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushal
	
	mov $0x10, %eax
	mov %ax, %ds
	mov %ax, %es
	
	pushl %esp
	call isr_handler
	
	popl %esp
	popal

	popl %gs
	popl %fs
	popl %es
	popl %ds

	addl $0x8, %esp
	iret

.GLOBAL irq_save_register
.EXTERN irq_handler
irq_save_register:
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushal
	
	mov $0x10, %eax
	mov %ax, %ds
	mov %ax, %es
	
	pushl %esp
	call irq_handler
	
	popl %esp
	popal

	popl %gs
	popl %fs
	popl %es
	popl %ds

	addl $0x8, %esp
	iret


.GLOBAL idt_flush
idt_flush:
	mov  4(%esp), %eax
	lidt (%eax)
	ret
