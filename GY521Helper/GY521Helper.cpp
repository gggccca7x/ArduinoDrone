#include "GY521Helper.h"

float GY521Helper::convert_acc(int16_t i)
{
    return (float)i / 13500.0f;
}

float GY521Helper::convert_gyro_x(int16_t x)
{
    x = x + 3500;
    return (float)x / 200.0f;
}

float GY521Helper::convert_gyro_y(int16_t y)
{
    y = y - 240;
    return (float)y / 200.0f;
}

float GY521Helper::convert_gyro_z(int16_t z)
{
    z = z + 730;
    return (float)z / 200.0f;
}

void GY521Helper::setup()
{
    Wire.begin();
    Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slace (GY-521 board)
    Wire.write(0x6B);                 //PWR_MGMT_1 register
    Wire.write(0);                    //set to 0 to wake up MPU-6050
    Wire.endTransmission(true);
}

void GY521Helper::read_data()
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); // starting with register 0x3B
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 7 * 2, true); // Request a totla of 7*2=14 registers

    //Reading values
    int16_t acc_X = Wire.read() << 8 | Wire.read();
    accelerometer_x = convert_acc(acc_X);
    int16_t acc_Y = Wire.read() << 8 | Wire.read();
    accelerometer_y = convert_acc(acc_Y);
    int16_t acc_Z = Wire.read() << 8 | Wire.read();
    accelerometer_z = convert_acc(acc_Z);

    temperature = Wire.read() << 8 | Wire.read();

    int16_t gy_X = Wire.read() << 8 | Wire.read();
    gyro_x = convert_gyro_x(gy_X);
    int16_t gy_Y = Wire.read() << 8 | Wire.read();
    gyro_y = convert_gyro_y(gy_Y);
    int16_t gy_Z = Wire.read() << 8 | Wire.read();
    gyro_z = convert_gyro_z(gy_Z);

    Serial.print("aX=");
    Serial.print(accelerometer_x);
    Serial.print(" , aY=");
    Serial.print(accelerometer_y);
    Serial.print(" , aZ=");
    Serial.print(accelerometer_z);
    Serial.print(" , gX=");
    Serial.print(gyro_x);
    Serial.print(" , gY=");
    Serial.print(gyro_y);
    Serial.print(" , gZ=");
    Serial.print(gyro_z);

    Serial.println("");
}