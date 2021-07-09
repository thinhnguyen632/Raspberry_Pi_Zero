#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define bt1 12
#define bt2 16
#define bt3 15

#define red 7
#define green 11
#define blue 13

unsigned int do_sang, mau;

void xuat_led()
{
	if (mau==0)
	{
		softPwmWrite(red,0);
		softPwmWrite(green,0);
		softPwmWrite(blue,0);
		delay(100);
	}
	if (mau==1)
	{
		softPwmWrite(red,do_sang*10);
		softPwmWrite(green,0);
		softPwmWrite(blue,0);
		delay(100);
	}
	if (mau==2)
	{
		softPwmWrite(green,do_sang*10);
		softPwmWrite(red,0);
		softPwmWrite(blue,0);
		delay(100);
	}
	if (mau==3)
	{
		softPwmWrite(blue,do_sang*10);
		softPwmWrite(green,0);
		softPwmWrite(red,0);
		delay(100);
	}
}

void ngat_bt1()
{
	//chon mau led
	if (mau<3)
	{
		mau=mau+1;
	}
	else 
	{
		mau=0;
	}
}

void ngat_bt2()
{
	if (do_sang<10)
	{
		do_sang++;
	}
	else 
	{
		do_sang=do_sang;
	}
}

void ngat_bt3()
{
	if (do_sang>0)
	{
		do_sang--;
	}
	else
	{
		do_sang=do_sang;
	}
}

int main()
{
	//setup
	wiringPiSetupPhys();
	
	//khoi tao IO
	pinMode(red,PWM_OUTPUT);
	pinMode(green,PWM_OUTPUT);
	pinMode(blue,PWM_OUTPUT);
	softPwmCreate(red,0,100);
	softPwmCreate(green,0,100);
	softPwmCreate(blue,0,100);
	
	//khoi tao ngat
	wiringPiISR (bt1, INT_EDGE_RISING, ngat_bt1);
	wiringPiISR (bt2, INT_EDGE_RISING, ngat_bt2);
	wiringPiISR (bt3, INT_EDGE_RISING, ngat_bt3);
	
	do_sang=0;
	mau=0;
	
	while(1)
	{
		xuat_led();
	}
	return 0;
}
