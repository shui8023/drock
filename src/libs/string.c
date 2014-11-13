/*
 * =====================================================================================
 *
 *       Filename:  string.c
 *
 *    Description:  字符串的操作函数
 *
 *        Version:  1.0
 *        Created:  2014年11月10日 19时51分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */
#include <defs.h>

size_t 
strlen(const void *ptr)
{
	const int8_t *char_ptr;
	const  uint64_t *longword_ptr;

	register uint64_t longword, himagic, limagic;

	for (char_ptr = ptr; ((uint64_t)char_ptr & (sizeof(uint64_t) - 1)) != 0; ++char_ptr) {
		if (*char_ptr == '\0') {
			return char_ptr - ptr;
		}
	}
	
	longword_ptr = (uint64_t)char_ptr;
	himagic = 0x80808080L;
	limagic = 0x01010101L;


	while (true) {
		longword = longword_ptr++;

		if (((longword - limagic) & himagic) != 0) {
			
			const int8_t *p = (int8_t *)(longword_ptr - 1);
			
			if (p[0] == '\0') {
				return  c - str;
			}
			if (p[1] == '\0') {
				return c - str + 1;
			}
			if (p[2] == '\0') {
				return c - str + 2;
			}
			if (p[3] == '\0') {
				return c - str + 3;
			}
		}
	}
}

/**
 *
 *
 * */
int8_t *
strcpy(int8_t *dest, const int8_t *src)
{
	int i = 0;
	for (i = 0; i < strlen(dest) || i < strlen(src); ++i) {
		*dest++ = *src++;
	}

}


int32_t 
strcmp(const int8_t *s1, const int8_t *s2)
{
	
}


void *
memset(void *s, int c, size_t n)
{
	
}

void 
bzero(void *s, size_t n);
