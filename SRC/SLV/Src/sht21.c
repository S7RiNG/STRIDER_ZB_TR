#include "sht21.h"
#include "stdio.h"
uint16_t i2c_addr = 0x40;
uint8_t flag = 0;

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	flag = 1;
}
float TR_Get_tmp(void)
{
	uint8_t cmd_t = 0xE3;
	uint8_t cmd_r = 0xFE;
	uint8_t cmd_s = 0x01;
	uint8_t buf[3] = {0,0,0};
	uint16_t st = 0;
	float tp = 0;
	HAL_I2C_Master_Transmit(&hi2c1,0x80,&cmd_r,1,1000);
	HAL_Delay(100);
	HAL_I2C_Master_Transmit(&hi2c1,0x80,&cmd_s,1,1000);
	HAL_Delay(100);
	HAL_I2C_Master_Transmit(&hi2c1,0x80,&cmd_t,1,1000);
	HAL_Delay(5);
	HAL_I2C_Master_Receive(&hi2c1,0x80,buf,3,3000);
	st = (((uint16_t)buf[0])<<8)|(buf[1]& ~1);
	tp = ((((float)st)/65536)*175.72)-45.85;
	//printf("tmp = %f \n",tp);
	return tp;
}

float TR_Get_rh(void)
{
	uint8_t cmd_t = 0xE5;
	uint8_t cmd_r = 0xFE;
	uint8_t cmd_s = 0x01;
	uint8_t buf[3] = {0,0,0};
	uint16_t sr = 0;
	float rh = 0;
	HAL_I2C_Master_Transmit(&hi2c1,0x80,&cmd_r,1,1000);
	HAL_Delay(100);
	HAL_I2C_Master_Transmit(&hi2c1,0x80,&cmd_s,1,1000);
	HAL_Delay(100);
	HAL_I2C_Master_Transmit(&hi2c1,0x80,&cmd_t,1,1000);
	HAL_Delay(5);
	HAL_I2C_Master_Receive(&hi2c1,0x80,buf,3,3000);
	sr = (((uint16_t)buf[0])<<8)|(buf[1]& ~1);
	rh = ((((float)sr)/65536)*125)-6;
	//printf("rh = %.1f%% \n",rh);
	return rh;
}