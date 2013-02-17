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

#include <avr/io.h>
#include <avr/signal.h>
#include "com232.h"
#include "delay.h"
//#include "buffer.h"

//static cBuffer uartTxBuffer;
//#define UART_TX_BUFFER_SIZE		0x0080
//static char uartTxData[UART_TX_BUFFER_SIZE];

//------------------------------------------------------------------------------
void RS232_Init(void)
{
//	RS232_RxCharBegin = RS232_RxCharEnd = 0;
	
// enable RxD/TxD and interrupts


	//bufferInit(&uartTxBuffer, uartTxData, UART_TX_BUFFER_SIZE);

	outb(UCSRB, UART_FLAGS);

	#ifdef MONITOR
		{
		outb(UBRRH, (u08)(UART_BAUD_SELECT>>8));		// set baud rate
		outb(UBRRL, (u08)UART_BAUD_SELECT);
		}
	#else
		{
		outb(UBRRH, (u08)(UART_BAUD_SELECT_IPOD>>8));		// set baud rate
		outb(UBRRL, (u08)UART_BAUD_SELECT_IPOD);
		}
	#endif

}

SIGNAL(SIG_UART_RECV)
{
	u08 USARTstatus = UCSRA;


    while ((USARTstatus & (1<<RXC))) 
		{
		USARTstatus = UCSRA;
	}

}
//------------------------------------------------------------------------------
void RS232_ActallySendByte(u08 Data)
{
	while ((inb(UCSRA) & _BV(UDRE)) != _BV(UDRE));		// wait for UART to become available
	outb(UDR, Data);									// send character
};

void RS232_SendByte(u08 Data)
{
	RS232_ActallySendByte(Data);
}
//------------------------------------------------------------------------------
void RS232_Print(u08* pBuf)
{
	register u08 c;
	while ((c = *pBuf++))
	{
		if (c == '\n')
			{
			RS232_SendByte('\r');
			};
		RS232_SendByte(c);	
		delay1(20);
	}
}

//------------------------------------------------------------------------------
void RS232_PrintHex4(u08 Data)
{
	u08 Character = Data & 0x0f;
	Character += '0';
	if (Character > '9')
		Character += 'A' - '0' - 10;
	RS232_SendByte(Character);
}
//------------------------------------------------------------------------------
void RS232_PrintHex8(u08 Data)
{
    RS232_PrintHex4(Data >> 4);
    RS232_PrintHex4(Data);
} 
//------------------------------------------------------------------------------
void RS232_PrintDec(u08 Data)
{
 if (Data>99) {
   RS232_SendByte('*');
   return;
 }
 if (Data<10) {
   RS232_SendByte('0'+Data);
   return;
 }
 u08 c;
 u16 v,v1;
 v  = Data;
 v1 = v/10;
 c  = '0' + (v-v1*10);
 RS232_SendByte('0'+v1);
 RS232_SendByte(c);
}
//------------------------------------------------------------------------------
void RS232_PrintDec2(u08 Data)
{
 if (Data<10) RS232_SendByte('0');
 RS232_PrintDec(Data);
}
//------------------------------------------------------------------------------
void RS232_SendStuff()
{
	if ((inb(UCSRA) & _BV(UDRE)) != _BV(UDRE)) return;
	//u08 Data;
	//Data = bufferGetFromFront(&uartTxBuffer);
	//if (Data)
		//RS232_ActallySendByte(Data);
}
