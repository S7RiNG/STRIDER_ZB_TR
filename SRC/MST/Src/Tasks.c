#include "Tasks.h"
#include "main.h"
#include "string.h"
#include "USR_OLED.h"
#include "stdio.h"

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart1;
extern uint8_t x;
extern uint8_t y;

uint8_t THC_flag = 0;
uint8_t THC_flag_ACTIVE = 0;
uint8_t THR_flag = 0;
uint8_t THR_flag_ACTIVE = 0;

uint8_t THC = 0;
uint8_t THC_ACTIVE = 0;
uint8_t THR = 0;
uint8_t THR_ACTIVE = 0;

uint8_t THCH = 0;
uint8_t THCH_ACTIVE = 0;
uint8_t THRH = 0;
uint8_t THRH_ACTIVE = 0;

uint8_t slct_sub = 0;

uint8_t SW1_flag;
uint8_t SW2_flag;
uint8_t SW3_flag;
uint8_t SW4_flag;
uint8_t slct_num = 1;
uint8_t mode = 0;
uint8_t submode = 0;

uint8_t node = 1;

uint8_t RX_buf[10];
float tmp[3];
float rh[3] = {0};

int fputc(int ch, FILE* stream)//debug use, redefine fputc so that use printf() over uart
{
    HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,10);
    return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
		
		if(huart == &huart3)
		{
			if((x == 0xf0))
			{
				RX_buf[0] = x;
				HAL_UART_Receive(&huart3,RX_buf+1,9,100);
				memcpy(&tmp[RX_buf[1] - 1],RX_buf+2,4);
				memcpy(&rh[RX_buf[1] - 1],RX_buf+6,4);
			}
			else
			{
				HAL_UART_Transmit(&huart1,&x,1,10);
			}
			HAL_UART_Receive_IT(&huart3,&x,1);
		}
		if(huart == &huart1)
		{
			HAL_UART_Transmit(&huart3,&y,1,10);
			HAL_UART_Receive_IT(&huart1,&y,1);
		}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_Delay(3);
	SW1_flag = HAL_GPIO_ReadPin(SW1_GPIO_Port,SW1_Pin);
	SW2_flag = HAL_GPIO_ReadPin(SW2_GPIO_Port,SW2_Pin);
	SW3_flag = HAL_GPIO_ReadPin(SW3_GPIO_Port,SW3_Pin);
	SW4_flag = HAL_GPIO_ReadPin(SW4_GPIO_Port,SW4_Pin);

	mode_task();
	OLED_show_selecter(slct_num,mode);
	SW1_flag = 0;
	SW2_flag = 0;
	SW3_flag = 0;
	SW4_flag = 0;
}



