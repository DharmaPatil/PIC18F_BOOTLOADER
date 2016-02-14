/********************************************************************
 *	���C���֐�	������	���荞�݃x�N�^�[�̐ݒ�.
 ********************************************************************

�^�C�}�[�Q���荞�݂̎���:

�i�P�jTIMER2���g���� 10kHz�����̃C���^�[�o�����荞�݂��s���B
�i�Q�j���荞�ݏ�������10000��J�E���g���s���A10000��ɂȂ�Ɓi�P�b���j
      LED1�𔽓]������.


���̏�Ԃł� picmonit.exe �͎g�p�ł���̂ŁA�z�X�g�o�b����|�[�g��G������
���[�N�������肷�邱�Ƃ��o����.




 */
#include "usb/typedefs.h"
#include "usb/usb.h"
#include "io_cfg.h"
#include "timer2.h"
#include "monit.h"
#include "config.h"
#include "ps2keyb.h"

//	FUSE�ݒ�.
#include "fuse-config.h"

//	�I���X�C�b�`.
//---------------------------------------------------------------------
#define	TIMER2_INTERRUPT	0		// �^�C�}�[�Q���荞�݂��g�p����.
#define	TIMER2_INT_BLINK	0		// �^�C�}�[�Q���荞�݂�LED�u�����N.
//---------------------------------------------------------------------

void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
void timer2_int_handler(void);

/**	VECTOR REMAPPING ***********************************************/
#if	0
	#define	REMAPPED_RESET_VECTOR_ADDRESS			0x1000
	#define	REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
	#define	REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018
#endif

#if	1
	#define	REMAPPED_RESET_VECTOR_ADDRESS			0x800
	#define	REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
	#define	REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818
#endif

#if	0
	#define	REMAPPED_RESET_VECTOR_ADDRESS			0x00
	#define	REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x08
	#define	REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x18
#endif

/********************************************************************
 *	0x800�`�̃W�����v�x�N�^�[��ݒ肷��.
 ********************************************************************
 *	0x800 goto _startup
 *	0x808 goto YourHighPriorityISRCode
 *	0x818 goto YourLowPriorityISRCode
 */

extern void	_startup (void);		// See c018i.c in your C18 compiler	dir
#pragma	code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
void _reset	(void)
{
	_asm goto _startup _endasm
}


#pragma	code REMAPPED_HIGH_INTERRUPT_VECTOR	= REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void)
{
	 _asm goto YourHighPriorityISRCode _endasm
}


#pragma	code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
void Remapped_Low_ISR (void)
{
	 _asm goto YourLowPriorityISRCode _endasm
}

/********************************************************************
 *	0x008�`�̃W�����v�x�N�^�[��ݒ肷��.
 ********************************************************************
 *	0x008 goto 0x808
 *	0x018 goto 0x818
 */
#pragma	code HIGH_INTERRUPT_VECTOR = 0x08
void High_ISR (void)
{
	 _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
}


#pragma	code LOW_INTERRUPT_VECTOR =	0x18
void Low_ISR (void)
{
	 _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
}

/********************************************************************
 *	�W�����v�x�N�^�[�ݒ�͂����܂�.
 ********************************************************************
 */


#pragma	code
/********************************************************************
 *	High���荞�ݏ����֐�.
 ********************************************************************
 */
#pragma	interrupt YourHighPriorityISRCode
void YourHighPriorityISRCode()
{
	#if	defined(USB_INTERRUPT)
		USBDeviceTasks();
	#endif

#if	USE_PS2KEYBOARD		// PS/2�L�[�{�[�hI/F ���g�p����.
	#if	PS2KBD_USE_INTERRUPT
		// INT0���荞�݂� High�v���C�I���e�B�̂�.
		kbd_handler();
	#endif
#endif
}	//This return will be a	"retfie fast", since this is in	a #pragma interrupt	section

/********************************************************************
 *	Low	���荞�ݏ����֐�.
 ********************************************************************
 */
