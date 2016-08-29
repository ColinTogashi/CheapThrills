/*
Program ATTiny85 using USBTinyISP
TX_PIN -> PB3 (Pin 2)

*/

#include <Manchester.h>
#include <TinyWireM.h>

#define TX_PIN_MAN 3


uint8_t data[15];
const int MPU_addr=0x68;  // I2C address of the MPU-6050

Manchester manA;

#define NUM_MPU_REGS 14
struct
{
    int16_t x_accel;
    int16_t y_accel;
    int16_t z_accel;
    int16_t temperature;
    int16_t x_gyro;
    int16_t y_gyro;
    int16_t z_gyro;
} MPU_6050_data_struct;


void setup()
{
    manA.setupTransmit(TX_PIN_MAN, MAN_9600);
    TinyWireM.begin();
    TinyWireM.beginTransmission(MPU_addr);
    TinyWireM.send(0x6B);  // PWR_MGMT_1 register
    TinyWireM.send(0);     // set to zero (wakes up the MPU-6050)
    TinyWireM.endTransmission();
}

void loop()
{
    TinyWireM.beginTransmission(MPU_addr);
    TinyWireM.send(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    TinyWireM.endTransmission();
    TinyWireM.requestFrom(MPU_addr, 14);  // request a total of 14 registers
    data[0] = 15;
    for (int i=1; i<15; i++)
    {
      data[i] = TinyWireM.receive();
    }
    
    manA.transmitArray(15, data);
    delay(100);

}
