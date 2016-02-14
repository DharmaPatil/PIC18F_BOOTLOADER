#ifndef	_driver_h_
#define	_driver_h_

#include "monit.h"

#define HIDASP_RST_H_GREEN	0x18
#define HIDASP_RST_H_RED	0x14
#define HIDASP_RST_L_GREEN	0x08
#define HIDASP_RST_L_BOTH	0x00
#define HIDASP_SCK_PULSE 	0x80	// RST-L SLK-pulse ,LED ON	@@kuga

#define HIDASP_ISP_MODE 	1		// Add by senshu
#define HIDASP_USB_IO_MODE 	2
#define HIDASP_FUSION_OK 	4
#define HIDASP_MODE_ERROR 	128

int hidCommand (int cmd, int arg1, int arg2, int arg3);
int hidPeekMem (int addr);
int hidPokeMem (int addr, int data0, int mask);
int bulkRead(uchar *buf, int Length);
int hidReadBuffer (uchar *buf, int len ,int id);
int hidReadPoll (uchar *buf, int Length, int id);
int hidWriteBuffer (uchar *buf, int len);
void hidasp_close (void);
int hidasp_cmd (const unsigned char cmd[4], unsigned char res[4]);
int hidasp_init (void);
int hidasp_list (char * string);
int hidasp_page_read (long addr, unsigned char *wd, int pagesize);
int hidasp_page_write (long addr, const unsigned char *wd, int pagesize, int flashsize);
int hidasp_page_write_fast (long addr, const unsigned char *wd, int pagesize);
int hidasp_program_enable (int delay);
int		UsbGetDevID(void);

#define	REPORT_ID1			0	// 8  REPORT_COUNT(6)
#define	REPORT_ID4			0	// 40 REPORT_COUNT(38)

#define	REPORT_LENGTH1		65	// 8  REPORT_COUNT(6)
#define	REPORT_LENGTH4		65	// 40 REPORT_COUNT(38)

#define	PAGE_WRITE_LENGTH	32	// Page Write�ł�32byte�P�ʂ̓]����S�|����.
								// Length5���7�o�C�g���Ȃ��l�ł���K�v������.

//	�ő�̒��������� HID ReportID,Length
#define	REPORT_IDMAX		REPORT_ID1
#define	REPORT_LENGTHMAX	REPORT_LENGTH1

#endif

