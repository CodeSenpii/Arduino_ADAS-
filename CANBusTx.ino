#include <mcp_can_dfs.h>
#include <mcp_can.h>


#include <SPI.h>

int ledHIGH = 1;
int ledLOW = 0;
const int spiCS_PIN =  10;

// Sonic wave
int trigPin = 7;
int echoPin = 6;

const int stopLight = 4;
const int onTime = 2000;

long duration;
int distance = 2600;


int ledHigh = 1;
int ledLow = 0;

MCP_CAN CAN(spiCS_PIN);


void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(stopLight, OUTPUT);
  Serial.begin(9600);

  while (CAN_OK != CAN.begin(CAN_500KBPS, MCP_8MHz))
  {
    Serial.println("CAN BUS init Fail");
    delay(100);
    }

    Serial.println("CAN BUS init OK!");
  

}

unsigned char stmp[8] = {9999, 0, 0, 0, 0, 0, 0, 0};

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("in loop");
  // send data: id = 0x00, standrad frame, data len = 8, stmp:data buffer
  //Serial.println(stmp[1]);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;

  stmp[0] = distance;
    
  CAN.sendMsgBuf(0x48, 0, 8, stmp);
  delay(1000);

  if(distance < 10){
    digitalWrite(stopLight, HIGH);
    stmp[7] = 1;
    //delay(onTime);
    }
   else{
    digitalWrite(stopLight, LOW);
    stmp[7] = 0;
    }
  Serial.println("Distance in cm: ");
  Serial.println(distance);
  
