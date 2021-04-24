// Working with GY-521/MPU-6050 Module (Gyroscope + Accelerometer)
// Using libraries from: https://github.com/jrowberg/i2cdevlib

//Pins:
//VCC - Voltage Supply (3.3V or 5V sources)
//GND - Ground
//SCL SDA - Serial Clock Line and Serial Data Line. For I2C serial communication
//XDA XCL - Auxilary Data / Clock - For connecting module to external sensors
//AD0 - I2C Address if low/high
//INT - Handle interrupts

#include "Wire.h" //Allows you to communicate to I2C devices

const int MPU_ADDR=0x68; // I2C address of MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temperature;

char tmp_str[7];

char* convert_int16_to_str(int16_t i){
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slace (GY-521 board)
  Wire.write(0x6B); //PWR_MGMT_1 register
  Wire.write(0); //set to 0 to wake up MPU-6050
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7*2, true); // Request a totla of 7*2=14 registers

  //Reading values
  accelerometer_x = Wire.read()<<8 | Wire.read();
  accelerometer_y = Wire.read()<<8 | Wire.read();
  accelerometer_z = Wire.read()<<8 | Wire.read();
  temperature = Wire.read()<<8 | Wire.read();
  gyro_x = Wire.read()<<8 | Wire.read();
  gyro_y = Wire.read()<<8 | Wire.read();
  gyro_z = Wire.read()<<8 | Wire.read();

  Serial.print("aX = ");
  Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" , aY = ");
  Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" , aZ = ");
  Serial.print(convert_int16_to_str(accelerometer_z));
  Serial.print(" , gX = ");
  Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" , gY = ");
  Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" , gZ = ");
  Serial.print(convert_int16_to_str(gyro_z));

  Serial.println("");

  delay(1000);
}
