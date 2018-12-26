// **** INCLUDES *****
#include "LowPower.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9); // Arduino RX, TX  HC12(TX,RX)


bool HC12_EnterSleep() {
	unsigned char RFin_bytes[20];
  int noData=0;
  pinMode(6,OUTPUT);
  digitalWrite(6,LOW);
  delay(200);
  while (mySerial.read() >= 0);
 
  Serial.println("Sending AT+SLEEP");
  mySerial.println("AT+SLEEP");
 
//Wait for min 2 bytes, max 20 retry
while(mySerial.available()<2) {
  delay(5);
  Serial.println("No data");
  noData++;
  if (noData>20) {
    Serial.println("Enter Sleep failed");
    return false;
  }
}
Serial.println(noData);
for (int a=0;a<8;a++){
    RFin_bytes[a]=mySerial.read();
    Serial.write(RFin_bytes[a]);
}
Serial.println("");
if ((RFin_bytes[0]!='O') &&(RFin_bytes[1]!='K'))
  return false;

    
  while (mySerial.read() >= 0);
  while (Serial.read() >= 0);
digitalWrite(6, HIGH);
Serial.println("Sleep OK");
delay(200);
pinMode(6, INPUT); //Not sure this help at all

	return true;
}

bool HC12_ExitSleep() {
   unsigned char RFin_bytes[20];
   int noData=0; 
    pinMode(6,OUTPUT);
    digitalWrite(6,LOW);
    delay(50);
    Serial.println("Exit sleep enter");
    
   while (mySerial.read() >= 0);

   mySerial.println("AT");
    
   
  //Wait for min 2 bytes, max 20 retry
  while(mySerial.available()<2) {
    delay(5);
    Serial.println("No data");
    noData++;
  if (noData>20) return false;
}
     
for (int a=0;a<2;a++){
    RFin_bytes[a]=mySerial.read();
}
  
  if ((RFin_bytes[0]!='O') &&(RFin_bytes[1]!='K')){
  Serial.println("Exit sleep failed");
  return false;
  }

  digitalWrite(6,HIGH);
  delay(200);
Serial.println("Exit sleep ok");
return true;
}



void setup()
{
  mySerial.begin(9600);
  Serial.begin(57600);
  delay(200);
  Serial.println("Starting");
    // No setup is required for this library
    pinMode(6,OUTPUT);
    pinMode(13,OUTPUT);
    digitalWrite(6,LOW);
    delay(200);
    mySerial.println("AT+V");
    delay(50);
    for (int a=0;a<1000;a++){
    
    if (mySerial.available()) {
    Serial.write(mySerial.read());
     }
    delay(1);
    }
    
	if (HC12_EnterSleep() == false) {
		Serial.println("HC12 Sleep failed");
	}
}

void loop() 
{

    // Enter power down state for 8 s with ADC and BOD module disabled
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
    digitalWrite(13,HIGH);
    HC12_ExitSleep();

    mySerial.println("Test sending this string");
    
   delay(100);

    HC12_EnterSleep();
    delay(100);
    digitalWrite(13,LOW);
    
    
    // Do something here
    // Example: Read sensor, data logging, data transmission.
}
