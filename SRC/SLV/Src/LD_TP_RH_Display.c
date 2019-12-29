#include "LD_TP_RH_Display.h"
#include "stdio.h"

extern SPI_HandleTypeDef hspi2;

uint8_t minus_Symble = 0x40;

uint8_t NUM[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uint8_t Brightness = 1;

void LD_Transmit_Byte(uint8_t* pData)
{

	HAL_SPI_Transmit(&hspi2,pData,1,10);
	return;
}

void LD_STB_clr_pin(void)
{
	HAL_GPIO_WritePin(STB_GPIO_Port,STB_Pin,0);
	return;
}

void LD_STB_set_pin(void)
{
	HAL_GPIO_WritePin(STB_GPIO_Port,STB_Pin,1);
	return;
}

void Show_TP(float* pTP)
{
	float TP = *pTP;
	if(TP < 0)
	{
		TP = -(TP);
	}
	else
	{
		
	}
	
	TP = TP*10;
	
	uint8_t num01 = ((uint16_t)TP)%10;
	uint8_t num1 = (((uint16_t)TP/10)%10);
	uint8_t num10 = (((uint16_t)TP/100)%10);
	
	LD_Set_Dsiplay_Mode();
	LD_Set_Data_Mode(1);
	
	LD_Set_GRID_SEG(1,0x00);
	LD_Set_GRID_SEG(2,NUM[num10]);
	LD_Set_GRID_SEG(3,NUM[num1]|(1<<7));
	LD_Set_GRID_SEG(4,NUM[num01]);//dp
	
	LD_Set_brightness(1,Brightness);
	
	return;
}

void Show_RH(float* pRH)
{
	float RH = *pRH;

	
	RH = RH*10;
	
	uint8_t num01 = ((uint16_t)RH)%10;
	uint8_t num1 = (((uint16_t)RH/10)%10);
	uint8_t num10 = (((uint16_t)RH/100)%10);
	printf("LDRH = %d%d %d",num10,num1,num01);
	LD_Set_Dsiplay_Mode();
	LD_Set_Data_Mode(1);
	
	LD_Set_GRID_SEG(1,0x00);
	LD_Set_GRID_SEG(2,NUM[num10]);
	LD_Set_GRID_SEG(3,NUM[num1]|(1<<7));
	LD_Set_GRID_SEG(4,NUM[num01]);//dp
	
	LD_Set_brightness(1,Brightness);
	return;
}