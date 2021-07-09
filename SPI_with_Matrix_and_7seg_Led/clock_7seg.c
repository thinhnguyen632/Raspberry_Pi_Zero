#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>

const unsigned char madongho[11]={0x7e,0x30,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x7b,1};
unsigned char dongho_ht[8]={0x7e,0x7e,1,0x7e,0x7e,1,0x7e,0x7e};

unsigned int gio, phut, giay;
unsigned int gio_nhap, phut_nhap, giay_nhap;

void send_data(unsigned char adress, unsigned char value)
{
	unsigned char data[2];
	data[0] = adress;
	data[1] = value;
	wiringPiSPIDataRW(0,data,2);
}

void display_dongho(void)
{
	for (int i = 0; i < 8; i++)
	{
		send_data(i+1, dongho_ht[7-i]);
	}
}

void nhap_dongho(void)
{

BD:
	printf("Nhap gio tu 0-24 gio: ");
	scanf("%d",&gio_nhap);
	if (gio_nhap>24)
	{
		printf("Nhap lai\n");
		goto BD;
	}
	else
	{	
		printf("Nhap phut tu 0 - 60 phut: ");
		scanf("%d",&phut_nhap);
		if (phut_nhap>60)
		{
			printf("Nhap lai\n");
			goto BD;
		}
		else 
		{
			printf("Nhap giay tu 0 - 60 giay: ");
			scanf("%d",&giay_nhap);
			if (giay_nhap>60)
			{
				printf("Nhap lai\n");
				goto BD;
			}
		}
	}
}

void display_gio(void)
{
	dongho_ht[1]=madongho[gio%10];
	dongho_ht[0]=madongho[gio/10];
}

void display_phut(void)
{
	dongho_ht[4]=madongho[phut%10];
	dongho_ht[3]=madongho[phut/10];
}

void display_giay(void)
{
	dongho_ht[7]=madongho[giay%10];
	dongho_ht[6]=madongho[giay/10];
}

void reset_dongho(void)
{
	dongho_ht[7]=madongho[0];
	dongho_ht[6]=madongho[0];
	dongho_ht[5]=madongho[10];
	dongho_ht[4]=madongho[0];
	dongho_ht[3]=madongho[0];
	dongho_ht[2]=madongho[10];
	dongho_ht[1]=madongho[0];
	dongho_ht[0]=madongho[0];
	display_dongho();
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

int main(void)
{
	// setup giao tiếp SPI
	wiringPiSPISetup(0,10000000);
	// thiết lập chế độ hoạt động
	Init();
	reset_dongho();
	// nhập giờ phút giây
	nhap_dongho();
	while(1)
	{
		for (gio=gio_nhap; gio < 24; gio++)
		{
			for (phut=phut_nhap; phut < 60; phut++)
			{
				for (giay=giay_nhap; giay < 60; giay++)
				{
					display_gio();
					display_phut();
					display_giay();
					display_dongho();
					delay(1000);
				}
				giay_nhap=0;
			}
			phut_nhap=0;
		}
		gio_nhap=0;
		reset_dongho();
	}
	return 0;
}
