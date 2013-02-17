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
	TOYOTA AVC-Lan CD-Changer Emulator
*/

#ifndef __CONTS_H
#define __CONST_H

#define SNIFFER
#define MONITOR
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#define u08	unsigned char
#define u16 unsigned short
#define u32 unsigned int
//------------------------------------------------------------------------------

#define DATAOUT_DDR		DDRD
#define DATAOUT_PORT	PORTD
#define	DATAOUT_PIN		PIND
#define DATAOUT			5

#define INPUT_IS_SET (inb(ACSR)&_BV(ACO)) 
#define INPUT_IS_CLEAR (!(inb(ACSR)&_BV(ACO)))

// status event every 1 sec 
#define TI1_H	(((u16)-(F_CPU / 1024)) >> 8)
#define TI1_L	(((u16)-(F_CPU / 1024)) & 0xff )

#define STOPEvent  cli(); //cbi(TIMSK, TOIE1); cbi(UCSRB, RXCIE);
#define STARTEvent sei(); //sbi(TIMSK, TOIE1); sbi(UCSRB, RXCIE);

u08 AuxInput;
volatile u08 Event;

#define EV_NOTHING	0
#define EV_DISPLAY	1
#define EV_STATUS	4

#define versionMajor 1
#define versionMinor 0

void SwitchInputs();


//------------------------------------------------------------------------------
#endif
