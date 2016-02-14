; Tabsize: 4
;-----------------------------------------------------------------------------
;	H I D m o n  : ���C������
;-----------------------------------------------------------------------------
	#include "p18fxxxx.inc"
	#include "usb.inc"
	#include "boot.inc"
	#include "boot_if.inc"
	#include "usb_defs.inc"
	#include "hidcmd.inc"
	#include "io_cfg.inc"
;-----------------------------------------------------------------------------
; ���JAPI:
;	hid_process_cmd		// HID_Report����͂��A�ԓ��p�P�b�g���쐬����.
;	cmd_echo			// �G�R�[�o�b�N���s��.
;	cmd_peek			// �������[�ǂݏo�����s��.
;	cmd_poke			// �������[�������݂��s��.
;-----------------------------------------------------------------------------
; ��v���[�N:
;	boot_cmd[64];		// �z�X�g���瑗�����ꂽHID_Report�p�P�b�g.
;	boot_rep[64];		// �z�X�g�ɕԑ�����HID_Report�p�P�b�g.
;-----------------------------------------------------------------------------

;//	Version 1.1
#define	DEV_VERSION_H	1
#define	DEV_VERSION_L	1
#define	DEV_BOOTLOADER	1
;-----------------------------------------------------------------------------
;	�O���֐�.
;-----------------------------------------------------------------------------
	extern	cmd_page_tx		; Flash�������ݏ���.
	extern	cmd_page_erase	; Flash����.
	extern	usb_state_machine

; write eeprom EEADR,EEDATA must be preset, EEPGD must be cleared       
	extern	eeprom_write

;-----------------------------------------------------------------------------
;	�O���ϐ�(�o�b�t�@).
;-----------------------------------------------------------------------------
	extern	ep1Bo
	extern	ep1Bi
;;	extern	boot_cmd		; cmd��M�p�o�b�t�@.
;;	extern	boot_rep		; rep���M�p�o�b�t�@.

	extern	SetupPktCopy
	extern	usb_init

#if USE_SRAM_MARK
	extern	usb_initialized
#endif

;-----------------------------------------------------------------------------
;	�O���[�o���ϐ�.
;-----------------------------------------------------------------------------
	
	global	cmdsize;
;-----------------------------------------------------------------------------
;	���[�J���ϐ�.
;-----------------------------------------------------------------------------
BOOT_DATA	UDATA

cmdsize		res	1	; �ǂݏo���T�C�Y.
area		res	1	; �ǂݏo���G���A.
ToPcRdy		res	1	; �R�}���h���s���ʂ�PC�ɕԋp����Ȃ�1.

poll_mode	res	1	; POLL�R�}���h��t���Ɏ��s����ǂݎ�胂�[�h (0=digital 0xAx=analog)
poll_addr_l	res	1	; POLL�R�}���h��t���Ɏ��s���郁�����[�ǂݏo���A�h���X
poll_addr_h	res	1	; POLL�R�}���h��t���Ɏ��s���郁�����[�ǂݏo���A�h���X

;pollstat	res	1	; POLL�R�}���h�҂�=1 POLL ���s�ς�=0
;str_chr		res	1	; �����o�͗p�e���|�������[�N
;key_chr		res	1	; �������͗p�o�b�t�@(�P�����̂�) 0 �̂Ƃ��͓��͖���.
;hid_chr		res	1	; HID�u���b�N����M������1.
;snapcnt		res 1

#if	0
		global	BiosPutcBuf
		global	BiosGetsBuf

;	Putc/Getc�p
BiosPutcBuf		res		8	;;64
BiosGetsBuf		res		8	;;64
#endif

		global	boot_cmd
		global	boot_rep
;-----------------------------------------------------------------------------
HID_BUF	UDATA	DPRAM+0x70

boot_cmd		res		64	;;EP0_BUFF_SIZE
boot_rep		res		64	;;BOOT_REP_SIZE	; CtrlTrfData�Ƌ��p�ɂ��܂�.

;--------------------------------------------------------------------------
;//	�������[���.
#define	AREA_RAM     0
#define	AREA_EEPROM  0x40
#define	AREA_PGMEM   0x80
#define	AREA_MASK	 0xc0
#define	SIZE_MASK	 0x3f


; boot_cmd[64] �̓���.
#define	size_area	boot_cmd+1	;size(0..63)|area(bit7,6)
#define	addr_l		boot_cmd+2
#define	addr_h		boot_cmd+3
#define	data_0		boot_cmd+4	;�������݃f�[�^.
#define	data_1		boot_cmd+5	;�������݃}�X�N.



#define	UOWNbit		7

#define	REPLY_REPORT	0xaa


;#define mHIDRxIsBusy()              HID_BD_OUT.Stat.UOWN
;#define mHIDTxIsBusy()              HID_BD_IN.Stat.UOWN



BOOT_ASM_CODE	CODE

;-----------------------------------------------------------------------------
;	
;-----------------------------------------------------------------------------
	global	bios_task
bios_task
	movlb	GPR0
	;;; �A�v�����P�̋N�����āA�ŏ��̂P��ڂ�bios_task���Ă΂ꂽ��A
	;;; usb�̏��������s���K�v������.
#if USE_SRAM_MARK
	if_ne	usb_initialized  ,0x55,		bra,re_init
	if_ne	usb_initialized+1,0xaa,		bra,re_init
	bra		hid_process_cmd
#endif

	;; USB �������������o�����ꍇ�A�ď�����.
re_init
	rcall	usb_init
	;;; ������
;-----------------------------------------------------------------------------
;	HID�p�P�b�g�ɑ΂��鏈���R�[�h.
;-----------------------------------------------------------------------------

	global	hid_process_cmd
hid_process_cmd
	movlb	GPR0

	rcall	usb_state_machine

;	// �ԓ��p�P�b�g����ł��邱�ƁA���A
;	// �����Ώۂ̎�M�f�[�^������.
;	if((!mHIDRxIsBusy())) {

	btfsc	ep1Bi ,UOWNbit					; SIE �ғ���?(�ԓ���)
	bra		hid_proc_end					; �ғ����Ȃ̂ŃR�}���h�������Ȃ�.

	btfsc	ep1Bo ,UOWNbit					; SIE (�R�}���h��M��)
	bra		hid_proc_poll					; �R�}���h�͓͂��Ă��Ȃ�.


; �R�}���h����
;	{
		rcall	switch_case_cmd
;;;		rcall	led0_flip
;;;		rcall	snapshot

		;; ����M���L�b�N.
;		lfsr	FSR0 , ep1Bo
;		rcall	mUSBBufferReady
;	}
hid_proc_1
;	// �K�v�Ȃ�A�ԓ��p�P�b�g���C���^���v�g�]��(EP1)�Ńz�X�gPC�ɕԋp����.
;	if( ToPcRdy ) {
;		if(!mHIDTxIsBusy()) {
;			HIDTxReport64((char *)&PacketToPC);
;			ToPcRdy = 0;
;
;			if(poll_mode!=0) {
;				if(mHIDRxIsBusy()) {	//�R�}���h�����Ȃ����著�葱����.
;					make_report();
;				}
;			}
;		}
;	}
;	rcall	led0_flip

	if_eq	ToPcRdy	, 0 , 	bra,hid_proc_2	; ToPcRdy==0�Ȃ�USB�ԓ����Ȃ�.
	btfsc	ep1Bi ,UOWNbit					; SIE �ғ���?(�ԓ���)
	bra		hid_proc_3						; �ғ����Ȃ̂ŕԓ����Ȃ�.
		
		clrf	ToPcRdy
		;; �ԐM���L�b�N.
		lfsr	FSR0 , ep1Bi
		rcall	mUSBBufferReady
