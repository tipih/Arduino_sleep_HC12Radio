// **** INCLUDES *****
#include "LowPower.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9); // Arduino RX, TX  HC12(TX,RX)
void setup()
{
  mySerial.begin(9600);
  Serial.begin(57600);
  delay(100);
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
    mySerial.println("AT+SLEEP");
    for (int a=0;a<1000;a++){
    
    if (mySerial.available()) {
    Serial.write(mySerial.read());
     }
    delay(1);
    }
    
    digitalWrite(6,HIGH);
    

    delay(200);
    pinMode(6,INPUT);
}

void loop() 
{

    // Enter power down state for 8 s with ADC and BOD module disabled
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
    digitalWrite(13,HIGH);
    pinMode(6,OUTPUT);
    digitalWrite(6,LOW);
    delay(100);
    mySerial.println("AT");
    for (int a=0;a<1000;a++){
    
    if (mySerial.available()) {
    Serial.write(mySerial.read());
     }
    delay(1);
    }

    mySerial.println("AT+V");
    for (int a=0;a<1000;a++){
    
    if (mySerial.available()) {
    Serial.write(mySerial.read());
     }
    delay(1);
    }
    delay(100);
      mySerial.println("AT+SLEEP");
    for (int a=0;a<1000;a++){
    
    if (mySerial.available()) {
    Serial.write(mySerial.read());
     }
    delay(1);
    }
    
    digitalWrite(6,HIGH);
    

    delay(200);
    pinMode(6,INPUT);
    
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
    digitalWrite(13,LOW);
    // Do something here
    // Example: Read sensor, data logging, data transmission.
}
