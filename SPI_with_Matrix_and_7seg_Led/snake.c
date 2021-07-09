#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>

#define bt_phai 7 //bt1
#define bt_xuong 11 //bt3
#define bt_trai 12 //bt5
#define bt_len 13 //bt4

unsigned char display_1dot[64]={0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0};
unsigned char display[8]={0,0,0,0,0,0,0,0};
unsigned char snake[5]={51,43,35,27,19};
unsigned int dir=0;

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

void ngat_bt_phai()
{	
if (snake[4]+1==snake[3])
{
	dir=dir;
}
else
{
	dir = 1;
	while (dir==1)
	{
		if (snake[4]==7)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=0;
			delay(1000);
		}
		if (snake[4]==15)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=8;
			delay(1000);
		}
		if (snake[4]==23)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=16;
			delay(1000);
		}
		if (snake[4]==31)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=24;
			delay(1000);
		}
		if (snake[4]==39)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=32;
			delay(1000);
		}
		if (snake[4]==7)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=40;
			delay(1000);
		}
		if (snake[4]==55)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=48;
			delay(1000);
		}
		if (snake[4]==63)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=56;
			delay(1000);
		}	
		else
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=snake[4]+1;
			delay(1000);
		}
	}
}
}

void ngat_bt_xuong()
{
if (snake[4]+8==snake[3])
{
	dir=dir;
}
else
{
	dir = 2;
	while (dir==2)
	{
		if (snake[4]==56)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=0;
			delay(1000);
		}
		if (snake[4]==57)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=1;
			delay(1000);
		}
		if (snake[4]==58)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=2;
			delay(1000);
		}
		if (snake[4]==59)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=3;
			delay(1000);
		}
		if (snake[4]==60)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=4;
			delay(1000);
		}
		if (snake[4]==61)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=5;
			delay(1000);
		}
		if (snake[4]==62)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=6;
			delay(1000);
		}
		if (snake[4]==63)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=7;
			delay(1000);
		}	
		else
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=snake[4]+8;
			delay(1000);
		}
	}
}
}

void ngat_bt_trai()
{
if (snake[4]-1==snake[3])
{
	dir=dir;
}
else
{
	dir = 3;
	while (dir==3)
	{
		if (snake[4]==0)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=7;
			delay(1000);
		}
		if (snake[4]==8)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=15;
			delay(1000);
		}
		if (snake[4]==16)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=23;
			delay(1000);
		}
		if (snake[4]==24)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=31;
			delay(1000);
		}
		if (snake[4]==32)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=39;
			delay(1000);
		}
		if (snake[4]==40)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=47;
			delay(1000);
		}
		if (snake[4]==48)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=55;
			delay(1000);
		}
		if (snake[4]==56)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=63;
			delay(1000);
		}	
		else
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=snake[4]-1;
			delay(1000);
		}
	}
}
}

void ngat_bt_len()
{
if (snake[4]-8==snake[3])
{
	dir=dir;
}
else
{
	dir = 4;
	while (dir==4)
	{
		if (snake[4]==0)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=56;
			delay(1000);
		}
		if (snake[4]==1)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=57;
			delay(1000);
		}
		if (snake[4]==2)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=58;
			delay(1000);
		}
		if (snake[4]==3)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=59;
			delay(1000);
		}
		if (snake[4]==4)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=60;
			delay(1000);
		}
		if (snake[4]==5)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=61;
			delay(1000);
		}
		if (snake[4]==6)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=62;
			delay(1000);
		}
		if (snake[4]==7)
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=63;
			delay(1000);
		}	
		else
		{
			snake[0]=snake[1];
			snake[1]=snake[2];
			snake[2]=snake[3];
			snake[3]=snake[4];
			snake[4]=snake[4]-8;
			delay(1000);
		}
	}
}
}

void dich_display_1dot_to_display()
{
	display[0]=display_1dot[0]<<7|display_1dot[1]<<6|display_1dot[2]<<5|display_1dot[3]<<4|display_1dot[4]<<3|display_1dot[5]<<2|display_1dot[6]<<1|display_1dot[7]<<0; 
	display[1]=display_1dot[8]<<7|display_1dot[9]<<6|display_1dot[10]<<5|display_1dot[11]<<4|display_1dot[12]<<3|display_1dot[13]<<2|display_1dot[14]<<1|display_1dot[15]<<0;
	display[2]=display_1dot[16]<<7|display_1dot[17]<<6|display_1dot[18]<<5|display_1dot[19]<<4|display_1dot[20]<<3|display_1dot[21]<<2|display_1dot[22]<<1|display_1dot[23]<<0;
	display[3]=display_1dot[24]<<7|display_1dot[25]<<6|display_1dot[26]<<5|display_1dot[27]<<4|display_1dot[28]<<3|display_1dot[29]<<2|display_1dot[30]<<1|display_1dot[31]<<0;
	display[4]=display_1dot[32]<<7|display_1dot[33]<<6|display_1dot[34]<<5|display_1dot[35]<<4|display_1dot[36]<<3|display_1dot[37]<<2|display_1dot[38]<<1|display_1dot[39]<<0;
	display[5]=display_1dot[40]<<7|display_1dot[41]<<6|display_1dot[42]<<5|display_1dot[43]<<4|display_1dot[44]<<3|display_1dot[45]<<2|display_1dot[46]<<1|display_1dot[47]<<0;
	display[6]=display_1dot[48]<<7|display_1dot[49]<<6|display_1dot[50]<<5|display_1dot[51]<<4|display_1dot[52]<<3|display_1dot[53]<<2|display_1dot[54]<<1|display_1dot[55]<<0;
	display[7]=display_1dot[56]<<7|display_1dot[57]<<6|display_1dot[58]<<5|display_1dot[59]<<4|display_1dot[60]<<3|display_1dot[61]<<2|display_1dot[62]<<1|display_1dot[63]<<0;
}

void dich_snake_to_display_1dot()
{
	for (int i=0; i<64; i++)
	{	
		display_1dot[i]=0;
	}
	display_1dot[snake[0]]=1;
	display_1dot[snake[1]]=1;
	display_1dot[snake[2]]=1;
	display_1dot[snake[3]]=1;
	display_1dot[snake[4]]=1;
}

void display_led()
{
	for (int i = 0; i < 8; i++)
	{
		send_data(i+1, display[i]);
	}
}

void display_snake()
{
	dich_snake_to_display_1dot();
	dich_display_1dot_to_display();
	display_led();
	delay(50);
	display_1dot[snake[4]]=0;
	dich_display_1dot_to_display();
	display_led();
	delay(50);
}


int main(void)
{
	// setup pin
	wiringPiSetupPhys();
	// setup giao tiếp SPI
	wiringPiSPISetup(0,10000000);
	// khởi tạo ngắt
	wiringPiISR (bt_phai, INT_EDGE_RISING, ngat_bt_phai);
	wiringPiISR (bt_xuong, INT_EDGE_RISING, ngat_bt_xuong);
	wiringPiISR (bt_trai, INT_EDGE_RISING, ngat_bt_trai);
	wiringPiISR (bt_len, INT_EDGE_RISING, ngat_bt_len);
	// thiết lập chế độ hoạt động SPI
	Init();
	while(1)
	{
		display_snake();
	}
	return 0;
}
