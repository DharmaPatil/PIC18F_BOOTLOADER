�� �T�v

  ����� PIC18F2550/4550/14K50 ���g�p�����AUSB�o���N�]���t���[�����[�N�ł�
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  �EMicroChip���񋟂��Ă��� PIC18 ��USB�A�v���P�[�V�����t���[�����[�N�����ɂ��Ă��܂��B

  �EMPLAB�͎g�킸�ɁAGNU Makefile ���g�p���ăr���h����悤�ɂ��Ă��܂��B

    (wine�Ȃǂ̊��ݒ肳���s���΁ALinux�̃R�}���h���C���E�V�F����Ńr���h�\�ł�)


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
mkall.bat           .....	   �T�|�[�g���Ă���S�i��p��HEX�����܂�.
                              (18F2550�p��18F4550�p�͋���HEX�ł�)
srec2bin.exe        .....      HEX�t�@�C�����_���v�`���ɕϊ�����c�[���ł�.
mplistconv.exe      .....      LST�t�@�C�������₷������c�[���ł�.
  ��L�c�[���� make dumplst �������� make dumphex �Ŏg�p�ł��܂�.
mplistcnv.pl        .....      LST�t�@�C�������₷������c�[����perl��.


���\�[�X:
main.c              .....      ���C�����������𔲂��o��������.
usb_descriptors.c   .....      �f�B�X�N���v�^�e�[�u��.


���w�b�_�[�t�@�C��:
HardwareProfile.h   .....      �`�b�v�i��ɂ��A�n�[�h�E�F�A�v���t�@�C���̃Z���N�^.
Hp_LowPinCount.h    .....	   18F14K50�p�̃n�[�h�E�F�A�v���t�@�C��
Hp_2550.h           .....	   18F2550/4550�p�̃n�[�h�E�F�A�v���t�@�C��
usb_config.h        .....	   USB�̐ݒ�.


���i��ʂ̃����J�[�X�N���v�g:
rm18F14K50.lkr      .....	   18F14K50�p�̃����J�[�X�N���v�g
rm18F2550.lkr       .....	   18F2550�p�̃����J�[�X�N���v�g
rm18F4550.lkr       .....	   18F4550�p�̃����J�[�X�N���v�g

��Windows�p��inf�t�@�C��
driver_inf/

