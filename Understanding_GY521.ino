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

#include "Wire.h" //Allows you to communicate to I2C devices

const int MPU_ADDR=0x68; // I2C address of MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69

float accelerometer_x, accelerometer_y, accelerometer_z;
float gyro_x, gyro_y, gyro_z;
int16_t temperature;

float convert_acc(int16_t i){
  return (float)i / 13500.0f;
}

float convert_gyro_x(int16_t x){
  x = x + 3500;
  return (float)x / 200.0f;
}
float convert_gyro_y(int16_t y){
  y = y - 240;
  return (float)y / 200.0f;
}
float convert_gyro_z(int16_t z){
  z = z + 730;
  return (float)z / 200.0f;
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
  int16_t acc_X = Wire.read()<<8 | Wire.read();
  accelerometer_x = convert_acc(acc_X);
  int16_t acc_Y = Wire.read()<<8 | Wire.read();
  accelerometer_y = convert_acc(acc_Y);
  int16_t acc_Z = Wire.read()<<8 | Wire.read();
  accelerometer_z = convert_acc(acc_Z);
  
  temperature = Wire.read()<<8 | Wire.read();
  
  int16_t gy_X = Wire.read()<<8 | Wire.read();
  gyro_x = convert_gyro_x(gy_X);
  int16_t gy_Y = Wire.read()<<8 | Wire.read();
  gyro_y = convert_gyro_y(gy_Y);
  int16_t gy_Z = Wire.read()<<8 | Wire.read();
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

  delay(200);
}
