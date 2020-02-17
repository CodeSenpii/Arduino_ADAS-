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

        unsigned long canId = CAN.getCanId();#include <mcp_can_dfs.h>
#include <mcp_can.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


#include <SPI.h>



// LED indicator device 
const int spiCSPin = 10;
const int ledPin = 2;
boolean ledON = 1;

// CAN BUS object
MCP_CAN CAN(spiCSPin);

//Ethernet setup
byte mac[] = {0x90, 0xA2, 0xDA, 0x10, 0x3A, 0x1C}; // Assign a mac address for shield- 
IPAddress ip(10,0,0,100); // Assign an ip address - loaded in router ahead of yime
unsigned int localPort = 5000; // Assign a port to talk over
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //hold info in array
String dataReq; // string for data
int packetSize; // i need to know package size

EthernetUDP Udp; // Define UDP Object

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

    Ethernet.begin(mac, ip); // Initialize Ethernet
    Udp.begin(localPort); // Initialize Udp
    delay(1500);// delay
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
        }// end for
        Serial.println();
    }// end if CAN

   // Ethernet connection 
   packetSize = Udp.parsePacket();

   if(packetSize>0){ // if you have data the read it 
    
      Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE); // Reading the data request on the Udp
      String dataReq(packetBuffer); // convet packet data array to string for convienience

      if (dataReq == "Red") {
          Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());// send back to remote ip and port from the sending computer
          Udp.print(buf[0]); // send string back to client
          Udp.endPacket();
        }

       if (dataReq == "Green") {
          Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());// send back to remote ip and port from the sending computer
          Udp.print(buf[0]); // send string back to client
          Udp.endPacket();
        }

        if (dataReq == "Blue") {
          Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());// send back to remote ip and port from the sending computer
          Udp.print(buf[0]); // send string back to client
          Udp.endPacket();
        }

        memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE); // reset array to 0
    }
}
        
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
