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

#include "stdio.h"
#include "../driver/console.h"
int start(void)
{
	console_init();
	char d = 'c';
	char c = 'a';
	int a = 100;
	printk("xiyoulinux%10d%c", a, c);
	while (1);
	return 0;
}
