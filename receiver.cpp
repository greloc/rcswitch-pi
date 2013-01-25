/*
 Usage: ./receiver
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength){
  static char bin[64]; 
  unsigned int i=0;

  while (Dec > 0) {
    bin[32+i++] = (Dec & 1 > 0) ? '1' : '0';
    Dec = Dec >> 1;
  }

  for (unsigned int j = 0; j< bitLength; j++) {
    if (j >= bitLength - i) {
      bin[j] = bin[ 31 + i - (j - (bitLength - i)) ];
    }else {
      bin[j] = '0';
    }
  }
  bin[bitLength] = '\0';
  
  return bin;
}

static char* bin2tristate(char* bin) {
  char returnValue[50];
  int pos = 0;
  int pos2 = 0;
  while (bin[pos]!='\0' && bin[pos+1]!='\0') {
    if (bin[pos]=='0' && bin[pos+1]=='0') {
      returnValue[pos2] = '0';
    } else if (bin[pos]=='1' && bin[pos+1]=='1') {
      returnValue[pos2] = '1';
    } else if (bin[pos]=='0' && bin[pos+1]=='1') {
      returnValue[pos2] = 'F';
    } else {
      return "not applicable";
    }
    pos = pos+2;
    pos2++;
  }
  returnValue[pos2] = '\0';
  printf("[tri: %s]\n", returnValue);
  printf("[addressCode: ");
  for (int i=0; i<8; i++) {
    printf("%c", returnValue[i]);
  }
  printf("]\n");
  return returnValue;
}

int main(int argc, char *argv[]) {
    
    /*
     input PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 2;
 
    if (wiringPiSetup () == -1) return 1;
    printf("receiving\n");
    RCSwitch mySwitch = RCSwitch();
    mySwitch.enableReceive(PIN);

    while (1) {
        if (mySwitch.available()) {
            int value = mySwitch.getReceivedValue();
	    printf("==========Received==========\n");
            if (value == 0) {
                printf("Unknown encoding");
            } else {
		int length = mySwitch.getReceivedBitlength();
		unsigned int decimal = mySwitch.getReceivedValue();
		char* b = dec2binWzerofill(decimal, length);
                printf("[decimal: %i]\n", decimal);
		printf("[binary: %s]\n", b);
		char* c = bin2tristate(b);
                printf("%i", length);
                printf(" bit\n");
                printf("Protocol: ");
                printf("%i\n", mySwitch.getReceivedProtocol());
		printf("==========END==========\n");
             }

             mySwitch.resetAvailable(); 
        }
    }
    return 0;
}
