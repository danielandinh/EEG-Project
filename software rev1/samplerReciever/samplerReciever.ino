/*
  Created:    November 13, 2023
  Modified:   December 13, 2023
  Version:    1.0
  GitHub: https://github.com/danielandinh/EEG-Project
  
  Description:
  Implementation of analog data sampler.
  Recieves data via HC05. Sends serial data to python script.
  
  Modification History:
  - Version 1.0 (November 13, 2023): Initial commit
  - 
*/

#include <SoftwareSerial.h>

#define BT_NAME   "BT_RECIEVER"

SoftwareSerial BTSerial(2, 3);

// set up buffer to store info transmitted line by line
const byte bufferSize = 64; 
char buffer[bufferSize];
byte bufferIndex = 0;

void setup() {
    Serial.begin(38400);  
    BTSerial.begin(38400);
//  Uncomment to set up AT Mode
//  BTSerial.print("AT\r\n"); delay(200); 
//  BTSerial.print("AT+RMAAD\r\n"); delay(200);
//  BTSerial.print("AT+ADDR?\r\n"); delay(200);
//  BTSerial.print("AT+NAME="+String(BT_NAME)+"\r\n"); delay(200);
//  BTSerial.print("AT+PSWD=\"1234\"\r\n"); delay(200);
//  BTSerial.print("AT+ROLE=0\r\n"); delay(200);
//  BTSerial.print("AT+UART=38400,0,0\r\n"); delay(500);
}

void loop() {
    // check if data is available on the HC05
    if (BTSerial.available() > 0) {
        char receivedChar = BTSerial.read(); // read a character from HC05
    
        // reading line at a time
        if (receivedChar == '\n') {
            buffer[bufferIndex] = '\0'; // null-terminate the buffer
            Serial.println(buffer);     // send to laptop via serial
        
            // reset buffer for the next line
            bufferIndex = 0;
        } else {
            // Add the character to the buffer
            if (bufferIndex < bufferSize - 1) {
                buffer[bufferIndex++] = receivedChar;
            }
        }
    }
}
