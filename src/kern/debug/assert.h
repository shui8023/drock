/*
 * =====================================================================================
 *
 *       Filename:  assert.h
 *
 *    Description: 断言的文件
 *
 *        Version:  1.0
 *        Created:  2015年01月22日 22时39分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */


#ifndef __KERN_DEBUG_ASSERT_H__
#define __KERN_DEBUG_ASSERT_H__


void __painc(const char *filename, int line, const char *fm, ...);

#define panic(...) 		\
	__panic(__FILE__, __LINE__, __VA_ARGS__)

#define assert(x) 		\
	do { 			\
		if (!(x)) { 	\
			panic("assertion failed: %s", #x); \
		} 		\
	} while (0);


//静态断言，编译的时候检查,在编译的时候如果x是false，则会出现编译错误
#define static_assert(x) 	\
	switch (x) {case 0: case (x): ;}
		
#endif /*__KERN_DEBUG_ASSERT_H__ */
