/********************************************************************
 *	�ȈՃ��j�^
 ********************************************************************
 */
#include <string.h>
#include "usb/typedefs.h"
#include "usb/usb.h"
#include "io_cfg.h"
#include "monit.h"
#include "hidcmd.h"
#include "picwrt.h"
#include "timer2.h"

#include "config.h"

/********************************************************************
 *	�X�C�b�`
 ********************************************************************
 */
/********************************************************************
 *	��`
 ********************************************************************
 */
#if defined(__18F14K50)
#define	SOFTWARE_SPI_MODE	1
#define	DEVID	DEV_ID_PIC18F14K	//0x14
#else
#define	SOFTWARE_SPI_MODE	1		//18F4550����SPI��M�f�[�^��������.
#define	DEVID	DEV_ID_PIC			//0x25
#endif

#define	VER_H	1
#define	VER_L	1


//#define	POLL_ANALOG		0xa0
#define	REPLY_REPORT	0xaa

extern void user_cmd(int arg);

/********************************************************************
 *	�f�[�^
 ********************************************************************
 */
#pragma udata access accessram


//	AVR�������ݗp�R���e�N�X�g.
uchar near page_mode;
uchar near page_addr;
uchar near page_addr_h;

//	�f�[�^����胂�[�h�̐ݒ�.
uchar near  poll_mode;	// 00=���ݒ�  0xa0=�A�i���O�T���v��  0xc0=�f�W�^���T���v��
						// 0xc9=run�R�}���h�^�[�~�l�[�g
uchar near *poll_addr;	//

//	�R�}���h�̕ԐM���K�v�Ȃ�1���Z�b�g����.
uchar near ToPcRdy;


		uchar	puts_mode;

extern	uchar 	puts_buf[];
extern	uchar 	puts_ptr;

#if	TIMER2_INT_SAMPLE			// �^�C�}�[�Q���荞�݂�PORT�T���v��.
uchar	near	poll_wptr;
uchar	near	poll_rptr;

#pragma udata 	PollBuffer

uchar	poll_buf[256];

#endif


#pragma udata SomeSectionName1
Packet PacketFromPC;			//���̓p�P�b�g 64byte


#if defined(__18F14K50)
#pragma udata access accessram
Packet near PacketToPC;				//�o�̓p�P�b�g 64byte
#else
#pragma udata SomeSectionName2
Packet PacketToPC;				//�o�̓p�P�b�g 64byte
#endif




#define	Cmd0	PacketFromPC.cmd
#define	Data0	PacketFromPC.data[0]
#define	Mask1	PacketFromPC.data[1]





/********************************************************************
 *	ISP���W���[�� �C���N���[�h.
 ********************************************************************
 */
#pragma code

#if	SOFTWARE_SPI_MODE
#include "usi_pic18s.h"
#else
#include "usi_pic18.h"
#endif


static void isp_command(uchar *data) {
	uchar i;
	for (i=0;i<4;i++) {
		PacketToPC.raw[i]=usi_trans(data[i]);
	}
}

#if 1	/* Add by senshu */
unsigned char ReadEE(unsigned char Address)
{
	EECON1 = 0x00;
	EEADR = Address;
	EECON1bits.RD = 1;
	return (EEDATA);
}

void WriteEE(unsigned char Address, unsigned char Data)
{
	EEADR = Address;
	EEDATA = Data;
	EECON1 = 0b00000100;	// Setup writes: EEPGD=0,WREN=1
	/* Start Write */
	EECON2 = 0x55;
	EECON2 = 0xAA;
	EECON1bits.WR = 1;
	while( EECON1bits.WR);	// Wait till WR bit is clear, hopefully not long enough to kill USB
}
#endif

