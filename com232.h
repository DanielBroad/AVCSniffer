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

 -----------------------------------------------------------------------
	this file is a part of the TOYOTA Corolla MP3 Player Project
 -----------------------------------------------------------------------
 		http://www.softservice.com.pl/corolla/avc
*/


#ifndef __COM232_H
#define __COM232_H
//------------------------------------------------------------------------------

#include "const.h"
#include "buffer.h"



//------------------------------------------------------------------------------
#define UART_CPU			F_CPU

#define UART_BAUD_RATE_IPOD		19200
#define UART_BAUD_SELECT_IPOD 47//((UART_CPU / (UART_BAUD_RATE_IPOD * 16L)) - 1)

#define UART_BAUD_RATE		115200
#define UART_BAUD_SELECT	((UART_CPU / (UART_BAUD_RATE * 16L)) - 1)
#define UART_FLAGS2 (_BV(RXCIE) | _BV(RXEN) | _BV(TXEN))
#define UART_FLAGS (_BV(TXEN))

//------------------------------------------------------------------------------

void RS232_Init(void);
extern void RS232_SendByte(u08 Data);
extern void RS232_Print(u08* pBuf);
extern void RS232_PrintHex4(u08 Data);
extern void RS232_PrintHex8(u08 Data);
extern void RS232_PrintDec(u08 Data);
extern void RS232_PrintDec2(u08 Data);
extern void RS232_ClearInBuffer();
void RS232_SendStuff();

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
#endif
