/*
 * =====================================================================================
 *
 *       Filename:  timer.h
 *
 *    Description:  初始化8254可编程芯片
 *
 *        Version:  1.0
 *        Created:  2015年02月14日 19时53分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef __KERN_DRIVER_TIMER_H__
#define __KERN_DRIVER_TIMER_H__

void init_timer(uint32_t frequency);
void handler_timer(struct pt_regs *regs);

#endif /* __KERN_DRIVER_TIMER_H__ */
