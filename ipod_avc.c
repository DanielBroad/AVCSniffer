/*
  Copyright (C) 2006 Marcin Slonicki <marcin@softservice.com.pl>.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


	This file is part of
	iPod interface for TOYOTA AVC-Lan CD-Changer Emulator
	v1.0
	(C) 2006 SLONIU
				http://www.softservice.com.pl/corolla/avc
				marcin@softservice.com.pl
 ---------------------------------------------------------------------------
*/

//------------------------------------------------------------------------------
#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "delay.h"
#include "const.h"
#include "avclandrv.h"
#include "com232.h"
#include "timer.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void PIN_Setup();

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
int main()
{
 PIN_Setup();
 
 //delay_ms(100);

 AVCLan_Init();

 #ifndef SNIFFER
 	iPod_Init();
 #endif

#ifdef MONITOR
	RS232_Print("********************** RESET *********************\n");
 #endif

 while (1) {

	if (INPUT_IS_SET) {	 // if message from some device on AVCLan begin
  		AVCLan_Read_Message();
		// check command from HU
		if (answerReq != 0) AVCLan_SendAnswer();
	}

	#ifndef SNIFFER
	// HandleEvent
	if (Event & EV_STATUS)
		{
		Event &= ~EV_STATUS;
	  	if (CD_Mode!=stStop) {
			AVCLan_Send_Status();
			};
		}

	if (Event & EV_DISPLAY)
		{
		Event &= ~EV_DISPLAY;
		AVCLan_Send_Changer_Status();
		}
	#endif

	RS232_SendStuff();
 } // end while(1)
}
//------------------------------------------------------------------------------
void PIN_Setup()
{
 outb(GIMSK, 0);			// disable external interupts
 outb(MCUCR, 0);
 outb(TIMSK, (_BV(TOIE1))); // Enable timer1 interrupt

 set_sleep_mode(SLEEP_MODE_IDLE); 

 //cbi(DDRD, 6); 
 //cbi(PORTD, 6); 

  // Timer 1
 outb(TCCR1A, 0);
 outb(TCCR1B, (_BV(CS12)) | (_BV(CS10)));	// Prescaler /1024
 outb(TCNT1H, TI1_H);						// Load counter value hi
 outb(TCNT1L, TI1_L);						// Load counter value lo

 RS232_Init();

 Event = EV_NOTHING;
 cli();
 AuxInput=1;
 #ifndef SNIFFER
 SwitchInputs();
 #endif

}

//------------------------------------------------------------------------------
SIGNAL(SIG_OVERFLOW1)					// Timer1 overflow every 1Sec
{
	outb(TCNT1H, TI1_H);					// reload timer1
	outb(TCNT1L, TI1_L);

	if ((CD_Mode!=stStop)) {
		Event |= EV_STATUS;
	}
}

SIGNAL(SIG_COMPARATOR)
{
	//do nothing we're now awake!
};
//------------------------------------------------------------------------------
