// WiringPi-Api
#include <wiringPi.h>
#include <stdio.h>
#include <time.h> //for const struct timespec for nanosleep
#include "hx711.h"
/* Note that this driver is programmed according to
 * https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf
 *
 *  Author. pommoisel
; * */


int debug = 0; // simple debug flag
const struct timespec req = {0,100000000000}; //time of one period there is a weird bug here
int withoutWeight = 0; //24Bit number from HX711 when there is no weight on the scale

int measure(){
    return toGram(receive24BitNumber());
}

int init(){
    if(debug) printf("int init() \n");
    //Starte WiringPi Api
    if(wiringPiSetup() == -1);
    pinMode(2,INPUT);
    pinMode(0,OUTPUT);
    (void) tare();
}


/* This functiion is only help for the calibration of your scale, for more infos on this procedure please read the README */
void createFilesForCalibration(){
    if(debug) printf("void createFilesForCalibration()\n");
    char name[32];
    FILE *fp;
    while(1){
        printf("Name of the next file \n");
        scanf("%s",name);
        fp = fopen(name, "a+");
        int i = 0;
	int number24;
        for(i;i<10;i++){
            number24 = receive24BitNumber();
            fprintf(fp,"%i \n", number24);
	    printf("Value %i	\n", number24);
            delay(100);
        }
        fclose(fp);
    }
}

int tare(){
    if(debug) printf("int tare()\n");
    withoutWeight = receive24BitNumber();
    return withoutWeight;
}

int receive24BitNumber(){
    // Each conversation period is complete with first
    // receiving the number and than resetting the clock
    signed int count = 0; // count will be the 24-bit number received from hx711
    if(digitalRead(2) == 0){
        for(int i=0;i<24;i++){
            digitalWrite(0,1);
            nanosleep(&req, NULL);
            digitalWrite(0,0);
            if(i < 23) count = count << 1; //The last bit needs no shift
            if(digitalRead(2)) count = count + 1;
            nanosleep(&req,NULL);
        }
        resetClock(2); //please look at the gain setting at resetClock() definition
	delay(100);
        return sm2tc(count);
    }return -1;
}
//with the int gain you can choose the gain of the hx711
//1 => gain is 128
//2 => gain is 32
//3 => gain is 64
// any other number will lead to conversation problems
void resetClock(int gain){
    for (int j = 0; j < gain; ++j) {
        digitalWrite(0,1);
        nanosleep(&req, NULL);
        digitalWrite(0,0);
        nanosleep(&req, NULL);
    }

}


//Converts the 24 Bit number to decimal system on a 32 Bit processor
int sm2tc(int x) {
    int m = x >> 23;
    return (~m & x) | (((x & 0x400000) - x) & m);
}


/*For this function you should calibrate the scale on your own, for me it seems the
coefficient is no constant */
int toGram(int numFromScale){
	printf("%i \n", numFromScale);
   	float weight = (numFromScale - withoutWeight)*0.06; // the 0.06 comes from the calibration you have do do on your own
	return (int) weight;
}