void mode_task()//user logic
{
	if(mode == 0)
	{
		if(SW2_flag == 1)
		{
			if(slct_num > 1)
				slct_num--;
			else
				slct_num = 3;
		}
		
		if(SW3_flag == 1)
		{
			if(slct_num < 3)
				slct_num++;
			else
				slct_num = 1;
		}
		
		if(SW1_flag == 1)//ENTER
		{
			mode = slct_num;
			
			if(slct_num == 1)
			{
				THC = THC_ACTIVE;
				THCH = THCH_ACTIVE;
				THC_flag = THC_flag_ACTIVE;
				slct_sub = 0;
			}
				
			
			if(slct_num == 2)
			{
				THR = THR_ACTIVE;
				THRH = THRH_ACTIVE;
				THR_flag = THR_flag_ACTIVE;
				slct_sub = 0;
			}
		}
	}
	else if(mode == 1)//set RT
	{
		if((slct_sub == 0)&&(SW1_flag == 1))
		{
			THC_flag = !THC_flag;
		}
		else if((slct_sub != 0)&&(SW1_flag == 1))
		{
			mode = 3+slct_sub;//4 THCH SET 5 THC
			submode = 1;
		}
		
		if((SW2_flag == 1)&&(THC_flag))
		{
			if(slct_sub >= 1)
			{
				slct_sub--;
			}
			else
			{
				slct_sub = 0;
			}
		}
		
		if((SW3_flag == 1)&&(THC_flag))
		{
			if(slct_sub <= 1)
			{
				slct_sub++;
			}
			else
			{
				slct_sub = 2;
			}
		}
		
		if(SW4_flag == 1)
		{
			slct_sub = 0;
			OLED_show_subselecter(slct_num,slct_sub,submode);
			mode = 0;
			THC_ACTIVE = THC;
			THCH_ACTIVE = THCH;
			THC_flag_ACTIVE = THC_flag;
		}
	}
	else if(mode == 2)//set RH
	{
		if((slct_sub == 0)&&(SW1_flag == 1))
		{
			THR_flag = !THR_flag;
		}
		else if((slct_sub != 0)&&(SW1_flag == 1))
		{
			mode = 5+slct_sub;//4 THRH SET 5 THR
			submode = 1;
		}
		
		if((SW2_flag == 1)&&(THR_flag))
		{
			if(slct_sub >= 1)
			{
				slct_sub--;
			}
			else
			{
				slct_sub = 0;
			}
		}
		
		if((SW3_flag == 1)&&(THR_flag))
		{
			if(slct_sub <= 1)
			{
				slct_sub++;
			}
			else
			{
				slct_sub = 2;
			}
		}
		
		if(SW4_flag == 1)
		{
			slct_sub = 0;
			OLED_show_subselecter(slct_num,slct_sub,submode);
			mode = 0;
			THR_ACTIVE = THR;
			THRH_ACTIVE = THRH;
			THR_flag_ACTIVE = THR_flag;
			
		}
	}
	else if(mode == 3)//set NODE
	{
		if(SW1_flag == 1)
		{
			
		}
		
		if(SW2_flag == 1)
		{
			if(node > 1)
			node--;
			else
			node = 3;
		}
		
		if(SW3_flag == 1)
		{
			if(node < 3)
			node++;
			else
			node = 1;
		}
		
		if(SW4_flag == 1)
		{
			mode = 0;
		}
	}
	else if(mode == 4)// THCH
	{
		if(SW3_flag == 1)
		{
			
			if(THCH < 99)
			{
				THCH++;
			}
			else
			{
				THCH =  0;
			}
		}
		
		if(SW2_flag == 1)
		{
			if(THCH > 0)
			{
				THCH--;
			}
			else
			{
				THCH =  99;
			}
		}
		
		if(SW4_flag == 1)
		{
			submode = 0;
			mode = 1;
		}
	}
	else if(mode == 5)// THC
	{
		if(SW3_flag == 1)
		{
			
			if(THC < 99)
			{
				THC++;
			}
			else
			{
				THC =  0;
			}
		}
		
		if(SW2_flag == 1)
		{
			if(THC > 0)
			{
				THC--;
			}
			else
			{
				THC =  99;
			}
		}
		
		if(SW4_flag == 1)
		{
			submode = 0;
			mode = 1;
		}
	}
	else if(mode == 6)// THRH
	{
			if(SW3_flag == 1)
		{
			
			if(THRH < 99)
			{
				THRH++;
			}
			else
			{
				THRH = 0;
			}
		}
		
		if(SW2_flag == 1)
		{
			if(THCH > 0)
			{
				THRH--;
			}
			else
			{
				THRH = 99;
			}
		}
		
		if(SW4_flag == 1)
		{
			submode = 0;
			mode = 2;
		}
	}
	else if(mode == 7)// THR
	{
			if(SW3_flag == 1)
		{
			
			if(THR < 99)
			{
				THR++;
			}
			else
			{
				THR = 0;
			}
		}
		
		if(SW2_flag == 1)
		{
			if(THR > 0)
			{
				THR--;
			}
			else
			{
				THR = 99;
			}
		}
		
		if(SW4_flag == 1)
		{
			submode = 0;
			mode = 2;
		}
		
	}
	
}

void OLED_task()
{
	OLED_show_UI();
	OLED_show_data(tmp[node-1],rh[node-1],node);
	OLED_show_TH(THC,THR,THCH,THRH,THC_flag,THR_flag);
	OLED_show_selecter(slct_num,mode);
	if(slct_sub)
	OLED_show_subselecter(slct_num,slct_sub,submode);
	HAL_Delay(100);
}

void TH_task()//threshold detection
{
	uint8_t ov = 0;

	for(uint8_t i = 0; i < 3; i++)//fill ov
	{
		if(THC_flag_ACTIVE)
		{
			if((THCH_ACTIVE > (int8_t)tmp[i])||(THC_ACTIVE <= (int8_t)tmp[i]))
			{
				ov |= (1<<(2*i));
			}
		}
		if(THR_flag_ACTIVE)
		{
			if((THRH_ACTIVE > (int8_t)rh[i])||(THR_ACTIVE <= (int8_t)rh[i]))
			{
				ov |= ( 1 << ( ( 2 * i ) + 1 ) );
			}
		}
	}
	if(ov)
	{
		HAL_GPIO_WritePin(BUZZ_GPIO_Port,BUZZ_Pin,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(BUZZ_GPIO_Port,BUZZ_Pin,GPIO_PIN_RESET);
	}
	OLED_show_OV(ov);
}