#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>

unsigned char mssv[8] = {1,8,1,4,6,2,2,2};

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
	send_data(0x09,0xff);
	// intensity --> 80%
	send_data(0x0A,0x0C);
	// scan limit --> 8 chữ số
	send_data(0x0B,7);
	// shutdown --> không
	send_data(0x0C,1);
	// display test --> 0
	send_data(0x0F,0);
}

int main(void)
{
	// setup giao tiếp SPI
	wiringPiSPISetup(0,10000000);
	// thiết lập chế độ hoạt động
	Init();
	// hien thi mssv 18146222
	for (int i = 0; i < 8; i++)
	{
		send_data(i+1, mssv[7-i]);
	}
	
	return 0;
}