#if RAM_SERIAL	/* Add by senshu */
/*
  EEPROM MAP

	0x00�i���[�U�̈�j
	�@:
	0xef�i���[�U�̈�j

	0xf0 �V���A���ԍ��̑��������i���i�K�ł́A4�Ɍ���j
	0xf1 �V���A���ԍ��i1�����ځj
	0xf2 �V���A���ԍ��i2�����ځj
	0xf3 �V���A���ԍ��i3�����ځj
	0xf4 �V���A���ԍ��i4�����ځj
	0xf5 �V���A���ԍ��i5�����ځj
	0xf6 �V���A���ԍ��i6�����ځj
	0xf7 �\��
	 :
	0xfc �\��
	0xfd USB�V���A���̏������{�[���[�g
	0xfe DTR/RTS�Ȃǂ̗L���E�����̎w��Ȃ�
	0xff JUMP�A�h���X(H) .... �A�v���̏��8�r�b�g�w��
	�����ʂ� 0x00��z��
 */
#define EE_SERIAL_LEN 0xf0
#define EE_SERIAL_TOP 0xf1


void set_serial_number()
{
	unsigned char ch;
	int i, j;
	if (ReadEE(EE_SERIAL_LEN) == 4) {
		/* �f�[�^�̑Ó��������� */
		j = 0;
		for (i = EE_SERIAL_TOP; i < EE_SERIAL_TOP + 4; i++) {
			ch = ReadEE(i);
			if (' ' <= ch && ch <= 'z') {
				j++;
			}
		}
		/* �f�[�^���Ó��ł���΁A�l���Z�b�g���� */
		if (j == 4) {
			for (i = 0; i < 4; i++) {
				sd003.string[i] = ReadEE (EE_SERIAL_TOP + i);
			}
		}
	}
}

#endif

/********************************************************************
 *	������.
 ********************************************************************
 */
void UserInit(void)
{
    mInitAllLEDs();
	timer2_interval(5);	// '-d5'
	poll_mode = 0;
	poll_addr = 0;
	puts_ptr = 0;
	ToPcRdy = 0;

#if	TIMER2_INT_SAMPLE			// �^�C�}�[�Q���荞�݂�PORT�T���v��.
	poll_wptr=0;
	poll_rptr=0;
#endif
}


/********************************************************************
 *	�|�[�g�E�T���v��
 ********************************************************************
 */
#if	TIMER2_INT_SAMPLE			// �^�C�}�[�Q���荞�݂�PORT�T���v��.
void mon_int_handler(void)
{
	uchar c;

	if(	poll_mode == 0) return;

	if(	poll_mode == POLL_ANALOG) {
		// ANALOG
        while(ADCON0bits.NOT_DONE);     // Wait for conversion

		c = ADRESL;			//ADC �|�[�g�ǂݎ��,
		poll_buf[poll_wptr] = c;
		poll_wptr++;
		c = ADRESH;			//ADC �|�[�g�ǂݎ��,
		poll_buf[poll_wptr] = c;
		poll_wptr++;

        ADCON0bits.GO = 1;              // Start AD conversion
		return;
	}else{
		// DIGITAL
		c = *poll_addr;			//�|�[�g�ǂݎ��,
		poll_buf[poll_wptr] = c;
		poll_wptr++;
	}
}

int mon_read_sample(void)
{
	uchar c;
	if(	poll_rptr != poll_wptr) {
		c = poll_buf[poll_rptr];
		poll_rptr++;
		return c;
	}else{
		return -1;
	}
}

#endif
/********************************************************************
 *	�ڑ��e�X�g�̕ԓ�
 ********************************************************************
 */
void cmd_echo(void)
{
	PacketToPC.raw[1]=DEVID;				// PIC25/14K
	PacketToPC.raw[2]=VER_L;				// version.L
	PacketToPC.raw[3]=VER_H;				// version.H
	PacketToPC.raw[4]=0;					// bootloader
	PacketToPC.raw[5]=PacketFromPC.raw[1];	// ECHOBACK
	ToPcRdy = 1;
}

/********************************************************************
 *	�������[�ǂݏo��
 ********************************************************************
 */
