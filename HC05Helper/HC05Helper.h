#ifndef HC05HELPER_H
#define HC05HELPER_H

#include <Arduino.h>
// Working with HC-05 Bluetooth Module

// Pins:
// VCC - Voltage, connect to 5V
// GND - Ground, connect to GND
// RDX - Bluetooth receiving pin. Not plugged directly into Arduino, connects to 1k resistor. 
//       Wire after resistor connects to 'TX' on Arduino.
// TXD - Bluetooth sending Pin, connects to 'RX' on Arduino

//Uses:
//I will use this bluetooth module to communicate with some sort of controller.
//(Note: Radio Module is always used for a controller, but as I happen to have 
// a BT receiver, I will use it instead)

//Input codes:
//For now I can just send a number on which direction I want it to go in (NOTE: This
// approach will not work with a proper controller, just for a phone app for testing)
//Direction   |   Number
//Up          |    100
//Down        |    200
//Turn Left   |    300
//Turn Right  |    400
//Forwards    |    500
//Backwards   |    600

class HC05Helper {

private:
public:
    int listenFromHC05();
};

#endif