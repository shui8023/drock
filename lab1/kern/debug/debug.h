/*
 * =====================================================================================
 *
 *       Filename:  debug.h
 *
 *    Description:  打印函数栈的信息，kernel的基本的信息
 *
 *        Version:  1.0
 *        Created:  2015年01月23日 09时57分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef __KERN_DEBUG_DEBUG_H__
#define __KERN_DEBUG_DEBUG_H__

#include <defs.h>

void print_kerninfo(void);
void print_stackframe(void);


#endif  /* __KERN_DEBUG_DEBUG_H__ */
