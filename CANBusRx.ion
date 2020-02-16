#include <mcp_can_dfs.h>
#include <mcp_can.h>

#include <SPI.h>

const int spiCSPin = 10;
const int ledPin = 2;
boolean ledON = 1;

MCP_CAN CAN(spiCSPin);

void setup()
{
    Serial.begin(9600);
    pinMode(ledPin,OUTPUT);

    while (CAN_OK != CAN.begin(CAN_500KBPS, MCP_8MHz))
    {
        Serial.println("CAN BUS Init Failed");
        delay(100);
    }
    Serial.println("CAN BUS 2 Init OK!");
}


void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];
    //Serial.println("In Loop2");

    if(CAN_MSGAVAIL == CAN.checkReceive())
    {
        Serial.println("Received");
        CAN.readMsgBuf( &len, buf);

        unsigned long canId = CAN.getCanId();
        
        Serial.println("-----------------------------");
        Serial.print("Data from Device ID: 0x");
        Serial.println(canId, HEX);
        Serial.println('\n');
        Serial.print("Distance: ");
        Serial.print(buf[0]);
        Serial.println(" cm");
        
        
        if(buf[7] == 1){
          Serial.println("STOPPED!");
          delay(1);
          }
         else{Serial.println("GO!");
              delay(1);};
        
        

        for(int i = 0; i<len; i++)
       {
            //Serial.println(buf[i]);
            //Serial.print("\t");
            if(ledON && i==0)
            {

              digitalWrite(ledPin, buf[i]);
               ledON = 0;
               delay(250);
            }
            else if((!(ledON)) && i==4)
            {

                digitalWrite(ledPin, buf[i]);
                ledON = 1;
            }
        }
        Serial.println();
    }
}
