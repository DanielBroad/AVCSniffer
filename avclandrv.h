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
/*
  Copyright (C) 2006 Daniel Broad <daniel@dorada.co.uk>.

   -----------------------------------------------------------------------
	this file is a part of the Lexus iPod Project
 -----------------------------------------------------------------------
 		http://www.lexusipod.com
*/

#ifndef __AVCLANDRV_H
#define __AVCLANDRV_H
//------------------------------------------------------------------------------
#include "const.h"

u08 AVCLan_Read_Message();
void AVCLan_Send_Status();
void AVCLan_Init();
u08 AVCLan_Send_Changer_Status();

#define MAXMSGLEN	32//32

// MY AVCLAN ID
#define MY_ID_1	0x03
#define MY_ID_2	0x60

#define cmNull		0
#define cmStatus1	1
#define cmStatus2	2
#define cmStatus3	3
#define cmStatus4	4

#define cmPlayReq1	5
#define cmPlayReq2	6
#define cmPlayReq3	7
#define cmStopReq	8
#define cmStopReq2	9
#define cmPlayReq4	10

#define cmRegister		100
#define cmInit			101
#define cmCheck			102
#define cmPlayIt		103
#define cmInitv11		104
#define cmBeep			110
#define cmVolZero		111
#define cmDiscStatus	112
#define cmTrackDiscStatus		113
#define cmNoCart		114
#define cmCartStatus	115

typedef enum { stStop, stPlay, stFF, stRR } cd_modes;
cd_modes CD_Mode;

#define stNoDiscs 0x00
#define stAllDiscs 0x3f
#define stDisc6 0x32
#define stDisc5 0x16
#define stDisc4 0x08
#define stDisc3 0x04
#define stDisc2 0x02
#define stDisc1 0x01

u08 Changer_Mode;

u08 broadcast;
u08 master1;
u08 master2;
u08 slave1;
u08 slave2;
u08 message_len;
u08 message[MAXMSGLEN];

u08 data_control;
u08 data_len;
u08 data[MAXMSGLEN];

u08 AVCLan_SendData(u08 m1, u08 m2);
u08 AVCLan_SendAnswer();
u08 AVCLan_SendDataBroadcast();

u08 HexInc(u08 data);
u08 HexDec(u08 data);

u08 cd_Disc;
u08 cd_Track;
u08 cd_Time_Min;
u08 cd_Time_Sec;
u08 randomMode;
u08 repeatMode;

u08 masterDevice1;
u08 masterDevice2;

u08 maxDisc;
//------------------------------------------------------------------------------
u08 answerReq;
//------------------------------------------------------------------------------

#define eeprombase 0
#define EEPROM_MasterDevice1 (uint8_t*)eeprombase+0
#define EEPROM_MasterDevice2 (uint8_t*)eeprombase+1
#define EEPROM_AVCVersion (uint8_t*)eeprombase+2
#define EEPROM_UnknownCommand (uint8_t*)eeprombase+16
#endif
