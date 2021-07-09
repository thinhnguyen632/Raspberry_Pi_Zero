#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>

const unsigned char ma7doan[14]={0x7e,0x30,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x7b,0x63,0x4e,0x17,1};
unsigned char display[8]={0x7e,0x7e,0x7e,0x17,0x7e,0x7e,0x63,0x4e};

unsigned int s1_dau, s1_giatri, s2;
signed int s1;

void send_data(unsigned char adress, unsigned char value)
{
	unsigned char data[2];
	data[0] = adress;
	data[1] = value;
	wiringPiSPIDataRW(0,data,2);
}

void Init(void)
{
	// decode mode
	send_data(0x09,0);
	// intensity --> 80%
	send_data(0x0A,0x0C);
	// scan limit --> 8 chữ số
	send_data(0x0B,7);
	// shutdown --> không
	send_data(0x0C,1);
	// display test --> 0
	send_data(0x0F,0);
}

void random_s1(void)
{
	s1_dau = rand()%2;
	s1_giatri = rand()%41;
	s1 = rand()%81;
	s1 = s1 - 40;
}

void display_s1(void)
{
	if (s1_dau==0)
	{
		display[0]=ma7doan[13];
	}
	else 
	{
		display[0]=0;
	}
	display[1]=ma7doan[s1_giatri/10];
	display[2]=ma7doan[s1_giatri%10];
}

void random_s2(void)
{
	s2 = rand()%41 + 40;
}

void display_s2(void)
{
	display[4]=ma7doan[s2/10];
	display[5]=ma7doan[s2%10];
}

void tat_led_s1(void)
{
	send_data(8, 0);
	send_data(7, 0);
	send_data(6, 0);
	send_data(5, 0);
}

void tat_led_s2(void)
{
	send_data(4, 0);
	send_data(3, 0);
	send_data(2, 0);
	send_data(1, 0);
}

void display_led(void)
{	
	for (int i = 0; i < 8; i++)
	{
		send_data(i+1, display[7-i]);
	}
	if (s1_dau==1)
	{
		if (s1_giatri>30)
		{ 	
			for (int i = 0; i<5; i++)
			{
				tat_led_s1();
				delay(100);
				display_s1();
				for (int i = 0; i < 8; i++)
				{
					send_data(i+1, display[7-i]);
				}
				delay(100);
			}
		}
	}
	if (s2>70)
	{ 	
		for (int i = 0; i<5; i++)
		{
			tat_led_s2();
			delay(100);
			display_s2();
			for (int i = 0; i < 8; i++)
			{
				send_data(i+1, display[7-i]);
			}
			delay(100);
		}
	}
}

int main(void)
{
	// setup giao tiếp SPI
	wiringPiSPISetup(0,10000000);
	// thiết lập chế độ hoạt động SPI
	Init();

	display_led();
	while(1)
	{
		random_s1();
		random_s2();
		display_s1();
		display_s2();
		display_led();
		delay(1000);
	}
	return 0;
}
