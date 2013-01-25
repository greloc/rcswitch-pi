/*
 Usage: ./receiver
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    /*
     input PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 1;
    
    if (wiringPiSetup () == -1) return 1;
    printf("receiving\n");
    RCSwitch mySwitch = RCSwitch();
    mySwitch.enableReceive(PIN);
    
    while (1) {
        if (mySwitch.available()) {
            int value = mySwitch.getReceivedValue();
    
            if (value == 0) {
                printf("Unknown encoding");
            } else {
                printf("Received ");
                printf("%i", mySwitch.getReceivedValue());
                printf(" / ");
                printf("%i", mySwitch.getReceivedBitlength());
                printf("bit ");
                printf("Protocol: ");
                printf("%i", mySwitch.getReceivedProtocol());
             }

             mySwitch.resetAvailable(); 
        }
    }
	return 0;
}
