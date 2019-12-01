#include <stdlib.h>
#include <stdio.h>
#include <time.h>
FILE* f;
void delay(int milliseconds);  
int main(int argc, char* argv[]) {
	//for Debian image (after June 2013)
	while(1){
		// LED3
		f = fopen("/sys/class/leds/beaglebone:green:usr3/brightness", "w");
		if (f == NULL) 
			exit(EXIT_FAILURE);
		fprintf(f, "1");
		fclose(f);   
		delay(1000);
		//for Angstrom image (after June 2013)
		f = fopen("/sys/class/leds/beaglebone:green:usr3/brightness", "w");
		if (f == NULL)
			exit(EXIT_FAILURE);
		fprintf(f, "0");
		fclose(f);
		delay(1000);
		
		// LED2
		f = fopen("/sys/class/leds/beaglebone:green:usr2/brightness", "w");
		if (f == NULL) 
			exit(EXIT_FAILURE);
		fprintf(f, "1");
		fclose(f);   
		delay(1000);
		//for Angstrom image (after June 2013)
		f = fopen("/sys/class/leds/beaglebone:green:usr2/brightness", "w");
		if (f == NULL)
			exit(EXIT_FAILURE);
		fprintf(f, "0");
		fclose(f);
		delay(1000);
		
		// LED1
		f = fopen("/sys/class/leds/beaglebone:green:usr1/brightness", "w");
		if (f == NULL) 
			exit(EXIT_FAILURE);
		fprintf(f, "1");
		fclose(f);   
		delay(1000);
		//for Angstrom image (after June 2013)
		f = fopen("/sys/class/leds/beaglebone:green:usr1/brightness", "w");
		if (f == NULL)
			exit(EXIT_FAILURE);
		fprintf(f, "0");
		fclose(f);
		delay(1000);
		
		// LED0
		f = fopen("/sys/class/leds/beaglebone:green:usr0/brightness", "w");
		if (f == NULL) 
			exit(EXIT_FAILURE);
		fprintf(f, "1");
		fclose(f);   
		delay(1000);
		//for Angstrom image (after June 2013)
		f = fopen("/sys/class/leds/beaglebone:green:usr0/brightness", "w");
		if (f == NULL)
			exit(EXIT_FAILURE);
		fprintf(f, "0");
		fclose(f);
		delay(1000);
	}
    return EXIT_SUCCESS;
}
void delay(int milliseconds) {
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}