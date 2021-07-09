#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>

void send_data(unsigned char adress, unsigned char value)
{
	unsigned char data[2];
	data[0] = adress;
	data[1] = value;
	wiringPiSPIDataRW(0,data,2);
}

void display(int num)
{
	// đếm số chữ số
	int n = num;
	int count = 1;//count -> số chữ số
	while(n/10)
	{
		count++;
		n = n/10;
	}
	// set lại scan limit 
	send_data(0x0B,count-1);
	// hiển thị
	for (int i=0; i<count; i++)
	{
		send_data(1, num%10);
		send_data(2, (num/10)%10);
		send_data(3, (num/100)%10);
		send_data(4, (num/1000)%10);
	}
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
	// led chạy 0->9999
	while(1)
	{
		for (int i=0; i<9999; i++)
		{
			display(i);
			delay(500);
		}
	}
	return 0;
}
