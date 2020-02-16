#include <Ethernet.h>
#include <EthernetUdp.h> // Load UDP library
#include <SPI.h> // Load the spi lib

byte mac[] = {0x90, 0xA2, 0xDA, 0x10, 0x3A, 0x1C}; // Assign a mac address for shield- 
IPAddress ip(10,0,0,100); // Assign an ip address - loaded in router ahead of yime
unsigned int localPort = 5000; // Assign a port to talk over
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //hold info in array
String dataReq; // string for data
int packetSize; // i need to know package size

EthernetUDP Udp; // Define UDP Object
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // turn on serial port
  Ethernet.begin(mac, ip); // Initialize Ethernet
  Udp.begin(localPort); // Initialize Udp
  delay(1500);// delay

}

void loop() {
  // put your main code here, to run repeatedly:
  packetSize = Udp.parsePacket();

  if(packetSize>0){ // if you have data the read it 
    
      Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE); // Reading the data request on the Udp
      String dataReq(packetBuffer); // convet packet data array to string for convienience

      if (dataReq == "Red") {
          Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());// send back to remote ip and port from the sending computer
          Udp.print("You are asking for red"); // send string back to client
          Udp.endPacket();
        }

       if (dataReq == "Green") {
          Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());// send back to remote ip and port from the sending computer
          Udp.print("You are asking for green"); // send string back to client
          Udp.endPacket();
        }

        if (dataReq == "Blue") {
          Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());// send back to remote ip and port from the sending computer
          Udp.print("You are asking for Blue"); // send string back to client
          Udp.endPacket();
        }

        memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE);
    }
}
