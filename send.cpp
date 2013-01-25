/*
 Usage: ./send <AddressCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 0;
    char* addressCode = argv[1];
    int command  = atoi(argv[2]);
    
    if (wiringPiSetup () == -1) return 1;
    printf("sending addressCode[%s] command[%i]\n", addressCode, command);
    RCSwitch mySwitch = RCSwitch();
    mySwitch.enableTransmit(PIN);
    
    switch(command) {
        case 1:
            mySwitch.switchOn(addressCode);
            break;
        case 0:
            mySwitch.switchOff(addressCode);
            break;
        default:
            printf("command[%i] is unsupported\n", command);
            return -1;
    }
    return 0;
}
