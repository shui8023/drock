/*
 * =====================================================================================
 *
 *       Filename:  string.h
 *
 *    Description:  字符串操作函数
 *
 *        Version:  1.0
 *        Created:  2014年11月10日 19时36分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef STRING_H
#define STRING_H

#include <string.h>
#include <defs.h>

/**
 *字符串长度，字符串以'\0'结尾
 *
 * */
size_t strlen(const void *ptr);

/**
 *
 *
 * */
int8_t *strcpy(int8_t *dest, const int8_t *src);


int32_t strcmp(const int8_t *s1, const int8_t *s2);


void *memset(void *s, int c, size_t n);

void bzero(void *s, size_t n);

#endif //STRING_H
