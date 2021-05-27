  

//Seeed_Arduino_CAN-master library na githubu
#include <SPI.h>
#include "mcp2518fd_can.h"

const int SPI_CS_PIN_SEND = 9;
const int SPI_CS_PIN_RECEIVE = 10;

mcp2518fd CAN_SEND(SPI_CS_PIN_SEND);
mcp2518fd CAN_RECEIVE(SPI_CS_PIN_RECEIVE);

byte len = 0;
byte buf[8];




void setup() {
    SERIAL_PORT_MONITOR.begin(115200);
    while(!Serial); // cekanje serial porta

    if (CAN_SEND.begin(CAN_500K_1M) != 0 || CAN_RECEIVE.begin(CAN_500K_1M) != 0) {
      SERIAL_PORT_MONITOR.println("inicijalizacijski error");
      while(1);
    }
    
    SERIAL_PORT_MONITOR.println("inicijalizacija ok");
}

byte stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
void loop() {
  //sample poruka
  stmp[0]=0;
  stmp[1]=0;
  stmp[2]=0;
  stmp[3]=0;
  stmp[4]=0;
  stmp[5]=0;
  stmp[6]=0;
  stmp[7]=0;
  
  
    CAN_SEND.sendMsgBuf(0x00, 0, 8, stmp);
    delay(100);                       
    SERIAL_PORT_MONITOR.println("CAN poruka poslana!");
        
    if (CAN_MSGAVAIL == CAN_RECEIVE.checkReceive()) {
      SERIAL_PORT_MONITOR.println("provjera primanja");
      CAN_RECEIVE.readMsgBuf(&len, buf);
    for (int i = 0; i < len; i++) {
        SERIAL_PORT_MONITOR.print(buf[i]); SERIAL_PORT_MONITOR.print(" ");
    }
    SERIAL_PORT_MONITOR.println();
    }





    
    //ovaj dio doli je samo za promatranje poruka u serial monitoru
    unsigned long tempid;
    byte duljina;
    byte bufr[8];
    
      CAN_SEND.readMsgBufID(tempid, duljina, bufr);
      SERIAL_PORT_MONITOR.println("primljena CAN poruka je");
    SERIAL_PORT_MONITOR.print( tempid );
    for(int j=0;j<duljina;j++)
    {

      SERIAL_PORT_MONITOR.print(bufr[j]);
      SERIAL_PORT_MONITOR.print("/t");
      
      }
      SERIAL_PORT_MONITOR.print("/n");
   
    SERIAL_PORT_MONITOR.println("kraj loopa");
}
