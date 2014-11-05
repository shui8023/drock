/*
 * =====================================================================================
 *
 *       Filename:  bootmain.c
 *
 *    Description: kernel start 
 *
 *        Version:  1.0
 *        Created:  2014年10月28日 21时29分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */
#include "x86.h"
#include "elf.h"
#include "defs.h"


#define SECTSIZE 512

#define ELFHDR 	((struct elfhdr *)0x10000)

static void 
readsect(void *load_address, uint32_t count)
{
	/*使用LBA28来访问硬盘，0x1F7是一个命令端口，又是一个状态端口，
	 *它将0x1f7端口的第7位置为1,表示很忙，把第三位置1,表示准备好了
	 */
	while ((inb(0x1F7) & 0xC0) != 0x40) {
		;
	}	
	
	outb(0x1F2, 1);
	outb(0x1F3, count & 0xFF); 		//提取0-7位
	outb(0x1F4, (count >> 8) & 0xFF); 	//提取8-15位
	outb(0x1F5, (count >> 16) & 0xFF); 	//提取16-23
	outb(0x1F6, ((count >> 24) & 0xF) | 0xE0); 	//提取24-27

	outb(0x1F7, 0x20);

	
	while ((inb(0x1F7) & 0xC0) != 0x40) {
		;
	}
	
	insl(0x1F0, load_address, SECTSIZE / 4);
}
/*
 *readseg :read @count bytes at @offset from kernel into virtual address @va
 *
 */
static 	void 
readseg(uint32_t va, uint32_t count, uint32_t offset)
{
	uint32_t va_end = va + count; 		//结束地址
	
	/*
	 *为了完整开始一个扇区,这就可能读取的数据过多
	 */
	va -= offset % SECTSIZE;
	
	/*
	 *要读取的扇区的个数
	 */
	uint32_t  sector_number = (offset / SECTSIZE) + 1;

	/*va是内存中起始位置
	 *
	 */
	for (; va < va_end; va += SECTSIZE, ++sector_number) {
		readsect((void *)va, sector_number);
	}
}

void 
start_main()
{

	/*
	 *read the elf header, find the elf entry address 
	 *
	 */

	readseg((uint32_t)ELFHDR, SECTSIZE * 8, 0);

	struct proghdr *ph, *ehp;

	ph = (struct proghdr *)((uint32_t)ELFHDR + ELFHDR->e_phoff);
	ehp = ph + ELFHDR->e_phnum;

	for (; ph < ehp; ++ph) {
		readseg(ph->p_va & 0xFFFFFF, ph->p_memsz, ph->p_offset);
	}


	uint8_t *input = (uint8_t *)0xb8000;
	*input++ = '-';
	*input++ = 0x07;

	((void (*)(void))(ELFHDR->e_entry & 0xFFFFFF))();	
	
	while (1);


}
