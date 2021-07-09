#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define bt1 12
#define bt2 16
#define bt3 15

#define red 7
#define green 11
#define blue 13

unsigned int mau;
unsigned int tt=1;

void led_sang_ngau_nhien()
{
	mau = rand()%3;
	if (mau==0)
	{
		printf("RED!!!");
		digitalWrite(red, HIGH);
		digitalWrite(green, LOW);
		digitalWrite(blue, LOW);
	}
	if (mau==1)
	{
		printf("GREEN!!!");
		digitalWrite(green, HIGH);
		digitalWrite(red, LOW);
		digitalWrite(blue, LOW);
	}
	if (mau==2)
	{
		printf("BLUE!!!");
		digitalWrite(blue, HIGH);
		digitalWrite(green, LOW);
		digitalWrite(red, LOW);
	}
}

void tat_led()
{
	digitalWrite(red, LOW);
	digitalWrite(green, LOW);
	digitalWrite(blue, LOW);
}

void ngat_bt1()
{
	if (mau==0)
	{
		for (int i=0; i<10; i++)
		{
			digitalWrite(red, HIGH);
			digitalWrite(green, HIGH);
			digitalWrite(blue, HIGH);
			delay(50);
			digitalWrite(red, LOW);
			digitalWrite(green, LOW);
			digitalWrite(blue, LOW);
			delay(50);
		}
		tt = 0;
	}
	else mau = mau;
}

void ngat_bt2()
{
	if (mau==1)
	{
		for (int i=0; i<10; i++)
		{
			digitalWrite(red, HIGH);
			digitalWrite(green, HIGH);
			digitalWrite(blue, HIGH);
			delay(50);
			digitalWrite(red, LOW);
			digitalWrite(green, LOW);
			digitalWrite(blue, LOW);
			delay(50);
		}
		tt = 0;
	}
	else mau = mau;
}

void ngat_bt3()
{
	if (mau==2)
	{
		for (int i=0; i<10; i++)
		{
			digitalWrite(red, HIGH);
			digitalWrite(green, HIGH);
			digitalWrite(blue, HIGH);
			delay(50);
			digitalWrite(red, LOW);
			digitalWrite(green, LOW);
			digitalWrite(blue, LOW);
			delay(50);
		}
		tt = 0;
	}
	else mau = mau;
}

int main()
{
	//setup
	wiringPiSetupPhys();
	
	//khoi tao IO
	pinMode(red,OUTPUT);
	pinMode(green,OUTPUT);
	pinMode(blue,OUTPUT);
	
	//khoi tao ngat
	wiringPiISR (bt1, INT_EDGE_RISING, ngat_bt1);
	wiringPiISR (bt2, INT_EDGE_RISING, ngat_bt2);
	wiringPiISR (bt3, INT_EDGE_RISING, ngat_bt3);
	
	while(tt=1)
	{
		led_sang_ngau_nhien();
		delay(500);
		tat_led();
		delay(3000);
    }
	return 0;
}
