/********************************************************************
 *	ユーザー定義関数の実行
 ********************************************************************
 */
//#include "usb/typedefs.h"
#include "usb/usb.h"
#include "io_cfg.h"
#include "monit.h"
#include "hidcmd.h"

#include <stdio.h>

/* by default stdout issues to the USART */
FILE *stdout = _H_USER;

/********************************************************************
 *	定義
 ********************************************************************
 */
/********************************************************************
 *	データ
 ********************************************************************
 */
//#pragma udata access accessram
#pragma udata

#define	PUTBUF_SIZE	16

uchar puts_buf[PUTBUF_SIZE];
uchar puts_ptr;

#pragma code

/********************************************************************
 *	
 ********************************************************************
 */
int _user_putc(char c)
{
	uchar flush = 0;
	if( c == 0x0a) { flush = 1; }
	if( puts_ptr >= PUTBUF_SIZE ) {flush = 1;}

	if( flush ) {
		while(puts_ptr) {
			USBtask();
		}
	}

	if(	puts_ptr < PUTBUF_SIZE ) {
		puts_buf[puts_ptr++]=c;
	}

	return 1;
}
/********************************************************************
 *	
 ********************************************************************
 */
