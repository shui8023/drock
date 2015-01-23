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


#ifndef ASSERT_H
#define ASSERT_H


#define assert(x) 		\
	do { 			\
		if (!(x)) { 	\
			panic("assertion failed: %s", #x); \
		} 		\
	} while (0);


//静态断言，编译的时候检查,在编译的时候如果x是false，则会出现编译错误
#define static_assert(x) 	\
	switch (x) {case 0: case (x): ;}
		
#endif //ASSERT_H