//#pragma	interruptlow YourLowPriorityISRCode
#pragma	interruptlow YourLowPriorityISRCode nosave=TBLPTR,TBLPTRU,TABLAT,PCLATH,PCLATU,PROD,section("MATH_DATA")
void YourLowPriorityISRCode()
{
	//Check	which interrupt	flag caused	the	interrupt.
	//Service the interrupt
	//Clear	the	interrupt flag
	//Etc.

	#if	TIMER2_INTERRUPT
		timer2_int_handler();
	#endif

}	//This return will be a	"retfie", since	this is	in a #pragma interruptlow section




#pragma	code

/**********************************************************************
 *	timer : ���荞�݃n���h���[.
 **********************************************************************
 */
void timer2_int_handler(void)
{
    if(	PIR1bits.TMR2IF){		// �^�C�}2���荞�݁H
#if	TIMER2_INT_SAMPLE			// �^�C�}�[�Q���荞�݂�PORT�T���v��.
		mon_int_handler();
#endif

#if	TIMER2_INT_BLINK			// �^�C�}�[�Q���荞�݂�LED�u�����N.
		static ushort cnt=0;
		cnt++;
		if(cnt >= 1000) {
			cnt = 0;
			mLED_1 = !mLED_1;	// LED�𔽓].
		}
#endif

#if	USE_PS2KEYBOARD		// PS/2�L�[�{�[�hI/F ���g�p����.
		kbd_int_handler();
#endif
        PIR1bits.TMR2IF=0;		// �^�C�}2���荞�݃t���O��0�ɂ���
	}
}

/**********************************************************************
 *	LED2 blink (��������)
 **********************************************************************
 */
void LED2_blink(void)
{
	static	ushort cnt=0;
	cnt++;
	if(cnt & 0x8000) mLED_2 = 1;
	else             mLED_2 = 0;
}

/********************************************************************
 *	�������֐�
 ********************************************************************
 */
static void	InitializeSystem(void)
{
#if RAM_SERIAL
	extern void set_serial_number(void);

	set_serial_number();
#endif
#if defined(__18F14K50)
	// ���̓s�����f�W�^�����[�h�ɂ���.
	ANSEL=0;
	ANSELH=0;
#endif
    ADCON1 = 0x0F;			//Need to make sure RB4 can be used as a digital input pin

#if	1
	// HIDaspx , PICwriter�p portb,portc��S���͂ɂ���.
	TRISB = 0xFF;
	TRISC = 0xFF;
#endif

#if	defined(USE_USB_BUS_SENSE_IO)
	tris_usb_bus_sense = INPUT_PIN;
#endif

#if	defined(USE_SELF_POWER_SENSE_IO)
	tris_self_power	= INPUT_PIN;
#endif
	mInitializeUSBDriver();
	UserInit();

#if	USE_PS2KEYBOARD		// PS/2�L�[�{�[�hI/F ���g�p����.
	kbd_init();
#endif

#if	TIMER2_INTERRUPT

//	timer2_init(0x80 |(15<<3)| 2,255);	// ���荞��ON,postscale 1/16,prescale 1/16,1/256 = 183.10 H
//	timer2_init(0x80 |(14<<3)| 2,249);	// ���荞��ON,postscale 1/15,prescale 1/16,1/250 = 200Hz
//	timer2_init(0x80 |(14<<3)| 2, 49);	// ���荞��ON,postscale 1/15,prescale 1/16,1/50 = 1000Hz
	timer2_init(0x80 |(14<<3)| 2,  4);	// ���荞��ON,postscale 1/15,prescale 1/16,1/5  =  10kHz

	// ���荞�݋���.
	InitTimer2InterruptLow();			// Timer2���荞�݂� low Priority�ɐݒ肷��.

#else

	INTCONbits.GIEL = 0; 		// Low  Priority ���荞�݂��֎~.
	INTCONbits.GIEH = 0; 		// High Priority ���荞�݂��֎~.
#endif
}

void USBtask(void)
{
	USBCheckBusStatus();					// Must	use	polling	method
	USBDriverService();						// Interrupt or	polling	method
	if((usb_device_state ==	CONFIGURED_STATE) && (UCONbits.SUSPND != 1)) {
		ProcessIO();
	}
}
/********************************************************************
 *	���C���֐�
 ********************************************************************
 */
void main(void)
{
	InitializeSystem();
	while(1){
		USBtask();
//		LED2_blink();
	}
}
/********************************************************************
 *
 ********************************************************************
 */
