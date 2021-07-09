#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdint.h> // dạng biến int16_t
#include <math.h>

#define Sample_rate 	0x19
#define DLPF 			0x1a	
#define Gyro_config		0x1b
#define Acc_config		0x1c
#define Bypass_cofig	0x37
#define INT_enable		0x38
#define	PWR_management	0x6b	

#define interrupt_mpu	12

int mpu;

void mpu6050_Init()
{	
	// set giá trị cho register 25-28,55,56,107
	// sample rate = 1KHz, DLPF disable
	wiringPiI2CWriteReg8(mpu, Sample_rate, 0);
	// sử dụng DLPF, fc = 184 Hz
	wiringPiI2CWriteReg8(mpu, DLPF, 1);
	// gyro FS = +- 500
	wiringPiI2CWriteReg8(mpu, Gyro_config, 0x08);
	// acc FS = +- 8
	wiringPiI2CWriteReg8(mpu, Acc_config, 0x10);
	// interrupt enable bit3 bit4 = 0, bit0 = 1
	wiringPiI2CWriteReg8(mpu, INT_enable, 1);
	// power managenment 1 bit3 - bit7 = 0, bit0-bit2 = 1
	wiringPiI2CWriteReg8(mpu, PWR_management, 1);
}

int16_t read_sensor(uint8_t address)
{
	int16_t high_byte, low_byte, data;
	high_byte = wiringPiI2CReadReg8(mpu,address);
	low_byte = wiringPiI2CReadReg8(mpu,address+1);
	data = (high_byte<<8) | low_byte;
	return data;
}

void ngat_mpu()
{
	int16_t raw_Ax = read_sensor(0x3b);
	int16_t raw_Ay = read_sensor(0x3d);
	int16_t raw_Az = read_sensor(0x3f);
		
	float Ax = (float)raw_Ax/4096; //*9.81;
	float Ay = (float)raw_Ay/4096; //*9.81;
	float Az = (float)raw_Az/4096; //*9.81;	
		
	// Tính alpha x, alpha y đơn vị là radian
	float alphaX = atan2(Ay,sqrt(pow(Ax,2) + pow(Az,2)));
	float alphaY = atan2(Ax,sqrt(pow(Ay,2) + pow(Az,2)));
	// Xuất ra terminal góc alpha x, alpha y đơn vị độ
	printf("Goc alpha X la: %f\n",(alphaX*180)/M_PI);
	printf("Goc alpha Y la: %f\n",(alphaY*180)/M_PI);
	printf("\n");
	delay(1000);
	read_sensor(0x3a); //reset interrupt
}

int main(void)
{
	//setup port
	wiringPiSetupPhys();
	
	//setup giao tiếp I2C
	mpu = wiringPiI2CSetup(0x68);
	
	//thiết lập chế độ đo cho MPU6050
	mpu6050_Init();
	
	// check thanh ghi 117. Who Am I
	//int data = wiringPiI2CReadReg8(mpu, 0X75);
	//printf("gia tri = %x\n", data);
	
	// khởi tạo ngắt
	wiringPiISR(interrupt_mpu, INT_EDGE_RISING, &ngat_mpu);
	
	while(1)
	{
		
	}
	return 0;
}
