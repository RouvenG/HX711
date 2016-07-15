// WiringPi-Api einbinden
#include <wiringPi.h>

// C-Standardbibliothek einbinden
#include <stdio.h>

//for Nanosleep
#include <time.h>


int main(){
    int debug = 1;    
    initPi();
    readInput();


    return 0;
}
       
int initPi(){
     //Starte WiringPi Api 
        if(wiringPiSetup() == -1)
        return 1;
        pinMode(2,INPUT);
        pinMode(0,OUTPUT);
}

int readInput(){
     digitalWrite(0,0);
        delay(1000);
        int count = 0;
        const struct timespec req = {0,3000};
        int i;
        if(digitalRead(2) == 0){
                for(i=0;i<27;i++){
                        if(debug)printf("Before impuls Data: %i \n",digitalRead(2));
                        digitalWrite(0,1);
                        nanosleep(&req, NULL);
                        digitalWrite(0,0);
                        if(digitalRead(2)) count = count + 1;
                        count = count << 1;
                        if(debug) printf("After Implus  Data: %i \n",digitalRead(2));
                        if(debug)printf("\n");
                        nanosleep(&req,NULL);
                }       
        }
        
}       
       
int convertBinarytoDec(){
    }

       


