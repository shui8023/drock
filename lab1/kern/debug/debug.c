/*
 * =====================================================================================
 *
 *       Filename:  debug.c
 *
 *    Description:  打印kernel函数栈的信息和kernel的基本信息
 *
 *        Version:  1.0
 *        Created:  2015年01月25日 12时46分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include <debug.h>
#include <assert.h>
#include <elf.h>
#include <stdio.h>
#include <string.h>


#define ELFHEADER ((struct elfhdr *)0x10000)


/*查找字符串表,符号表的位置
 *
 *
 */
static struct elf_shdr *read_elf_header(void) 
{
	struct elf_shdr *pro = (struct elf_shdr *)((uint32_t)ELFHEADER + ELFHEADER->e_shoff);
	uint32_t elf_shdr_count = ELFHEADER->e_shnum;
/*
	int i = 0;
	for (i = 0; i < elf_shdr_count; ++i) {
		const char *name = (const char *)(elf_shdr_strs_addr + elf_sh[i].sh_name);
		printk("%s\n", name);
	}
	return elf_sh;
	*/
}

/*function：打印内核的基本信息
 *计算kernel在内存的大小
 *
 */
void inline print_kerninfo(void)
{
	extern char end[], edata[], kern_start[], etext[];
	printk("    start:\t%x(phys)\n", kern_start);
	printk("    etext:\t%x(phys)\n", etext);
	printk("    edata:\t%x(phys)\n", edata);
	printk("      end:\t%x(phys)\n", end);
	/* 加上1023是为了向上取整 */
	printk("the kernel  memory in used: %d KB\n", (end - kern_start + 1023) / 1024);
	read_elf_header();
}



/*打印drock的栈信息
 *
 *
 */
void print_stackframe(void)
{

}
