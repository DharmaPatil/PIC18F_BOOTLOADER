/********************************************************************
 *	ユーザー定義関数の実行
 ********************************************************************
 */
#include <stdio.h>
#include <string.h>

#include "usb/typedefs.h"
#include "usb/usb.h"
#include "io_cfg.h"
#include "monit.h"
#include "hidcmd.h"
#include "ps2keyb.h"
#include "config.h"

//int _user_putc(char c);

#if	USE_PS2KEYBOARD		// PS/2キーボードI/F を使用する.

/********************************************************************
 *	定義
 ********************************************************************
 */
/********************************************************************
 *	データ
 ********************************************************************
 */
#pragma udata

#pragma code
/**********************************************************************
 *	LED1 blink (生存反応)
 **********************************************************************
 */
static void LED1_blink(void)
{
	static	ushort cnt=0;
	cnt++;
	if(cnt & 0x800) mLED_1 = 1;
	else            mLED_1 = 0;
}


#if	0
	#define	GETKEY	kbd_getchar()	// ASCII CODE
#else
	#define	GETKEY	kbd_getcode()	// KEY-PRESS CODE
#endif

/********************************************************************
 *	
 ********************************************************************
 */
void user_cmd(int arg)
{
	uchar c;
	uchar i;
	for(i=0;i<80;i++) {
		do {
			USBtask();
			c = GETKEY;
		} while(c==0);
		printf("key : %02x\n",c);
	}
}
/********************************************************************
 *	
 ********************************************************************
 */
#else
void user_cmd(int arg)
{
}
#endif	//USE_PS2KEYBOARD		// PS/2キーボードI/F を使用する.
