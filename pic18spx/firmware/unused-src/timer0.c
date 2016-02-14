/********************************************************************
 *	�^�C�}�[�O
 ********************************************************************
 */
#include "usb/typedefs.h" 
#include "usb/usb.h"      
#include "io_cfg.h"       

#include <timers.h>       

#include "timer0.h"       

volatile int   timer_count;			//�N�����Ă���̎���.(tick)
volatile int   timer_count_high;	//�N�����Ă���̎���.(tick/65536)

volatile uchar timer_tick;			//�^�C�}�[���荞�ݔ����t���O.

#define	TIMER_DA_OUT	0			//�^�C�}�[���荞�݂̃^�C�~���O��D/A�o�͂�L����.

#if		TIMER_DA_OUT				//�^�C�}�[���荞�݂̃^�C�~���O��D/A�o�͂�L����.
static	 uchar timer_daout;			//�^�C�}�[���荞�݂̃^�C�~���O��D/A�o��.
#endif


void kbd_int_handler(void);

/**********************************************************************
 *	������.
 **********************************************************************
 */
void timer0_init(int cnt)
{
	timer_count = 0;

//    OpenTimer0(TIMER_INT_ON & T0_8BIT & T0_SOURCE_INT & T0_PS_1_256);
    OpenTimer0(TIMER_INT_ON & T0_8BIT & T0_SOURCE_INT & T0_PS_1_1);	//46kHz
                                // �^�C�}0�̐ݒ�, 8�r�b�g���[�h, �����ݎg�� 
                                //�����N���b�N�A1:256�v���X�P�[��
	//**** �����݂̋���
    INTCONbits.GIE=1;           // ���荞�݂��C�l�[�u���ɂ���
}

/**********************************************************************
 *	���Ɋ��荞�ނ܂ő҂�.
 **********************************************************************
 */
uchar timer0_wait(void)
{
	while(timer_tick == 0) { /* nothing */ };
	timer_tick --;
	return timer_tick;
}
/**********************************************************************
 *
 **********************************************************************
 */
int timer0_gettime(void)
{
	return timer_count;
}
/**********************************************************************
 *	timer : ���荞�݃n���h���[.
 **********************************************************************
 */
void timer0_int_handler(void)
{
    if(	INTCONbits.T0IF){		// �^�C�}0���荞�݁H
        INTCONbits.T0IF=0;		// �^�C�}0���荞�݃t���O��0�ɂ���

		timer_count ++;
		if(	timer_count==0) {
			timer_count_high++;
		}
		timer_tick ++;
	}

#if	PS2KBD_USE_INTERRUPT
//  use PCINT8 hardhandler
#else
//	use TIMER1 softhandler
	kbd_int_handler();
#endif

}
/**********************************************************************
 *	
 **********************************************************************
 */
#if		TIMER_DA_OUT				//�^�C�}�[���荞�݂̃^�C�~���O��D/A�o�͂�L����.
void sound_out(uchar x)
{
	timer_daout = x;
}
#endif
/**********************************************************************
 *	
 **********************************************************************
 */