;;		bra		hid_proc_3

hid_proc_2

hid_proc_3

	;; ����M���L�b�N.
	lfsr	FSR0 , ep1Bo
;;	rcall	mUSBBufferReady
;;	return

;#define mUSBBufferReady(buffer_dsc)                                         \
;{                                                                           \
;    buffer_dsc.Stat._byte &= _DTSMASK;          /* Save only DTS bit */     \
;    buffer_dsc.Stat.DTS = !buffer_dsc.Stat.DTS; /* Toggle DTS bit    */     \
;    buffer_dsc.Stat._byte |= _USIE|_DTSEN;      /* Turn ownership to SIE */ \
;}
mUSBBufferReady
	movlw	64
	st		PREINC0
	ld		POSTDEC0
	
	ld		INDF0
	xorlw	_DTSMASK
	andlw	_DTSMASK
	st		INDF0
	iorlw	_USIE|_DTSEN
	st		INDF0
hid_proc_end
	return


;-----------------------------------------
hid_proc_poll
;;	btfsc	ep1Bi ,UOWNbit					; SIE �ғ���?(�ԓ���)
;;	bra		hid_proc_end					; �ғ����Ȃ̂ŃR�}���h�������Ȃ�.

	if_eq	poll_mode,0		,bra,hid_proc_poll_end

		rcall	make_report
		;; �ԐM���L�b�N.
		lfsr	FSR0 , ep1Bi
		rcall	mUSBBufferReady

