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

int main(void)
{
	unsigned char * input = (unsigned char *)0xb8000;
	
	int i = 0;
	for (i = 0; i < 80 * 25; i += 2) {
		input[i] = 'H';
		input[i+1] = 0x70;
	}

	while (1);
	
	return 0;
}
