rem 
rem �J�����gDIR�ɂ��� main-0000.hex��CQ-STARM�ɏ�������Ŏ����I�ɏI������.
rem
rem openocd.exe -f blaster.cfg -f stm32.cfg -f batch.cfg

openocd.exe -f blaster.cfg -f lpc2378.cfg -f batch.cfg

rem pause