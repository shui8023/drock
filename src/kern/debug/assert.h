/*
 * =====================================================================================
 *
 *       Filename:  assert.h
 *
 *    Description:  
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


#define static_assert(x) 	\
	switch (x) {case 0: case (x): ;}
		
#endif //ASSERT_H