hid_proc_poll_end
	return

#if	0	;// debug only
led0_flip
	btfsc	LED,LED_PIN0
	bra		led0_off
led0_on
	bsf		LED, LED_PIN0	;; debug
	return
led0_off
	bcf		LED, LED_PIN0	;; debug
	return

snapshot
	lfsr	FSR2,0x400
	lfsr	FSR0,0
	movlw	0
	rcall	cmd_peek_ram_l	;; fsr2->fsr0

	incf	snapcnt
	movff	snapcnt,0x6f
	return
#endif

;-----------------------------------------------------------------------------
;	hidmon�R�}���h�ɑ΂��鏈���R�[�h.
;-----------------------------------------------------------------------------
switch_case_cmd
	;; boot_cmd[] �̍ŏ��̃o�C�g�� boot_rep[]�ɃR�s�[.
	ld		boot_cmd
	st		boot_rep

	andlw	1
	st		ToPcRdy

	ld		boot_cmd
	dcfsnz	WREG	; HIDASP_TEST         1 ;//�G�R�[�o�b�N(R)
	bra		cmd_echo		
	dcfsnz	WREG	; HIDASP_BOOT_EXIT	  2 ;//bootload���I�����A�A�v���P�[�V�������N������.
	bra		cmd_reset		
	decf	WREG	; reserved            3

	dcfsnz	WREG	; HIDASP_POKE         4	;//�������[��������.
	bra		cmd_poke		
	dcfsnz	WREG	; HIDASP_PEEK         5	;//�������[�ǂݏo��.(R)
	bra		cmd_peek		
	dcfsnz	WREG	; HIDASP_JMP	      6	;//�w��Ԓn�̃v���O�������s.
	bra		cmd_jmp			
	dcfsnz	WREG	; HIDASP_SET_MODE     7	;//poll���[�h�̐ݒ� (R)
	bra		cmd_set_mode	
	dcfsnz	WREG	; HIDASP_PAGE_ERASE	  8 ;//Flash����.
	bra		cmd_page_erase	
	dcfsnz	WREG	; HIDASP_KEYINPUT	  9 ;// �z�X�g���̃L�[�{�[�h�𑗂�.
	bra		cmd_keyinput	
    dcfsnz	WREG    ; HIDASP_PAGE_WRITE   10;//
	bra		cmd_page_tx		
;;-----------------------------------------------------------------------------
;;	�s���ȃp�P�b�g�ɑ΂��鉞��.
;;-----------------------------------------------------------------------------
unknown_cmd
return_hid_process_cmd
	return



;-----------------------------------------------------------------------------
;	boot_rep[64] �ԋp�o�b�t�@�̃Z�b�g�A�b�v.
;-----------------------------------------------------------------------------

#ifdef __18F14K50
#define	DEVICE_ID	DEV_ID_PIC18F14K
#else
#define	DEVICE_ID	DEV_ID_PIC
#endif

;-----------------------------------------------------------------------------
;	buf[0] = HIDASP_ECHO;
;	buf[1] = ECHO BACK DATA;
cmd_echo
	lfsr	FSR0 , boot_rep+1
;;	movff	boot_cmd 		, POSTINC0	; [0] = CMD_ECHO
	movlf	DEVICE_ID		, POSTINC0	; [1] = DEV_ID
	movlf	DEV_VERSION_L	, POSTINC0	; [2] = HIDmon Device Version lo
	movlf	DEV_VERSION_H	, POSTINC0	; [3] = HIDmon Device Version hi
	movlf	DEV_BOOTLOADER	, POSTINC0	; [4] = AVAILABLE BOOTLOADER FUNC
	movff	boot_cmd+1   	, POSTINC0	; [5] = ECHO BACK DATA
	return



;-----------------------------------------------------------------------------
;	�ϐ� cmdsize �� area ���Z�b�g����.
;	buf[1] = HIDASP_PEEK;
;	buf[2] = size | area;
;
	global	get_size_arena
get_size_arena
	ld		size_area
	andlw	SIZE_MASK
	
	bnz		get_size_a1
	movlw	SIZE_MASK + 1	; size==0 �� 64�Ɖ��߂���.
get_size_a1
	st		cmdsize

	ld		size_area
	andlw	AREA_MASK
	st		area
	return

;-----------------------------------------------------------------------------
;	buf[0] = HIDASP_PEEK;
;	buf[1] = size | area;
;	buf[2] = addr;
;	buf[3] =(addr>>8);
cmd_peek
	;; �]����� boot_rep
	lfsr	FSR0 , boot_rep
	
	rcall	get_size_arena
	bz		cmd_peek_ram
	if_eq	area,AREA_EEPROM	,bra ,cmd_peek_eeprom
;-----------------------------------------------------------------------------
;	ROM �ǂݏo��.
;-----------------------------------------------------------------------------
cmd_peek_rom
	;; �ǂݏo���� (ROM) �A�h���X���Z�b�g.
	clrf	TBLPTRU
	movff	addr_h, TBLPTRH
	movff	addr_l, TBLPTRL

	;; �ǂݏo���恁���M�o�b�t�@���Z�b�g.
	;lfsr	FSR0 , boot_rep
	;; ReportID ���Z�b�g.
	;;movlf	REPORT_ID1 , POSTINC0

	;; �]������ WREG �ɃZ�b�g.
	movf	cmdsize , W