void cmd_peek(void)
{
	uchar i,size,area;
	uchar *p;

 	size = PacketFromPC.size;
	area = size & AREA_MASK;
	size = size & SIZE_MASK;
 	p = (uchar*)PacketFromPC.adrs;

	if(area & AREA_PGMEM) {
//		PacketFromPC.data[0]=0;	// TBLPTRU���[���N���A.
		TBLPTR = (unsigned short long)PacketFromPC.adrs;

		for(i=0;i<size;i++) {
				_asm
				tblrdpostinc
				_endasm
			PacketToPC.raw[i]=TABLAT;
		}
	}else if(area & AREA_EEPROM) {
		unsigned char ee_adr = (unsigned char)(PacketFromPC.adrs & 0xff);

		for(i=0;i<size;i++) {
			PacketToPC.raw[i] = ReadEE(ee_adr++);
		}
	}else{
		for(i=0;i<size;i++) {
			PacketToPC.raw[i]=*p++;
		}
	}
	ToPcRdy = 1;
}
/********************************************************************
 *	�������[��������
 ********************************************************************
 */
void cmd_poke(void)
{
	uchar size,area;
	uchar *p;
 	area = PacketFromPC.size;
 	p = (uchar*)PacketFromPC.adrs;

#if 1	/* Add by senshu */
	if(area & AREA_EEPROM) {
		unsigned char ee_adr = (unsigned char)(PacketFromPC.adrs & 0xff);
		WriteEE(ee_adr, Data0);
	} else {
		if( Mask1 ) {	//�}�X�N��������.
			*p = (*p & Mask1) | Data0;
		}else{			//�ʏ폑������.
			*p = Data0;
		}
	}
#else
	if( Mask1 ) {	//�}�X�N��������.
		*p = (*p & Mask1) | Data0;
	}else{			//�ʏ폑������.
		*p = Data0;
	}
#endif
}

void usbModuleDisable(void)
{
    UCON = 0;                               // Disable module & detach from bus
    UIE = 0;                                // Mask all USB interrupts
//	usb_device_state = DETACHED_STATE;      // Defined in usbmmap.c & .h
}

void wait_ms(uchar ms);

/********************************************************************
 *	�Ԓn�w��̎��s
 ********************************************************************
 */
void cmd_exec(void)
{
	uchar bootflag=PacketFromPC.raw[5];

	if(	bootflag ) {

		INTCONbits.GIEL = 0; 		// Low  Priority ���荞�݂��֎~.
		INTCONbits.GIEH = 0; 		// High Priority ���荞�݂��֎~.

		wait_ms(10);
		usbModuleDisable();		// USB����U�؂藣��.
		wait_ms(10);
	}


	PCLATU=0;
	PCLATH=PacketFromPC.raw[3];	// adrs_h
#if	0
	PCL   =PacketFromPC.raw[2];	// adrs_l
#else
	{
		uchar adrs_l=PacketFromPC.raw[2];
		_asm
		movf	adrs_l,1,1
		movwf	PCL,0
		_endasm
	}
#endif
}


/********************************************************************
 *	puts ��������z�X�g�ɕԑ�����.
 ********************************************************************
 */
void cmd_get_string(void)
{
	PacketToPC.raw[0] =  puts_mode;	//'p';		/* �R�}���h���s������HOST�ɒm�点��. */
	PacketToPC.raw[1] =  puts_ptr;	// ������.
	memcpy( (void*)&PacketToPC.raw[2] , (void*)puts_buf , puts_ptr & 0x3f);	//������.
	puts_ptr = 0;
	ToPcRdy = 1;
}
/********************************************************************
 *	���[�U�[��`�֐��̎��s.
 ********************************************************************
 */
void cmd_user_cmd(void)
{
	puts_ptr = 0;
	puts_mode = 'p';
	user_cmd(PacketFromPC.adrs);
	puts_mode = 'q';
}

/********************************************************************
 *	1mS�P�ʂ̒x�����s��.
 ********************************************************************
 */
void cmd_wait_msec(void)
{
	uchar ms = PacketFromPC.size;
	if(ms) {
		wait_ms(ms);
	}
}

