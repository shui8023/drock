/*
 * =====================================================================================
 *
 *       Filename:  init.c
 *
 *    Description:  start the drock kernel
 *
 *        Version:  1.0
 *        Created:  2014年11月01日 21时54分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <console.h>
#include <debug.h>
#include <idt.h>
int start(void)
{
	/* 必须把数据段初始化为0 */
	extern char end[], edata[];
	memset(edata, 0, end-edata);
	init_idt();
	console_init();
	print_kerninfo();

	asm volatile ("int $0x03");
	while (1);
	return 0;
}
