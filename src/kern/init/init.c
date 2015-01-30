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

int start(void)
{
	extern char edata[], end[];
	memset(edata, 0, end-edata);
	int i = 0;
	console_init();
	assert(i);
	char c = 'a';
	char *s = "hello word!";
	int a;
	a = strlen(s);
	printk("xiyoulinux%10d\t%c\b", a, c);
	while (1);
	return 0;
}
