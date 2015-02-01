/*
 * =====================================================================================
 *
 *       Filename:  console.h
 *
 *    Description:  IO端口的输入输出
 *
 *        Version:  1.0
 *        Created:  2014年11月14日 21时07分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef __KERN_DRIVER_CONSOLE_H__
#define __KERN_DEIVER_CONSOLE_H_

void console_init(void);
void console_putc(int c);
void console_getc(void);

#endif  //__KERN_DRIVER_CONSOLE_H__

