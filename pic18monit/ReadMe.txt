������ �T�v ������

  ����́AMicroChip���񋟂��Ă��� PIC18 ��USB�A�v���P�[�V�����t���[�����[�N��
  �܂܂�Ă���USB Generic device �����Ƃɂ��č쐬���� PIC18F��p�̊ȈՃ��j�^�ł��B



������ �f�B���N�g���\�� ������ 

pic18monit --+-- firmware /        main-18F14K50.hex �������� main-18F2550.hex
             |                     ��Ή�����PIC�ɏĂ��܂��B
             |
             +-- driver_inf /      WindowsXP�p��USB Generic �f�o�C�X�p inf �t�@�C��
             |
             +-- picmonit /        WindowsXP���̃R�}���h���C���c�[�� picmonit.exe
             |
             +-- libusb /          picmonit.exe ���r���h����ꍇ�Ɏg�p����libusb-win32
                                   ���C�u�����ł��B
             |
             +-- picmonit / test   WindowsXP�p: pic18ctl.dll �̌Ăяo����T���v��.



������ ���C�Z���X ������ 

 MicroChip��USB�t���[�����[�N�̒��쌠�� MicroChip �ɋA������Ă��܂��B
 
 ����������������AWindows�����[�e�B���e�B��GPL���C�Z���X�ł��B

 PIC18�p�t�A�Z���u���̃\�[�X ��GNU gputils�ɗR�����Ă��܂��B




������ �ڍ� ������

�i�P�jWindows��ł̎g����:

 D:> picmonit.exe      �E�E�E�N��
 PIC> help             �E�E�EHELP�\��
 PIC> q                �E�E�E�I��


-------------
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
 ain   <CNT>                 Analog input
 aingraph                    Analog input (Graphical)
 aindebug <mode>             Analog input debug
 reg   <CNT>                 Registance Meter
 reggraph                    Registance Meter (Graphical)
 q                           Quit to DOS
PIC>
-------------


-------------------------------------------------------------------------------------
�i�Q�j�r���h��

-Windows��̃R�}���h���C���c�[���� MinGW-gcc ���g�p���ăr���h���܂��B
-PIC18F�t�@�[���E�F�A�� MicroChip mcc18�R���p�C�����g�p���ăr���h���܂��B
--�ǂ�����r���h�ɂ� make ���g�p���܂��B



-------------------------------------------------------------------------------------
�i�R�j�J�X�^�}�C�Y

-PIC18F�t�@�[���E�F�A�Ƀ��[�U�[��p�̋@�\���ȒP�ɒǉ�����ɂ́A usercmd.c
��������������@������܂��B

-picmonit.exe ���� user <arg> �R�}���h�ɂĎ��s����܂��B



-------------------------------------------------------------------------------------
�i�S�jI/O�|�[�g�Ď�

 PIC> p  �R�}���h��I/O�|�[�g�̏�ԊĎ��ƕύX���\�ł��B
 
��F port��Ԉꗗ
 PIC> p
 
��F LED�̓_��
 PIC> p latc 3
 
��F LED�̏���
 PIC> p latc 0
 
   PORT[ABC] LAT[ABC] TRIS[ABC] �̈Ӗ��̓f�[�^�V�[�g���m�F���Ă��������B
 
 
-------------------------------------------------------------------------------------
�i�T�j���j�^�[�X�N���v�g
 PIC> �v�����v�g��Ԃł̃R�}���h�������o�b�`�t�@�C���Ŏ������ł��܂��B
 �R�}���h�V�[�P���X��K���ȃe�L�X�g�t�@�C��(SCRIPT.TXT)�ɏ�������ŁA

 D:>  picmonit.exe -iSCRIPT.TXT

 �����s����ƁA��A�̃V�[�P���X�����s���܂��B


-------------------------------------------------------------------------------------
�i�U�j�A�i���O�I�V��

  PIC> graph analog�@�@�R�}���h�ɂ���āA�ᑬ�A�i���O�I�V���ɂȂ�܂��B



-------------------------------------------------------------------------------------
�i�V�j��H�}

      pic18spx�݊��ł��B


-------------------------------------------------------------------------------------
�i�W�jLinux��

      ubuntu,debian �Ȃǂ̏ꍇ libusb0-dev ( ������libusb-dev )�p�b�P�[�W���K�v�ł��B
      firmware �� DOS/Linux���ʂł��B
      picmonit �� �ăR���p�C�����Ă��������B
      picmonit �̎��s�̓��[�g�����ōs�����A���邢�� udev ��
      �Y��USB�f�o�C�X�̃A�N�Z�X���������[�U�[�ɋ�����悤�ɂ��܂��B

      Linux�ł̓O���t�B�b�N�������g�p�ł��܂���B

-------------------------------------------------------------------------------------
�i�X�j���̑�

      picmonit/test/ �́Apic18ctl.dll �i��hidmon.dll�����j �̌Ăяo���T���v���ł��B
      ���̂Ƃ���b����݂̂Ńe�X�g���ł��B
      pic18ctl.dll �� picmonit/ �f�B���N�g���ɐ������ꂽ���̂� test/ �ɃR�s�[����
      ���쎎�����s���Ă��������B


-------------------------------------------------------------------------------------
�i�P�O�j���̑�

      �ԊO�������R����͋@�\���i���Ԃ�j�g����͂��ł��Bpic18spx�̃h�L�������g��
�@�@�@�Q�Ƃ��Ă��������B




-------------------------------------------------------------------------------------
