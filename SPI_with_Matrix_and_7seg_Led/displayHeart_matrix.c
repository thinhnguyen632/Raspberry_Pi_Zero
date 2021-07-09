#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char display[8]={0,0,0,0,0,0,0,0};
unsigned char display_matran_traitim[8]={0x18,0x24,0x42,0x81,0x81,0x99,0x66,0x00};
unsigned char display_matran_traitim_chay[24]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x18,0x24,0x42,0x81,0x81,0x99,0x66,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

unsigned char display_matran_traitim_mini[8]={0x00,0x00,0x66,0x5a,0x42,0x24,0x18,0x00};

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

void display_ledmatran_traitim(void)
{
	for (int i = 0; i < 8; i++)
	{
		send_data(i+1, display_matran_traitim[7-i]);
	}
}

void display_ledmatran_traitim_mini(void)
{
	for (int i = 0; i < 8; i++)
	{
		send_data(i+1, display_matran_traitim_mini[i]);
	}
}

void display_ledmatran_traitim_chay(void)
{
	for (int i=0; i<8; i++)
	{
		send_data(8, display_matran_traitim[i]);
		send_data(7, display_matran_traitim[i+1]);
		send_data(6, display_matran_traitim[i+2]);
		send_data(5, display_matran_traitim[i+3]);
		send_data(4, display_matran_traitim[i+4]);
		send_data(3, display_matran_traitim[i+5]);
		send_data(2, display_matran_traitim[i+6]);
		send_data(1, display_matran_traitim[i+7]);
		delay(100);
	}
}

void display_ledmatran_traitim_nhapnhay(void)
{
	for (int i=0; i<10; i++)
	{
		display_ledmatran_traitim();
		delay(100);
		display_ledmatran_traitim_mini();
		delay(100);
	}
}

void display_ledmatran_traitim_dsp(void)
{
	for (int j=0; j<9; j++)
	{
		for (int i=0; i<8; i++)
		{
			send_data(i+1, display_matran_traitim[7-i]>>j);
		}
		delay(100);
	}
}

void display_ledmatran_traitim_dst(void)
{
	for (int j=0; j<9; j++)
	{
		for (int i=0; i<8; i++)
		{
			send_data(i+1, display_matran_traitim[7-i]<<j);
		}
		delay(100);
	}
}

void display_ledmatran_test(void)
{
	
}

int main(void)
{
	// setup giao tiếp SPI
	wiringPiSPISetup(0,10000000);
	// thiết lập chế độ hoạt động
	Init();
	display_ledmatran_traitim();
	while(1)
	{
		display_ledmatran_traitim();
		display_ledmatran_traitim_chay();
		display_ledmatran_traitim_nhapnhay();
		display_ledmatran_traitim_dsp();
		display_ledmatran_traitim_dst();
	}
	return 0;
}