/********************************************************************
 *	�f�[�^�̘A�����M���s.
 ********************************************************************
 */
void make_report(void)
{
#if	TIMER2_INT_SAMPLE			// �^�C�}�[�Q���荞�݂�PORT�T���v��.
	uchar i;
	uchar cnt=0;
	int c;
	//�T���v���l���ő�60�܂ŕԂ�����.
	PacketToPC.raw[0] =  REPLY_REPORT;		/* �R�}���h���s������HOST�ɒm�点��. */
	for(i=0;i<60;i++) {
		c = mon_read_sample();
		if(c<0) break;
		PacketToPC.raw[2+i]=c;
		cnt++;
	}
	PacketToPC.raw[1] =  cnt;
#else
	//�T���v���l���P�����Ԃ�����.
	PacketToPC.raw[0] =  REPLY_REPORT;		/* �R�}���h���s������HOST�ɒm�点��. */

	if(	poll_mode == POLL_ANALOG) {
		PacketToPC.raw[1] = 2;
        while(ADCON0bits.NOT_DONE);     // Wait for conversion
		PacketToPC.raw[2] = ADRESL;
		PacketToPC.raw[3] = ADRESH;

	}else{
		PacketToPC.raw[1] = 1;
		PacketToPC.raw[2] = *poll_addr;
	}
#endif
	ToPcRdy = 1;
}
/********************************************************************
 *	�f�[�^����胂�[�h�̐ݒ�
 ********************************************************************
 */
void cmd_set_mode(void)
{
	poll_mode = PacketFromPC.size;
	poll_addr = (uchar near *) PacketFromPC.adrs;

	if(	poll_mode == POLL_ANALOG) {
		mInitPOT();
		ADCON0bits.GO = 1;              // Start AD conversion
	}

	make_report();
}

/********************************************************************
 *	AVR���C�^�[�̐ݒ�
 ********************************************************************
 */
void cmd_set_status(void)
{
/* ISP�p�̃s����Hi-Z���� */
/* ISP�ڍs�̎菇���A�t�@�[�����Ŏ��� */
	if(PacketFromPC.raw[2] & 0x10) {// RST�����̏ꍇ
		ispDisconnect();
	}else{
		if(PacketFromPC.raw[2] & 0x80) {// RST��Ԃ�SCK H�� SCK�p���X�v��
			ispSckPulse();
		} else {
			ispConnect();
		}
	}
	PacketToPC.raw[0] = REPLY_REPORT;	/* �R�}���h���s������HOST�ɒm�点��. */
	ToPcRdy = 1;
}
/********************************************************************
 *	PORT�ւ̏o�͐���
 ********************************************************************
 */
void cmd_tx(void)
{
	isp_command( &PacketFromPC.raw[1]);
	ToPcRdy = Cmd0 & 1;	// LSB��On�Ȃ�ԓ����K�v.
}
/********************************************************************
 *	�y�[�W�A�h���X�̐ݒ�.
 ********************************************************************
 */
void cmd_set_page(void)
{
	page_mode = PacketFromPC.raw[1];
	page_addr = PacketFromPC.raw[2];
	page_addr_h = PacketFromPC.raw[3];
}
/********************************************************************
 *	ISP�������݃N���b�N�̐ݒ�.
 ********************************************************************
 */
void cmd_set_delay(void)
{
	usi_set_delay(PacketFromPC.raw[1]);	// '-dN'
}

/********************************************************************
 *	AVR��������(Fusion)�R�}���h�̎��s
 ********************************************************************
 *	Cmd0 : 0x20�`0x27
 */
