#ifndef GY521HELPER_H
#define GY521HELPER_H

#include <Arduino.h>
#include <Wire.h> //Allows you to communicate to I2C devices

// Working with GY-521/MPU-6050 Module (Gyroscope + Accelerometer)

//Pins:
//VCC - Voltage Supply (3.3V or 5V sources)
//GND - Ground
//SCL SDA - Serial Clock Line and Serial Data Line. For I2C serial communication
//XDA XCL - Auxilary Data / Clock - For connecting module to external sensors
//AD0 - I2C Address if low/high
//INT - Handle interrupts

//Data picked up:
// Temperature - Obvious and unneccessary for this project
// Gyroscope - Speed of rotation around an axis
// Assuming the board is flat and in front of you:
//  gyro X - Forwards/Backwards tilting. Lifting back up/front down = negative, other way is positive
//  gyro Y - Tilting side to side. clockwise = positive, anticlockwise = negative
//  gyro Z - Clockwise / Anticlockwise flat on the table, CW = negative, ACW = positive
// Accelerometer - measures g force exercised by Earth
//  accele X - When tilting the side of the board so it is tilted, value rises. This also decreases Z value
//  accele Y - When tilting the front of the board, value rises. This also decreases Z value
//  accele Z - g pull down. It is always a large value when left motionless - earth's gravity is 9.81m/s2

//Converting Standard Data (when board is flat):
// Sensor  : Value : Convert To
// gyroX   : -3500 : Very low (almost 0) - Note, gyro measures velocity therefore when stationary should be 0
// gyroY   : 240   : Very low (almost 0)
// gyroZ   : -730  : Very low (almost 0)
// acceleX : +-300 : 0.00
// acceleY : +-300 : 0.00
// acceleZ : ~13500 : 1.00 - Measures Gravity effect

//Using data picked up:
// For a drone, you want it to naturally be flat in the air. Using the accelerometers values you can measure if the drone
// is getting tilted. The natural resting drone position in the air needs to be when accelerometer X,Y values are 0, and Z
// is a large number (due to gravity).
// The Gyroscope data can be used to calculate when the drone is turning.

class GY521Helper {

private:

    float convert_acc(int16_t i);
    float convert_gyro_x(int16_t x);
    float convert_gyro_y(int16_t y);
    float convert_gyro_z(int16_t z);

    const int MPU_ADDR = 0x68; // I2C address of MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69

public:

    float accelerometer_x, accelerometer_y, accelerometer_z;
    float gyro_x, gyro_y, gyro_z;
    int16_t temperature;

    void setup();
    void read_data();
};

#endif