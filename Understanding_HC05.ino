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

int incoming_value = -1;

//A simple method to read inputs from the HC-05 when connected to the Android App
void listenFromHC05(){
  if(Serial.available() > 0) {
    incoming_value = Serial.read();
    Serial.println(incoming_value);
    switch(incoming_value){
      case 100: // Up
        break;
      case 200: // Down
        break;
      case 300: // Turn Left
        break;
      case 400: // Turn Right
        break;
      case 500: // Forwards
        break;
      case 600: // Backwards
        break;
      default:
        //do nothing
        break;
    }
    incoming_value = -1; // Reset incoming_value back to -1 after input is read
  }
}

void setup() {
  Serial.begin(9600); // All that's needed to initialise BT reading
}

void loop() {
  listenFromHC05();
  delay(500);
}
