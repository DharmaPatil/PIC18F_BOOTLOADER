�� �T�v

  ����́AMicroChip���񋟂��Ă��� PIC18 ��USB�A�v���P�[�V�����t���[�����[�N
  �Ɋ܂܂�Ă���HID-Bootloader �����Ƃɂ��č쐬���� PIC18F��p�̊ȈՃ��j�^�ł��B



�� �r���h���̍\�z�̎����

�i�P�j
  �܂��AWinAVR(GNU Make) ���C���X�g�[�����܂��B
  http://sourceforge.net/projects/winavr/
  �C���X�g�[����́A�ʏ�Ȃ� C:\WinAVR\ �ɂȂ�܂��B
  WinAVR/utils/bin �ɂ́Amake.exe �ȊO�ɂ�unix�V�F���ł悭�g�p���� ls �� cat , rm
  �ȂǂƂ�����������݂̃c�[����Win32�o�C�i���[���܂܂�Ă���̂ŁA���ɕ֗��ł��B
  
�i�Q�j
  ���ɁAmcc18(Compiler)���C���X�g�[�����܂��BStandard-Eval Version��OK�ł��B
  http://www.microchip.com/
  �C���X�g�[����́A�ʏ�Ȃ� C:\mcc18\ �ɂȂ�܂��B
  
�i�R�j
  �����āAMicroChip�̃T�C�g����A���LUSB�A�v���P�[�V�������C�u�����A
  MicrochipApplicationLibrariesv2009-07-10.zip
  �������͂�����V�����o�[�W��������肵�Ă��������B


  �{�f�B���N�g���́A
  MicrochipApplicationLibrariesv2009-07-10.zip
  �̓��e�̈ꕔ���AGNU Make�r���h��ʂ��ړI�ōĔz�u�A�č\���������̂ł��B


  �������o������A�p�X��ʂ��܂��B
#  �E�p�X�̒ʂ���:
#    PATH %PATH%;C:\mcc18\bin;C:\mcc18\mpasm;C:\WinAVR\utils\bin;
#                ~~~~~~~~~    ~~~~~~~~ ��������mcc18�̃C���X�g�[����ɉ����ēǂݑւ��Ă�������.
  �K���ȃo�b�`�t�@�C����p�ӂ��ČĂяo�����A���邢��Windows�̃V�X�e���v���p�e�B
  -->�ڍ�-->���ϐ�-->���[�U�[�̊��ϐ�
  PATH �� C:\mcc18\bin;C:\mcc18\mpasm;C:\WinAVR\utils\bin
  ���L�q���܂��B
  �C���X�g�[�����Ƀp�X��ʂ��Ă��܂����ꍇ�́A��L�m�F�݂̂Ō��\�ł��B


�� �t�@�C���ꗗ

ReadMe.txt			.....      ���̃t�@�C��.
Makefile            .....      GNU Make���g�p���܂�.
                              (18F2550�p��18F4550�p�͋���HEX�ł�)
srec2bin.exe        .....      HEX�t�@�C�����_���v�`���ɕϊ�����c�[���ł�.
mplistconv.exe      .....      LST�t�@�C�������₷������c�[���ł�.


���i��ʂ̃����J�[�X�N���v�g:
rm18F14K50.lkr      .....	   18F14K50�p�̃����J�[�X�N���v�g
rm18F2550.lkr       .....	   18F2550�p�̃����J�[�X�N���v�g
rm18F4550.lkr       .....	   18F4550�p�̃����J�[�X�N���v�g


���\�[�X:
main.c              .....      
monit.c             .....      
picwrt.c            .....      
timer2.c            .....      
ps2keyb.c           .....      
print.c             .....      
keybtest.c          .....      
usbdsc.c            .....      
usb/usbmmap.c       .....      
usb/usbctrltrf.c    .....      
usb/usbdrv.c        .....      
usb/hid.c           .....      
usb/usb9.c          .....      

���w�b�_�[�t�@�C��:
fuse-config.h
io_cfg.h
hidcmd.h
monit.h
usbdsc.h
usb/usbcfg.h
usb/usbdrv.h
usb/usbmmap.h
usb/typedefs.h
usb/usbdefs_ep0_buff.h
usb/usbdefs_std_dsc.h
usb/usb.h
usb/usb9.h
usb/hid.h
usb/usbctrltrf.h

���g�p���Ȃ��t�@�C��
mchip-src/bootmain.c
mchip-src/BootPIC18NonJ.c
mchip-src/BootPIC18NonJ.h

�� ���p��

��PIC18F14K50 / PIC18F2550 ���Ή�.

  ���XMicroChip�� cdc-serial emulator�͑��i��Ή��ł����A�����Makefile��
    DEVICE=18F2550 
  �̍s�����������邱�ƂŁAPIC18F14K50�ɂ��Ή������邱�Ƃ��o���܂��B
  
  makeall.bat ���R�}���h���C���Ŏ��s����ƁA������HEX�������܂��B

  �܂��A18F4550 �� 18F2550��HEX�����̂܂ܗ��p�ł���悤�ł��B

�� ���Ɏg���܂����H

 �Epicmonit.exe ��̃R�}���h�ƁAfirmware��̃R�}���h�󂯎�菈���̑΂�
 �@�����Œǉ����邱�Ƃɂ��A���낢��ȋ@�\��ǉ����邱�Ƃ��o���܂��B


 �Emain.c �̈ȉ��̃X�C�b�`��L��(1)�ɂ��āA
	#define	TIMER0_INTERRUPT	0		// �^�C�}�[�O���荞�݂��g�p����.
	#define	USE_PS2KEYBOARD		0		// PS/2�L�[�{�[�hI/F ���g�p����.
   
   Makefile��OBJS�ɉ��L�R�����g�A�E�g���ꂽ�R�s��L���ɂ���ƁA�ꉞPS/2
   �L�[�{�[�h�̑Ō����͂̃n���h�����O���m�F���邱�Ƃ��ł���悤�ł��B
�@�@�i���쒆��LED���_���܂��B�܂��A���쒆�ɃL�[�{�[�h���̓o�b�t�@���e��
�@�@�@�_���v���Ċm�F���邱�Ƃ��o���܂��j

OBJS = \
	main.o		\
	monit.o		\
	usbdsc.o	\
	usb/hid.o	\
	usb/usb9.o	\
	usb/usbctrltrf.o	\
	usb/usbdrv.o		\
	usb/usbmmap.o		\

#	timer0.o	\
#	task.o		\
#	ps2keyb.o	\

