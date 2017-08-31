#include<msp430f5529.h>
#include "lcd.h"

int sec=0;
int min=0;

void main ( void )
{
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
  lcdInit();
  lcdClear();
  lcdSetText("SEC",2,0);
  lcdSetText("MIN",6,0);
  P1DIR |= 0x01; // Set P1.0 to output direction
  TA0CCR0 = 32768-1;
  TA0CTL = TASSEL_1+MC_1; // ACLK, upmode
  TA0CCTL0 |= CCIE; // enable CCRO interrupt
  _EINT();

while(1)
  {
  lcdClear();
  lcdSetText("SEC",6,0);
  lcdSetText("MIN",2,0);
  lcdSetInt(sec,6,1);
  lcdSetInt(min,3,1);
  LPM3;
  }
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)

{
	TA0CCTL0 &= ~CCIFG;
	if(sec<20)
	   sec+=1;
	  else if(min<10)
	    {
		    sec=0;
		    min+=1;
	    }
	else
	  {
		   sec=0;
		   min=0;
	  }
	LPM3_EXIT;
}




