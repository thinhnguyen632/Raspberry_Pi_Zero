#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <softPwm.h>

#include <mariadb/mysql.h>

#define MAXTIMINGS	85
#define DHTPIN		7

#define IN1			16
#define IN2			18
#define ENA			22

int dht11_dat[5]={0, 0, 0, 0, 0};
float nhiet_do=0;
float do_am=0;
int mode=0;
int manual=0;

int tt_nhiet_do = 1; 
int tt_do_am = 1;
int tt_auto = 1;

void read_dht11_dat()
{
	uint8_t laststate=HIGH;
	uint8_t counter=0;
	uint8_t j=0,i;
	float f; 
 
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
	pinMode(DHTPIN,OUTPUT);
	digitalWrite(DHTPIN,LOW);
	delay(18);
	digitalWrite(DHTPIN,HIGH);
	delayMicroseconds(40);
	pinMode(DHTPIN,INPUT);
 
	for (i=0;i<MAXTIMINGS;i++)
	{
		counter=0;
		while (digitalRead(DHTPIN)==laststate)
		{
			counter++;
			delayMicroseconds(1);
			if(counter==255)
			{
				break;
			}
		}
		laststate=digitalRead(DHTPIN);
 
		if ( counter == 255 )
			break;
 
		if ((i>=4)&&(i%2==0))
		{
			dht11_dat[j/8]<<=1;
			if (counter>16)
				dht11_dat[j/8]|=1;
			j++;
		}
	}
 
	if ((j>=40)&&(dht11_dat[4]==((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3])&0xFF)))
	{
		//printf("\nDo am = %d.%d \nNhiet do = %d.%d \n",dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3]);
		do_am = (float)dht11_dat[0] + (float)dht11_dat[1]/10;
		nhiet_do = (float)dht11_dat[2] + (float)dht11_dat[3]/10;
	}
	else  
	{
		//printf("\nMeasuring...\n");
	}
}



void setupMotor()
{
	pinMode(IN1,OUTPUT);
	pinMode(IN2,OUTPUT);
	softPwmCreate(IN1,0,100);
	softPwmCreate(IN2,0,100);
	pinMode(ENA,OUTPUT);
	
	digitalWrite(IN1,HIGH);
	digitalWrite(IN2,HIGH);
	digitalWrite(ENA,LOW);
}

void DCStop()
{
	digitalWrite(ENA,LOW);
}

void DCLow()
{
	digitalWrite(ENA,HIGH);
	softPwmWrite(IN1, 33);
	delay(100);
}

void DCMedium()
{
	digitalWrite(ENA,HIGH);
	softPwmWrite(IN1, 66);
	delay(100);
}

void DCHigh()
{
	digitalWrite(ENA,HIGH);
	softPwmWrite(IN1, 99);
	delay(100);
}

void motorControl()
{
	if (mode==0)
	{
		switch (manual)
		{
			case 0: 
				DCStop();
				break;
			case 1:	
				DCLow();
				break;
			case 2:	
				DCMedium();
				break;
			case 3:	
				DCHigh();
				break;
		}
	}
	
	if (mode==1)
	{
		// che do AUTO dua vao nhiet do va do am
		
		if (nhiet_do>=0 && nhiet_do<25)	 	{tt_nhiet_do = 0;} //thap
		if (nhiet_do>=25 && nhiet_do<35)		{tt_nhiet_do = 1;} //tb
		if (nhiet_do>=35 && nhiet_do<100)	{tt_nhiet_do = 2;} //cao
		
		if (do_am>=0 && do_am<40)	 		{tt_do_am = 0;} //thap
		if (do_am>=40 && do_am<70)	 		{tt_do_am = 1;} //tb
		if (do_am>=70 && do_am<100)	 	{tt_do_am = 2;} //cao
		
		if (tt_do_am==0 && tt_nhiet_do ==0)	{DCLow();}
		if (tt_do_am==0 && tt_nhiet_do ==1)	{DCLow();}
		if (tt_do_am==1 && tt_nhiet_do ==0)	{DCLow();}
		if (tt_do_am==1 && tt_nhiet_do ==1)	{DCMedium();}
		if (tt_do_am==2 && tt_nhiet_do ==0)	{DCMedium();}
		if (tt_do_am==0 && tt_nhiet_do ==2)	{DCMedium();}
		if (tt_do_am==1 && tt_nhiet_do ==2)	{DCHigh();}
		if (tt_do_am==2 && tt_nhiet_do ==1)	{DCHigh();}
		if (tt_do_am==2 && tt_nhiet_do ==2)	{DCHigh();}
	}
}

int main(void)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "raspi";
    char *password = "123456"; /* set me first */
    char *database = "motorControl";
	
	wiringPiSetupPhys();
	setupMotor();
	DCStop();
	
	while(1)
	{
		//ket noi database
		conn = mysql_init(NULL);
		//mysql_real_connect(conn,server,user,password,database,0,NULL,0);
        if (mysql_real_connect(conn, server,user, password, database, 0, NULL, 0) == NULL)
		{
			fprintf(stderr, "%s\n", mysql_error(conn));
			mysql_close(conn);
			exit(1);
		}
		 
		char sql[200];
		
		// doc do am, nhiet do tu database
	    sprintf(sql, "select do_am, nhiet_do from sensor order by stt desc limit 1");
		mysql_query(conn,sql);
        res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		//while(row != NULL) // kiem tra row khac NULL de tranh loi segmentation fault
		//{
		do_am = atof(row[0]);
		nhiet_do = atof(row[1]);
		//}
		
		// doc do_am, nhiet_do tu sensor
		read_dht11_dat();
		
		// cap nhat do_am va nhiet_do len database
		sprintf(sql, "insert into sensor (do_am, nhiet_do) values (%f,%f)",do_am,nhiet_do);
		mysql_query(conn,sql);
		
		// doc table motor tu database
		sprintf(sql, "select * from motor");
		mysql_query(conn,sql);
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		//while(row != NULL)
		//{
		mode = atoi(row[0]);
		manual = atoi(row[1]);
		//}
			
		// dieu khien dong co
		motorControl();
		
		// ngat ket noi database
        mysql_close(conn);
		
		printf("\e[1;1H\e[2J"); //xoa terminal
		printf("\nDo am = %.1f \nNhiet do = %.1f\n",do_am, nhiet_do);
		if (mode==0)
		{
			printf("\nDong co chay che do Manual\n");
			printf("Manual = %d\n",manual);
		}
		if (mode==1)
		{
			printf("\nDong co chay che do Auto\n");
		}
		delay(1000);
	}
	return(0);
}
