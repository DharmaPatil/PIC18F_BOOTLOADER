�� �T�v

  ����́AMicroChip���񋟂��Ă��� PIC18 ��USB�A�v���P�[�V�����t���[�����[�N
  �Ɋ܂܂�Ă���HID-Bootloader �����Ƃɂ��č쐬���� PIC18F��p�̊ȈՃ��j�^�ł��B

�� ���݂̃X�e�[�^�X

  �i�P�jPIC 18F2550/18F4550/18F14K50 ��œ��삵�܂��B
  �i�Q�jpicmonit.exe ���g���܂��B
  �i�R�jhidaspx.exe �̉��o�[�W����picspx-gcc�������܂��B
		���݂͏������݃G���[���������܂��B---> �n�[�h�E�F�ASPI���g���ƃf�[�^����������
		����悤�ł��B���݂̓\�t�g�E�F�ASPI�ŉ�����Ă��܂��B
  �i�S�jpicwriter �̉��o�[�W�����������܂��B
        picwriter�� LVP�������݂̂ł���PIC�}�C�R���Ƀt�@�[�����������݂��Ƃ��o���܂��B
  �i�T�jPIC24F�p��writer24.exe (���o�[�W����)�������܂��B

�� ������

  �܂��Apicboot ���g�p���ăt�@�[���E�F�A���������݂܂��B
  C:> picboot -r firmware/picmon-18F2550.hex

  ���ɁApicmonitor ���N�����܂��B
  C:> cd picmon
  C:picmon> picmonit.exe 

  ���ݎ�������Ă���R�}���h�̎�Ȏg�����ł��B

TARGET DEV_ID=25

�������[�_���v(SRAM)
PIC> d
000000 00 00 40 00 20 78 02 00
000008 08 41 22 68 05 00 07 20
000010 bf 04 02 80 ac 40 84 41
000018 5d 44 88 83 05 03 c4 41
000020 fe 20 85 84 0c e9 24 cb
000028 36 50 8c 22 22 f8 51 21
000030 04 44 25 dc 02 c0 31 14
000038 81 09 48 d4 43 10 d6 35

�t�A�Z���u��(FLASH)
PIC> l 0
0000 6af7        clrf   0xf7, 0
0002 6af8        clrf   0xf8, 0
0004 d054        bra    0xae
0006 d330        bra    0x668
0008 ef04 f004   goto   0x808
000c d05d        bra    0xc8
000e d27b        bra    0x506
0010 d328        bra    0x662
0012 d32c        bra    0x66c
0014 d32f        bra    0x674
0016 d345        bra    0x6a2
0018 ef0c f004   goto   0x818
001c 0112        movlb  0x12
001e 0200        mulwf  0, 0
0020 0000        nop
0022 4000        rrncf  0, 0, 0
0024 04d8        decf   0xd8, 0, 0
0026 003c        dw     0x3c  ;unknown opcode
PIC> q
Bye.
C:>

���̑��̃R�}���h
PIC> ?
* HID_Monit Ver 0.1
Command List
 d  <ADDRESS1> <ADDRESS2>    Dump Memory(RAM)
 dr <ADDRESS1> <ADDRESS2>    Dump Memory(EEPROM)
 dp <ADDRESS1> <ADDRESS2>    Dump Memory(PGMEM)
 e  <ADDRESS1> <DATA>        Edit Memory
 f  <ADDRESS1> <ADDRESS2> <DATA> Fill Memory
 l  <ADDRESS1> <ADDRESS2>    List (Disassemble) PGMEM
 p ?                         Print PortName-List
 p .                         Print All Port (column format)
 p *                         Print All Port (dump format)
 p <PortName>                Print PortAddress and data
 p <PortName> <DATA>         Write Data to PortName
 p <PortName>.<bit> <DATA>   Write Data to PortName.bit
 sleep <n>                   sleep <n> mSec
 bench <CNT>                 HID Write Speed Test
 boot                        Start user program
 run  <address>              Run user program at <address>
 user <arg>                  Run user defined function (usercmd.c)
 poll <portName>             Continuous polling port
 poll <portName> <CNT>       continuous polling port
 poll  *  <CNT>              continuous polling port A,B,D
 graph <portName>            Graphic display
 q                           Quit to DOS
------
Topics:

boot�R�}���h�ɃA�h���X������^���邱�Ƃ��o���܂��B

�Ⴆ�΁Abootloader�ɖ߂肽���ꍇ�� boot 0
0x2c00�`�ɏĂ����e�X�g�v���O���������s�������ꍇ boot 2c00
�Ƃ��܂��B

run�R�}���h�Ƃ̈Ⴂ�́AUSB�o�X����U���Z�b�g���邱�Ƃł��B

run�R�}���h�ł̎��s�́AUSB�ڑ��̂܂܂ŁAgoto���߂����s����܂��B

graph�R�}���h�́A�Ď��|�[�g����������ŗ^���܂��B
graph�R�}���h�̑������͈ȉ��̂悤�Ȃ��̂�p�ӂ��Ă��܂��B
 PIC> graph porta trig 0   �������� porta��bit0 ���g���K�[�ɂ���B
 PIC> graph porta infra    �������� porta bit0�ɐԊO�������R����M�f�q��
                �@�ڑ�����Ă���O��ŁA�Ɠd���R�[�h����͂��ĕ\�����܂��B
 PIC> graph analog         �������� AIN���A�i���O�\�����܂��B

graph�R�}���h�̃T���v�����O���[�g�́APIC18F14K50�̏ꍇ���悻1mS�Œ�ɂȂ�܂��B
PIC18F2550/4550�̏ꍇ��10kHz���荞�݃T���v�����O���s���܂��B
�i14K50�Ŋ��荞�݃T���v�����O�o���Ȃ��̂́A�o�b�t�@�������[�e�ʂ̎���ł��j

�T���v�����O���[�g�̕ύX�� PR2���W�X�^�̏��������ōs���Ă݂Ă��������B
 PIC> p pr2 17   �Ȃ�.



�� �f�B���N�g���\��

 +- picspx/ -+-- picspx/     AVR���C�^�[    (gcc)
             |
             +-- picwriter/  PIC18F���C�^�[ (gcc)
             |
             +-- writer24/   PIC24F���C�^�[ (gcc)
             |
             +-- picmon/     �ȈՃ��j�^�[   (gcc)
             |
             +-- firmware/   �t�@�[���E�F�A (mcc18)



�� ��H�} (PIC 18F4550)

circuit.txt ���Q�Ƃ��Ă�������



�� AVR���C�^�[�Ƃ��Ă̎�����

18F2550/18F4550�̂S�{��SPI�M�����������ݐ��AVR�`�b�v�ɐڑ����܂��B

18F4550���pin�ԍ�:�M����  = SPI�[�q(AVR�`�b�v��̃s������)
			-----------------------------
  				25:RC6=TX  = Reset
 				33:RB0=SDI = MISO
  				34:RB1=SCK = SCK
  				26:RC7=SDO = MOSI
			-----------------------------

C:> cd picspx
C:picspx> picspx-gcc.exe  -r

�̂悤�ɂ��Ďg���܂��B

C:picspx> picspx-gcc.exe ��������͂���Ǝg�����̕\�����o�܂��B

picspx-gcc.ini �������f�B���N�g���ɂȂ��ꍇ�́A���Ȃ��Ƃ� -ph
�I�v�V�������蓮�Ŏw�肷��K�v������܂��B





�� PIC���C�^�[�Ƃ��Ă̎�����

  �ڑ�:

 AVR�pISP 6PIN          �������ݑΏ� PIC18F2550/14K50
------------------------------------------------------------
	1 MISO    ------------------>   PGD
	2 Vcc     ------------------>   Vcc
	3 SCK     ------------------>   PGC
	4 MOSI    ------------------>   PGM
	5 RESET   ------------------>   MCLR
	6 GND     ------------------>   GND

 �Epicwriter/picwrite.exe -r 
 �@�����s���āAPIC�̃f�o�C�XID���\���ł���΁A�ڑ��͂��܂������Ă��܂��B
 �ELVP�������݃��[�h�̂Ȃ�PIC��A����HVP(���d��)�������ݍς݂�PIC��
   ����PIC���C�^�[�ł͓ǂݏ����ł��܂���B
 �ELVP�������݌�̃}�C�R���g�p���͏펞PGM�[�q���u�v���_�E���v���Ďg�p����
�@ �K�v������܂��B

==================================================
�� hidmon-14k50 �� hidmon-2550�Ƃ̈Ⴂ

 �E�ꉞ�A�b����ŏ�����Ă��܂��B(mcc18)

 �E�R�[�h�T�C�Y���傫���ł��B(8kB���x)

 �EUSB ��PID���Ⴂ�܂��B

 �E�v���g�R�����Ⴂ�܂��B

 �EHID Report�̓]�����@���قȂ�܂��B
   hidmon�ł́A�S�ăR���g���[���]��(HidD_SetFeature/HidD_GetFeature)
   �ōs���Ă��܂����Apicmonit.exe�ł́AEndPoint1�ɑ΂���C���^���v�g�]��
   �ɂ��f�[�^�̎󂯓n�����s���Ă��܂��B

   ���̂��߁A�C���^���v�g�]���p�P�b�g���f�o�C�X��著�o����Ȃ������
   HID Report���󂯎�邱�Ƃ��ł��܂���B�i�z�X�g���^�C���A�E�g�ɂȂ�܂��j
   ���o���ꂽ�ꍇ�́A�K���󂯎���Ă����Ȃ��ƁA���p�P�b�g�̎�M���ɁA�o�b�t�@
�@ �ɂ��܂����Â��p�P�b�g���󂯎���č������邱�ƂɂȂ�܂��B


�� ���Ɏg���܂����H

 �Epicmonit.exe ��̃R�}���h�ƁAfirmware��̃R�}���h�󂯎�菈���̑΂�
 �@�����Œǉ����邱�Ƃɂ��A���낢��ȋ@�\��ǉ����邱�Ƃ��o���܂��B


�� ���p�P
   -------------------------------------------------------------------------
   PS/2 �^�C�v�̃L�[�{�[�h���q���ŁA�Ō����ꂽ�L�[�R�[�h���P�U�i�_���v���܂�
   -------------------------------------------------------------------------

   �ڑ��F
     
     PORTB.bit0 <---- PS/2 KeyBoard CLK
     PORTB.bit1 <---- PS/2 KeyBoard DATA

   �g�����F
     �i�P�jfirmware/picmon-18F2550.hex ���Ă��܂��B
     �i�Q�j�o�b��ɂāApicmon/picmonit.exe ���N�����܂��B

     ���ʂɃ������[�_���v('D'�R�}���h)��t�A�Z���u��('L'�R�}���h)���g���邱�Ƃ�
     �m�F���܂��B
     
     �i�R�juser�R�}���h����͂��܂��B

     PIC> user
     
       �����āA�q����PS/2�L�[�{�[�h��Ō�����ƁA�R���\�[���ɂP�U�i�ŃR�[�h�\����
       �o�܂��B
       
       �W�O�̃R�[�h���\������邩�A�������̓p�\�R��������[ESC]�L�[����������I���ł��B


�� ���p�Q
   -------------------------------------------------------------------------
   PIC�ォ��printf��puts�������܂��B
   -------------------------------------------------------------------------

   firmware/Makefile �ɋL�q���Ă��� OBJ���� keybtest.o �� usercmd.o �ƒu�������܂��B
   firmware�f�B���N�g���� make clean ���� make ���܂��B
   firmware/picmon-18F2550.hex ���Ă��܂��B
   �o�b��ɂāApicmon/picmonit.exe ���N�����܂��B
   ������user�R�}���h����͂��܂��B
     PIC> user
   ����ŁAPIC�ォ��print���ꂽ�������o�b��Ō��邱�Ƃ��o���܂��B
   
   usercmd.c �����낢�돑�������Ď������Ƃ��o���܂��B


�� ���p�R
   -------------------------------------------------------------------------
   �ԊO�������R���̎���g�`�Ȃǂ��ϑ����邱�Ƃ��o���܂��B
   -------------------------------------------------------------------------
   �����R����M��(38kHz)�̏o�͒[�q��PortA.bit0�Ɍq���ŁA

 PIC> graph porta
�t���[�������[�h�Ŋϑ����܂��B

 PIC> graph porta trig 0
porta bit0�̕ω��ɂ��g���K�[�Ŋϑ����܂��B

 PIC> graph porta infra
porta bit0�̕ω��ɂ��g���K�[�Ŋϑ������̂��A��͌��ʂ��R���\�[���\�����܂��B



�� ���p�S
   -------------------------------------------------------------------------
   PIC24F�f�o�C�X�̃t�@�[���E�F�A�������݂��o���܂��B
   -------------------------------------------------------------------------
   PIC18F14K50��3.3V����Ŏg�p���܂��B
   PIC24F��p�̏������݃c�[���� writer24/ �f�B���N�g���ɂ���܂��B
   �^�[�Q�b�g��PIC24F��ڑ�������A

   C:picspx> writer24\writer24.exe -r

   ����ɂ��APIC24F�f�o�C�X���ƃf�o�C�XID,���r�W����No���\�������ΐڑ���OK�ł��B
   
   �k�d�c�`�J�`�J�T���v��(���ۂɂ�PGD1��Toggle���Ă��܂�)
      writer24/ledtest24/main.hex
   ������r���h����ɂ�MICROCHIP�� C30�R���p�C�����K�v�ł��B


