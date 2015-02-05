/*
 * =====================================================================================
 *
 *       Filename:  elf.h
 *
 *    Description:  ELF文件格式的定义
 *
 *        Version:  1.0
 *        Created:  2014年11月02日 23时49分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef __LIB_ELF_H__
#define __LIB_ELF_H__

#include "defs.h"

#define MAGIC_HEAD_COUNT 	12

/*
 *elf header struct 
 *we can use the readelf to view 
 */

struct elfhdr {
	uint32_t 	e_magic;    
	uint8_t 	e_ident[MAGIC_HEAD_COUNT];
	uint16_t 	e_type;
	uint16_t 	e_machine;
	uint32_t 	e_version;
	uint32_t 	e_entry;
	uint32_t 	e_phoff;
	uint32_t 	e_shoff;
	uint32_t 	e_flags;
	uint16_t 	e_ehsize;
	uint16_t 	e_phentsize;
	uint16_t 	e_phnum;
	uint16_t 	e_shentsize;
	uint16_t 	e_shnum;
	uint16_t 	e_shstrndx;
}__attribute__((packed));

/*ELF的程序头部,是一个结构数组
 *每个结构描述了一个段或着系统准备的程序执行所必需的的其他信息
 *
 */
struct proghdr {
	uint32_t 	p_type;
	uint32_t 	p_offset;
	uint32_t 	p_va;
	uint32_t 	p_pa;
	uint32_t 	p_filesz;
	uint32_t 	p_memsz;
	uint32_t 	p_flags;
	uint32_t 	p_align;
}__attribute__((packed));

/*ELF的节区头部
 *
 *
 */

struct elf_shdr {
	uint32_t sh_name;
	uint32_t sh_type;
	uint32_t sh_flags;
	uint32_t sh_addr;
	uint32_t sh_offset;
	uint32_t sh_size;
	uint32_t sh_link;
	uint32_t sh_info;
	uint32_t sh_addralign;
	uint32_t sh_entsize;
}__attribute__((packed));
#endif //__LIB_ELF_H__
