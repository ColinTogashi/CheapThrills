/*
https://github.com/mchr3k/arduino-libs-manchester

Move to [arduino_dir]/libraries/Manchester
May need to rename example files so Arduino IDE doesn't throw errors

Program Arduino with Arduino IDE

Run on ATTiny85 with the following connections:
RX_PIN_MAN_A -> PB3 -> 415MHz Receiver
RX_PIN_MAN_B -> PB4 -> 315MHz Receiver
RX_PIN_SS    -> PB0 -> Disconnected
TX_PIN_SS    -> PB1 -> RX Serial to USB Converter


*/

#include <SoftwareSerial.h>
#include <Manchester.h>
#define RX_PIN_MAN_A 3
#define RX_PIN_MAN_B 4
#define RX_PIN_SS 0
#define TX_PIN_SS 1
#define BUFFER_SIZE 4 // TODO: Increase buffer size to be size of actual MPU data

SoftwareSerial mySerial(RX_PIN_SS, RX_PIN_SS); // RX, TX
Manchester manA;
Manchester manB;
uint8_t bufferA[BUFFER_SIZE];
uint8_t bufferB[BUFFER_SIZE];
uint8_t receivedSizeA;
uint8_t receivedSizeB;


void setup()  
{
    // Open serial communications and wait for port to open:
    mySerial.begin(9600);
    manA.setupReceive(RX_PIN_MAN_A, MAN_9600);
    manB.setupReceive(RX_PIN_MAN_B, MAN_9600);
    manA.beginReceiveArray(BUFFER_SIZE, bufferA);
    manB.beginReceiveArray(BUFFER_SIZE, bufferB);
}

void loop() // run over and over
{
    if (manA.receiveComplete())
    {
        receivedSizeA = 0;
        receivedSizeA = bufferA[0];
        for (uint8_t i=1; i<receivedSizeA; i++)
        {
            // Serial.write(bufferA[i]);
            mySerial.write(bufferA[i]);
        }
        //Serial.println();
        mySerial.println();
    
        manA.beginReceiveArray(BUFFER_SIZE, bufferA);
    }
    if (manB.receiveComplete())
    {
        receivedSizeB = 0;
        receivedSizeB = bufferB[0];
        for (uint8_t i=1; i<receivedSizeB; i++)
        {
            // Serial.write(bufferB[i]);
            mySerial.write(bufferB[i]);
        }
        //Serial.println();
        mySerial.println();
    
        manB.beginReceiveArray(BUFFER_SIZE, bufferB);
    }
}

