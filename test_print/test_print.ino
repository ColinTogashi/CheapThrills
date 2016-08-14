/*
https://github.com/mchr3k/arduino-libs-manchester

Move to [arduino_dir]/libraries/Manchester
May need to rename example files so Arduino IDE doesn't throw errors

Program Arduino with Arduino IDE
Eventually port to ATTiny85 and program with USBTinyISP

RX_PIN -> D10
TX_PIN -> D11

*/

#include <SoftwareSerial.h>
#include <Manchester.h>
SoftwareSerial mySerial(10, 11); // RX, TX

#define RX_PIN 10
#define TX_PIN 11
#define BUFFER_SIZE 4
uint8_t buffer[BUFFER_SIZE];


void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //mySerial.begin(9600);
  man.setupReceive(RX_PIN, MAN_9600);
  man.beginReceiveArray(BUFFER_SIZE, buffer);
  Serial.println("Running");
}

void loop() // run over and over
{
  if (man.receiveComplete())
  {
    uint8_t receivedSize = 0;
    receivedSize = buffer[0];
    for (uint8_t i=1; i<receivedSize; i++)
    {
         Serial.write(buffer[i]);
         //mySerial.write(buffer[i]);
    }
    Serial.println();
    //mySerial.println();
    
    man.beginReceiveArray(BUFFER_SIZE, buffer);
    
  }
}

