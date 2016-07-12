// WiringPi-Api einbinden
#include <wiringPi.h>

// C-Standardbibliothek einbinden
#include <stdio.h>

//for Nanosleep
#include <time.h>


int main(){

	pinMode(4,INPUT);
	pinMode(5,OUTPUT);
	int i;
	const struct timespec req = {0,5000};
	//req.tv_sec = 0;
	//req.tv_nsec = 3000;

	for(i=0;i<24;i++){
		digitalWrite(5,0);
		nanosleep(&req,NULL);
		digitalWrite(5,1);
		nanosleep(&req, NULL);
		digitalWrite(5,0);
		nanosleep($req, NULL);
		int k = digitalRead(4);
		printf("%i",k);
	}
	printf("\n");

	return 0;
}

