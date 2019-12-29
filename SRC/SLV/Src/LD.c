#include "LD.h"
#include "main.h"

__weak void LD_STB_set_pin(void)
{
}

__weak void LD_STB_clr_pin(void)
{
}

__weak void LD_Transmit_Byte(uint8_t* pData)
{
}

void LD_Set_Dsiplay_Mode(void)
{
	LD_STB_clr_pin();
	uint8_t Cmd[] = {(1<<2)};
	LD_Transmit_Byte(Cmd);
	LD_STB_set_pin();
	return;
}

void LD_Set_Data_Mode(uint8_t Mode)//0 addr auto add \1 addr static
{
	LD_STB_clr_pin();
	uint8_t Cmd[] = {(1<<6)};//normal mode,write mode
	if(Mode)
	{
		Cmd[0] |= (1<<2);
	}
	LD_Transmit_Byte(Cmd);
	LD_STB_set_pin();
	return;
}

void LD_Set_GRID_SEG(uint8_t Grid,uint8_t SEG)//Grid 1~6(1~4 connected) SEG display data
{
	LD_STB_clr_pin();
	uint8_t addrGrid = 0;
	addrGrid = (Grid - 1)*2;
	uint8_t Cmd[] = {(3<<6)|addrGrid,SEG};
	LD_Transmit_Byte(&Cmd[0]);
	LD_Transmit_Byte(&Cmd[1]);
	LD_STB_set_pin();
	return;
}

void LD_Set_brightness(uint8_t toggle, uint8_t bright_level)//toggle ON\OFF brightness level 0~7
{
	LD_STB_clr_pin();
	uint8_t Cmd[] = {2<<6};
	if(toggle == 1)// ON
	{
		Cmd[0] |= (1<<3);
		Cmd[0] |= (bright_level);
	}
	else //OFF
	{
	}
	LD_Transmit_Byte(Cmd);
	LD_STB_set_pin();
}

void LD_init()
{
	LD_STB_clr_pin();
	HAL_Delay(100);
	LD_STB_set_pin();
}