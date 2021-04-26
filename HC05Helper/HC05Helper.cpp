#include "HC05Helper.h"

//A simple method to read inputs from the HC-05 when connected to the Android App
int HC05Helper::listenFromHC05()
{
    if(Serial.available() > 0) {
        int incoming_value = Serial.read();
        Serial.println(incoming_value);
        switch(incoming_value){
            case 100: // Up
                return 100;
                break;
            case 200: // Down
                return 200;
                break;
            case 300: // Turn Left
                return 300;
                break;
            case 400: // Turn Right
                return 400;
                break;
            case 500: // Forwards
                return 500; 
                break;
            case 600: // Backwards
                return 600;
                break;
            default:
                //do nothing
                break;
        }
    }
    return -1;
}