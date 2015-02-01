/*
 * =====================================================================================
 *
 *       Filename:  stdarg.h
 *
 *    Description:  printf所用的宏，用来求取参数的
 *
 *        Version:  1.0
 *        Created:  2014年11月13日 23时26分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef STDARG_H
#define STDARG_H

#include <defs.h>

#define va_list 	char *
#define va_start(ap, list) 	(ap = (va_list)&list + sizeof(list)) //求取第二个参数的首地址(从左到右)
#define va_arg(ap, type) 	(*(type *)((ap += sizeof(type)) - sizeof(type))) //将ap指向下一个参数的首地址
#define va_end(ap) 		(ap = (va_list)NULL)
#endif //STDARG_H