cmd_peek_rom_l
	tblrd*+						;; ROM����ǂݏo��.
	movff	TABLAT , POSTINC0	;; ROM�̃��b�`�� ���M�o�b�t�@�ɓ]��.
	decfsz	WREG
	bra		cmd_peek_rom_l			;; �]�����������J��Ԃ�.
cmd_peek_rom_q
	return
;-----------------------------------------------------------------------------
;	RAM �ǂݏo��.
;-----------------------------------------------------------------------------
cmd_peek_ram
	movff	addr_h, FSR2H
	movff	addr_l, FSR2L

	;; �]������ WREG �ɃZ�b�g.
	movf	cmdsize , W

memcpy_fsr2to0

cmd_peek_ram_l
	movff	POSTINC2 , POSTINC0		;; RAM�̃G���A�� ���M�o�b�t�@�ɓ]��.
	decfsz	WREG
	bra		cmd_peek_ram_l			;; �]�����������J��Ԃ�.
cmd_peek_ram_q
	return

;-----------------------------------------------------------------------------
;	RAM �ǂݏo��.
;-----------------------------------------------------------------------------
cmd_peek_eeprom
	ld		addr_l		; EEPROM address
	st		EEADR
	clrf	EECON1, W

	;; �]������ WREG �ɃZ�b�g.
	;ld		cmdsize		--> WREG�͎g�킸����dec����.
cmd_peek_eeprom_l
	bsf		EECON1, RD			; Read data
	ld		EEDATA
	st		POSTINC0
	incf	EEADR, F			; Next address
	decfsz	cmdsize			;WREG
	bra		cmd_peek_eeprom_l
	return
;-----------------------------------------------------------------------------


;-----------------------------------------------------------------------------
;	buf[0] = HIDASP_POKE;
;	buf[1] = size | area;
;	buf[2] = addr;
;	buf[3] =(addr>>8);
;	buf[4] = data_0;
;	buf[5] = data_1;
cmd_poke
	rcall	get_size_arena
	bz		cmd_poke_ram
;;	if_eq	area,AREA_EEPROM	,bra ,cmd_poke_eeprom
;-----------------------------------------------------------------------------
;	EEPROM ��������.
;-----------------------------------------------------------------------------
cmd_poke_eeprom
	ld		addr_l		; EEPROM address
	st		EEADR
	clrf	EECON1, W

;;write_eeprom_loop
	ld		data_0
	st		EEDATA
	bcf		EECON1, EEPGD	; Access EEPROM (not code memory)
	rcall	eeprom_write
	btfsc	EECON1, WR			; Is WRITE completed?
	bra		$ - 2				; Wait until WRITE complete
;	incf	EEADR, F			; Next address
;;	decfsz	cntr
;;	bra		write_eeprom_loop
	bcf		EECON1, WREN	; Disable writes
	return

;	flash.asm ���Ɏ���.
;eeprom_write
;	bcf		EECON1, CFGS	; Access code memory (not Config)
;	bsf		EECON1, WREN	; Enable write
;	movlf	0x55,EECON2
;	movlf	0xAA,EECON2
;	bsf		EECON1, WR	; Start flash/eeprom writing
;	clrf	hold_r		; hold_r=0
;	return

;-----------------------------------------------------------------------------
;	RAM ��������.
;-----------------------------------------------------------------------------
;	uchar data=cmd->memdata[0];
;	uchar mask=cmd->memdata[1];
;	if(mask) {	//�}�X�N�t�̏�������.
;		*p = (*p & mask) | data;
;	}else{			//�ׂ���������.
;		*p = data;
;	}

cmd_poke_ram
	movff	addr_h, FSR0H
	movff	addr_l, FSR0L
	ld		data_1
	bz		direct_write_ram
; MASK ��������.
	andwf	INDF0 , W
	iorwf	data_0, W
	st		data_0
direct_write_ram
	movff	data_0 , POSTINC0		;; RAM�̃G���A����������.
	return


#if	0
;-----------------------------------------------------------------------------
;	USB: HID_Report IN ����Ăяo�����.
;-----------------------------------------------------------------------------
	global	cmd_poll
cmd_poll
;;	movlw	REPORT_ID2				; HID ReportID = 4 (poll)
	cpfseq	(SetupPktCopy + wValue)	; request HID_ReportID
	return
	;; if( wValue == REPORT_ID2 ) {
		movlw	0
		cpfseq	poll_mode
		;; if ( pagemode != 0 ) goto cmd_poll_string
		bra		cmd_poll_string

		;; else {
			movff	pageaddr_l,FSR0L
			movff	pageaddr_h,FSR0H
			ld		INDF0 				; �|�[�g�ǂݎ��.
;;;			st		boot_rep + 1		; �ԋp�o�b�t�@[1]�ɏ���.
			movff	WREG,boot_rep + 1	; �ԋp�o�b�t�@[1]�ɏ���.
;;			movlf	REPORT_ID2,boot_rep	; HID ReportID = 2 (poll)�� �ԋp�o�b�t�@[0]�ɏ���.
		;; }
	;; }

	return
#endif

#if	0
;-----------------------------------------------------------------------------
;	USB: �z�X�gPC����̔C�ӂ�HID�f�[�^(63byte)���󂯎��.
;-----------------------------------------------------------------------------
;cmd_gethid
;--- EP0 in �ɂ��̂܂܃R�s�[����.
;	lfsr	FSR0,BiosGetsBuf
;	lfsr	FSR2,boot_rep
;	movlw	64
;	rcall	memcpy_fsr2to0		; memcpy(boot_rep,BiosPutcBuf,62);
;	movlf	1,hid_chr
;	return
;-----------------------------------------------------------------------------
;	USB: HID_Report IN ����Ăяo�����.
;	printf��������z�X�g�o�b�ɑ���.
;-----------------------------------------------------------------------------
;	������f�[�^�̊i�[�ꏊ:
;		BiosPutcBuf[2]     = ������.
;		BiosPutcBuf[3�`63] = ������.
;	�ȉ��͌Œ�l:
;		BiosPutcBuf[0]     = REPORT_ID2.
;		BiosPutcBuf[1]     = 0xc0 �ԋp��񂪕�����ł��邱�Ƃ������}�[�N.
;
cmd_poll_string
	lfsr	FSR2,BiosPutcBuf
;;	movlf	REPORT_ID2,POSTINC2			; HID ReportID = 2 (poll)��BiosPutcBuf[0]�ɏ���.
	movff	pagemode,  POSTINC2			; String Mark �� BiosPutcBuf[1]�ɏ���.
;--- EP0 in �ɂ��̂܂܃R�s�[����.
	lfsr	FSR2,BiosPutcBuf
	lfsr	FSR0,boot_rep
	movlw	62
	rcall	memcpy_fsr2to0		; memcpy(boot_rep,BiosPutcBuf,62);
	clrf	pollstat
;--- �����������Z�b�g.
	lfsr	FSR0,BiosPutcBuf+2
	clrf	INDF0
	return
#endif

#if	0
;-----------------------------------------------------------------------------
;	API: �P�����L�[����. ���͂Ȃ��̏ꍇ�O��Ԃ�.  ����=>WREG
;-----------------------------------------------------------------------------
	global	bios_getc
bios_getc
	movlb	GPR0
	ld		key_chr
	clrf	key_chr
	return
;-----------------------------------------------------------------------------
;	API: �P�����o��. (WREG) ===> BiosPutcBuf �ɗ��߂�.
;-----------------------------------------------------------------------------
;		��t�ɂȂ�����AUSB�ʐM�̊�����҂��āA�܂����߂�.
	global	bios_putc
bios_putc
	movlb	GPR0

	st		str_chr
	lfsr	FSR0,BiosPutcBuf+2	;; ������.
	if_ge	INDF0 , 59,		rcall, bios_putc_flush	;;���ł�60�����o�^�ς�.

	ld		INDF0				;; WREG=������
	addlw	LOW(BiosPutcBuf+3);	;; ������o�b�t�@�̐擪.
	st		FSR0L				;; ������o�b�t�@�̌��݈ʒu.
	
	movff	str_chr , INDF0		;; �����̕�����BiosPutcBuf[3+cnt]�Ɋi�[.

	lfsr	FSR0,BiosPutcBuf+2	;; ������.
	incf	INDF0				;; ������ cnt ��+1.

	return
;-----------------------------------------------------------------------------
;		��t�ɂȂ�����AUSB�ʐM�̊�����҂��āA�܂����߂�.
;-----------------------------------------------------------------------------
bios_putc_flush
	rcall	bios_task
	lfsr	FSR0,BiosPutcBuf+2	;; ������.
	if_ge	INDF0 , 59,		bra, bios_putc_flush	;;���ł�60�����o�^�ς�.


	return

#endif

;-----------------------------------------------------------------------------
;	API: HID Report�ɂ�镶����]�����[�h�̐ݒ�.
;-----------------------------------------------------------------------------
;	pagemode = 0    : ���ʂ� usb_poll (Graph�R�}���h�Ŏg�p)
;	pagemode = 0xAx : HIDmon-2313�ł̃A�i���O���̓T�|�[�g�R�}���h.
;	pagemode = 0xc0 : �ʏ�̕�����]��.(�z�X�gPC�ւ̈�����胂�[�h)
;	pagemode = 0xc9 : �A�v���P�[�V�����I���\�� (�z�X�gPC��Terminal���[�v�𔲂���)
;
;;	global	bios_setmode
;bios_setmode
;	movlb	GPR0
;	st		poll_mode
;
;	return
;-----------------------------------------------------------------------------
;	���s.
;-----------------------------------------------------------------------------
;	uchar bootflag=PacketFromPC.raw[5];
;	if(	bootflag ) {
;		wait_ms(10);
;		usbModuleDisable();		// USB����U�؂藣��.
;		wait_ms(10);
;	}
cmd_jmp
;;	if_eq	data_1,0	,	bra,cmd_jmp_1

	;; USB disconnect
	dcfsnz	data_1			; data_1 == 1 �Ȃ� USB��؂藣��.
	rcall	usb_disconnect	; Disable USB Engine


cmd_jmp_1
	clrf	PCLATU
	ld		addr_h
	st		PCLATH
	ld		addr_l

	movlb	0
	st		PCL
	return						;; ���Ԃ�s�v.

;-----------------------------------------------------------------------------
;	Reset����.
;-----------------------------------------------------------------------------
cmd_reset
	rcall	usb_disconnect	 ; Disable USB Engine

#if USE_SRAM_MARK
	movlf	0x55,usb_initialized
	movlf	0x5e,usb_initialized+1
#endif

	reset

;-----------------------------------------------------------------------------

usb_disconnect
	rcall	delay_loop
	bcf     UCON,USBEN      ; Disable USB Engine

delay_loop
	; Delay to show USB device reset
	clrf	cmdsize
cmd_reset_1
	clrf	WREG
cmd_reset_2
	decfsz	WREG
	bra		cmd_reset_2
	decfsz	cmdsize
	bra		cmd_reset_1
	return

;-----------------------------------------------------------------------------
;	buf[0] = HIDASP_SET_MODE;
;	buf[1] = mode (digital=0, analog=0xAx) ;
;	buf[2] = addr;
;	buf[3] =(addr>>8);
;	CMD_POLL �œǂݏo���|�[�g�ƃ��[�h�����炩���߃Z�b�g����.
cmd_set_mode
	movff	size_area,poll_mode		; size�l�� �ǂݎ�胂�[�h�Ƃ��Ĉ���.
	movff	addr_l	 ,poll_addr_l
	movff	addr_h	 ,poll_addr_h

make_report
;	//�T���v���l���P�����Ԃ�����.
	movlf	REPLY_REPORT , boot_rep		;// �R�}���h���s������HOST�ɒm�点��.
	;;		PacketToPC.raw[1] = 1;
	movlf	1			 , boot_rep+1	;//�T���v����.
	;;		PacketToPC.raw[2] = *poll_addr;
	;; {
		movff	poll_addr_l,FSR0L
		movff	poll_addr_h,FSR0H
		ld		INDF0 				; �|�[�g�ǂݎ��.
		st		boot_rep + 2		; �ԋp�o�b�t�@[2]�ɏ���.
	;; }
;	movlf	1,ToPcRdy
;;	return

;-----------------------------------------------------------------------------
;	buf[1] = HIDASP_KEYINPUT;
;	buf[2] = KEY Charactr
;	�z�X�g����L�[���͂�����ꂽ.
cmd_keyinput
;;	movff	size_area,key_chr		; size�l�� Character �Ƃ��Ĉ���.
	return
;-----------------------------------------------------------------------------
;
;-----------------------------------------------------------------------------

	END
