#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define red 13
#define bt1 7 
#define bt2 11
#define bt3 12
#define bt4 15

void ngat_bt1()
{
	softPwmWrite(red,25);
	delay(100);
}

void ngat_bt2()
{
	softPwmWrite(red,50);
	delay(100);
}

void ngat_bt3()
{
	softPwmWrite(red,75);
	delay(100);
}

void ngat_bt4()
{
	softPwmWrite(red,100);
	delay(100);
}

int main()
{
	wiringPiSetupPhys();
	
	pinMode (red, PWM_OUTPUT);
	pinMode (bt1, INPUT);
	pinMode (bt2, INPUT);
	pinMode (bt3, INPUT);
	pinMode (bt4, INPUT);
	
	digitalWrite (bt1, LOW);
	digitalWrite (bt2, LOW);
	digitalWrite (bt3, LOW);
	digitalWrite (bt4, LOW);
	softPwmWrite (red, 0);

	//khoi tao softPwm
	softPwmCreate(red,0,100);
	
	//khoi tao ngat
	wiringPiISR (bt1, INT_EDGE_RISING, ngat_bt1);
	wiringPiISR (bt2, INT_EDGE_RISING, ngat_bt2);
	wiringPiISR (bt3, INT_EDGE_RISING, ngat_bt3);
	wiringPiISR (bt4, INT_EDGE_RISING, ngat_bt4);
	
	while(1)
	{
		
	}
	return 0;
}
