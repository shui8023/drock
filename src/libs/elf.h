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

#ifndef ELF_H
#define ELF_H

#include "defs.h"

#define MAGIC_HEAD_COUNT 	16

/*
 *elf header struct 
 *we can use the readelf to view 
 */
typedef struct {
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
}elf_header_t;

#endif //ELF_H
