#include <stdio.h>
#include <stdlib.h>
#include "hx711.h"
#include <unistd.h>

int main(){
	(void) init();
	while(1){
		printf("%i g \n",measure());
		sleep(1);
	}
	return 0;
}
