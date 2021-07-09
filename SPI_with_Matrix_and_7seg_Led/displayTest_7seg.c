#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>

int main(void)
{
	// setup giao tiep SPI
	wiringPiSPISetup(0,10000000);
	// test led
	unsigned char data[2];
	data[0] = 0x0f;
	data[1] = 1;
	wiringPiSPIDataRW(0,data,2);
	
	return 0;
}
