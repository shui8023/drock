/*
 * =====================================================================================
 *
 *       Filename:  bootmain.c
 *
 *    Description: kernel start 
 *
 *        Version:  1.0
 *        Created:  2014年10月28日 21时29分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

void start_main()
{
	unsigned char *input = (unsigned char *)0xb8000;
	*input++ = 'H';
	*input++ = 0x70;
	*input++ = 'H';
	*input++ = 0x70;
	*input++ = 'H';
	*input++ = 0x70;
	*input++ = 'H';
	*input++ = 0x70;
	*input++ = 'H';
	*input++ = 0x70;
	*input++ = 'H';
	*input++ = 0x70;
	*input++ = 'H';
	*input++ = 0x70;
	*input++ = 'H';
	*input++ = 0x70;
	*input++ = 'H';
	*input++ = 0x70;
	*input++ = 'H';
	*input++ = 0x70;
	*input++ = 'H';
	*input++ = 0x70;
	*input++ = 'H';
	*input++ = 0x70;

	while (1);

}
