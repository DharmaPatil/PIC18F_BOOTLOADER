/********************************************************************
 *	64�o�C�g���ő���memcpy����.
 *  void memcpy64(char *t,char *s)
 ********************************************************************
 *	�P���b�P�ʂ̎��ԑ҂�. �i�ő�255���b�܂Łj
 *	void wait_ms(uchar ms)
 ********************************************************************
 *	�P�ʕb�P�ʂ̎��ԑ҂�.�i�ő�255�ʕb�܂Łj
 *	void wait_us(uchar us)
 ********************************************************************
 */

#include "monit.h"

#pragma code

/********************************************************************
 *	64�o�C�g���ő���memcpy
 ********************************************************************
 *  void memcpy64(char *t,char *s)
 *	����:
 *		char *t : �]����A�h���X
 *		char *s : �]�����A�h���X
 *
 *  ����:
 *		���ׂ�asm�L�q�Ȃ̂ŁA�����擾(FSR1�f�[�^�X�^�b�N����)�͎��O�ōs���Ă���.
 *		�]���o�C�g����64�o�C�g�Œ�.
 *
 */

void memcpy64()		//(char *t,char *s)
{
	_asm
		movff  FSR2L, POSTINC1
		movff  FSR2H, POSTINC1

		// FSR2=t;
		movlw  0xfa
		movff  PLUSW1, FSR2L
		movlw  0xfb
		movff  PLUSW1, FSR2H

		// FSR0=s;
		movlw  0xfc
		movff  PLUSW1, FSR0L
		movlw  0xfd
		movff  PLUSW1, FSR0H

		movlw  4

memcpy64_loop:	// 16byte copy
		//		  *t++ = *s++  x 16
		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0

		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0

		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0

		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0
		movff     POSTINC2, POSTINC0

		decfsz	WREG,1,0
		bra		memcpy64_loop


		movlw  0xff
		movff  PLUSW1, FSR2H
		movf   POSTDEC1,0,0
		movlw  0xff
		movff  PLUSW1, FSR2L
		movf   POSTDEC1,0,0
	_endasm
}


/*********************************************************************
 *	�P�ʕb�P�ʂ̎��ԑ҂�.�i�ő�255�ʕb�܂Łj
 *********************************************************************
 */
void wait_us(uchar us)
{
	do {
		_asm 
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		_endasm;
	} while(--us);
}


/*********************************************************************
 *	�P���b�P�ʂ̎��ԑ҂�. �i�ő�255���b�܂Łj
 *********************************************************************
 */
void wait_ms(uchar ms)
{
	do {
		wait_us(250);
		wait_us(250);
		wait_us(250);
		wait_us(250);
	}while(--ms);
}
