/*
	Created:    November 12, 2023
	Modified:   December 13, 2023
	Version:    1.0
	GitHub: https://github.com/danielandinh/EEG-Project
	
	Description:
	Implementation of analog data sampler.
  Sends data to another nano via HC05 module.
	

	Modification History:
	- Version 1.0 (November 12, 2023): Initial commit
	- 
*/  

#include <SoftwareSerial.h>

#define BT_NAME   "BT_TRANSMITTER"
#define RECIEVER_ADDRESS "0022:09:010403"

const int electrode1 = A7;
const int samplingFrequency = 200;  // Desired sampling rate in samples per second
const int samplingPeriod = 1000 / samplingFrequency;  // Microseconds between samples
unsigned long StartTime;

SoftwareSerial BTSerial(2, 3);

void setup() {
    Serial.begin(38400);
    BTSerial.begin(38400);
    StartTime = millis(); // read start time
    
//  Uncomment to set up AT Mode
//  BTSerial.print("AT\r\n"); delay(200);
//  BTSerial.print("AT+RMAAD\r\n"); delay(200);
//  BTSerial.print("AT+ROLE=1\r\n"); delay(200);  
//  BTSerial.print("AT+NAME="+String(BT_NAME)+"\r\n"); delay(200);
//  BTSerial.print("AT+PSWD=\"1234\"\r\n"); delay(200);
//  BTSerial.print("AT+BIND="+String(RECIEVER_ADDRESS)+"\r\n"); delay(200);
//  BTSerial.print("AT+UART=38400,0,0\r\n"); delay(500);
//  BTSerial.print("AT+UART?\r\n"); delay(200);
}

void loop(){
    // reading and printing the value
    int sensorValue = analogRead(electrode1); // 10 bit, 0-1023
    Serial.print(sensorValue); 
    BTSerial.print(sensorValue);
  
    // printing time value
    unsigned long CurrentTime = millis(); // reads time in milliseconds
    unsigned long ElapsedTime = CurrentTime - StartTime;
    Serial.print(", ");
    Serial.println(ElapsedTime);
    BTSerial.print(", ");
    BTSerial.println(ElapsedTime);
  
    // implement sampling frequency
    delay(samplingPeriod);
}
