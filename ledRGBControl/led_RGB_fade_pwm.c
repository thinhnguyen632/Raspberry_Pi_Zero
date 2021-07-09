#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

unsigned char led[3] = {13, 15, 16};

void sangdan(unsigned char pin)
{
	for(int i=0;i<21;i++)
	{
		softPwmWrite(pin,i*5);
		delay(100);
	}
}

void toidan(unsigned char pin)
{
	for(int i=0;i<21;i++)
	{
		softPwmWrite(pin, 100 - i*5);
		delay(100);
	}
}


int main()
{
	wiringPiSetupPhys();
	//khoi tao softpwm
	for(int i=0;i<3;i++)
	{
		softPwmCreate(led[i],0,100);
	}

	while(1)
	{
		for (int i=0;i<3;i++)
		{
			sangdan(led[i]);
			toidan(led[i]);
		}
	}
	return 0;
}
