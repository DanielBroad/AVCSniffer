#include "sniffit.h"
#include "com232.h"
#include "avclandrv.h"
#include "const.h"
#include "avr\io.h"
//------------------------------------------------------------------------------
void ShowInMessage()
{
 if (message_len==0) return;

 //if ((broadcast==1) & ((slave1!=MY_ID_1) | (slave2!=MY_ID_2))) return;

 RS232_PrintHex4(master1);
 RS232_PrintHex8(master2);
 RS232_Print(" (");

 if (broadcast==0) RS232_Print("bro) ");
 else RS232_Print("dir) ");
 RS232_PrintHex4(slave1);
 RS232_PrintHex8(slave2);
 RS232_Print("| ") ;
 RS232_PrintHex8(message_len);
 u08 i;
 for (i=0;i<message_len;i++) {
  RS232_Print(" ");
  RS232_PrintHex8(message[i]);
 }
 RS232_Print("\n");
}
//------------------------------------------------------------------------------
void ShowOutMessage(int broadcast)
{
 u08 i;


 RS232_PrintHex4(MY_ID_1);
 RS232_PrintHex8(MY_ID_2);
 RS232_Print(" (");

 if (broadcast==0) {
 	RS232_Print("bro) ");
	RS232_PrintHex4(0x01);
    RS232_PrintHex8(0xFF); }
 else {
 	RS232_Print("dir) ");
	RS232_PrintHex4(masterDevice1);
    RS232_PrintHex8(masterDevice2);
	};

 RS232_Print("| ") ;
 RS232_PrintHex8(data_len);
 RS232_Print(" ");
 for (i=0; i<data_len; i++) {
	RS232_PrintHex8(data[i]);
	RS232_SendByte(' ');
 }
 RS232_Print("\n");
}

//------------------------------------------------------------------------------