void cmd_page_tx(void)
{
	uchar i;
	//
	//	page_write�J�n����page_addr��data[1]�ŏ�����.
	//
	if( Cmd0 & (HIDASP_PAGE_TX_START & MODE_MASK)) {
		page_mode = 0x40;
		page_addr = 0;
		page_addr_h = 0;
	}
	//
	//	page_write (�܂���page_read) �̎��s.
	//
	for(i=0;i<PacketFromPC.size;i++) {
		usi_trans(page_mode);
		usi_trans(page_addr_h);
		usi_trans(page_addr);
		PacketToPC.raw[i]=usi_trans(PacketFromPC.raw[i+2]);

		if (page_mode & 0x88) { // EEPROM or FlashH
			page_addr++;
			if(page_addr==0) {page_addr_h++;}
			page_mode&=~0x08;
		} else {
			page_mode|=0x08;
		}
	}
	//
	//	isp_command(Flash��������)�̎��s.
	//
	if( Cmd0 & (HIDASP_PAGE_TX_FLUSH & MODE_MASK)) {
		isp_command( &PacketFromPC.raw[PacketFromPC.size+2]);
	}
	ToPcRdy = Cmd0 & 1;	// LSB��On�Ȃ�ԓ����K�v.
}

/********************************************************************
 *	AVR���C�^�[�n�R�}���h��M�Ǝ��s.
 ********************************************************************
 *	Cmd0 : 0x20�`0x2F
 */
void cmd_avrspx(void)
{
	if(Cmd0 < (HIDASP_CMD_TX) ) 	{cmd_page_tx();}	// 0x20�`0x27

	// 0x28�`0x2F
	else if(Cmd0==HIDASP_SET_STATUS){cmd_set_status();}
	else if(Cmd0==HIDASP_SET_PAGE) 	{cmd_set_page();}
	else if(Cmd0==HIDASP_CMD_TX) 	{cmd_tx();}
	else if(Cmd0==HIDASP_CMD_TX_1) 	{cmd_tx();}
	else if(Cmd0==HIDASP_SET_DELAY) {cmd_set_delay();}
	else if(Cmd0==HIDASP_WAIT_MSEC) {cmd_wait_msec();}
}


/********************************************************************
 *	���j�^�R�}���h��M�Ǝ��s.
 ********************************************************************
 */
void ProcessIO(void)
{
	// �ԓ��p�P�b�g����ł��邱�ƁA���A
	// �����Ώۂ̎�M�f�[�^������.
	if((ToPcRdy == 0) && (!mHIDRxIsBusy())) {

		//��M�f�[�^������΁A��M�f�[�^���󂯎��.
		HIDRxReport64((char *)&PacketFromPC);
		PacketToPC.raw[0]=Cmd0;		// CMD ECHOBACK

		//�R�}���h�ɑΉ����鏈�����Ăяo��.
		if(Cmd0 >= HIDASP_PAGE_TX)  {cmd_avrspx();}	// AVR���C�^�[�R�}���h.
		else if(Cmd0 >= PICSPX_SETADRS24){cmd_picspx();}	// PIC���C�^�[�R�}���h.
		else if(Cmd0==HIDASP_PEEK) 	{cmd_peek();}	// �������[�ǂݏo��.
		else if(Cmd0==HIDASP_POKE) 	{cmd_poke();}	// �������[��������.
		else if(Cmd0==HIDASP_JMP) 	{cmd_exec();}	// ���s.
		else if(Cmd0==HIDASP_SET_MODE)  {cmd_set_mode();}
		else if(Cmd0==HIDASP_GET_STRING){cmd_get_string();}
		else if(Cmd0==HIDASP_USER_CMD)  {cmd_user_cmd();}
		else if(Cmd0==HIDASP_TEST) 	{cmd_echo();}	// �ڑ��e�X�g.
	}

	// �K�v�Ȃ�A�ԓ��p�P�b�g���C���^���v�g�]��(EP1)�Ńz�X�gPC�ɕԋp����.
	if( ToPcRdy ) {
		if(!mHIDTxIsBusy()) {
			HIDTxReport64((char *)&PacketToPC);
			ToPcRdy = 0;

			if(poll_mode!=0) {
				if(mHIDRxIsBusy()) {	//�R�}���h�����Ȃ����著�葱����.
					make_report();
				}
			}
		}
	}
}
/********************************************************************
 *
 ********************************************************************
 */
