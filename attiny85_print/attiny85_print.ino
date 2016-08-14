/*
Program ATTiny85 using USBTinyISP
TX_PIN -> PB3 (Pin 2)

*/

#include <Manchester.h>

#define TX_PIN 3

uint8_t data[3] = {2, 'H', 'i'};

void setup()
{
    man.setupTransmit(TX_PIN, MAN_9600);
	data[0] = 2;
}

void loop()
{
    man.transmitArray(2, data);
	delay(100);
}
