/**********************************************************************
 *	8bit TIMER2 ���g�p�������荞�݃n���h���[.
 **********************************************************************
 *	timer2_init()
 *	timer2_wait()
 */
#ifndef _timer2_h_
#define _timer2_h_

void  timer2_init(uchar t2config,uchar period);
uchar timer2_wait(void);
int   timer2_gettime(void);
void  timer2_interval(uchar spi_delay);


// Enable Interrupt priority
// Enable all unmasked low priority interrupts
// Enable all unmasked high priority interrupts
// Timer2 interrupt is low priority

#define InitTimer2InterruptLow()  {RCONbits.IPEN = 1; INTCONbits.GIEL = 1; INTCONbits.GIEH = 1; IPR1bits.TMR2IP = 0; }	//Timer2���荞�݂� low Priority�ɐݒ肷��.

#define StartTimer2Interrupt()  {PIE1bits.TMR2IE = 1;}	//Timer2 ���荞�݋���.

#define StopTimer2Interrupt()   {PIE1bits.TMR2IE = 0;}	//Timer2 ���荞�݋֎~.


#endif  //_timer2_h_
/**********************************************************************
 *	
 **********************************************************************
 */
