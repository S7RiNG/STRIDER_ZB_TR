#include "main_task.h"
#include "sht21.h"
#include "ZB_USR.h"
#include "LD_TP_RH_Display.h"

#include "stdio.h"
#include "string.h"
float rh;
float tmp;

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim1;

uint8_t node = 1;

uint8_t TX_buf[10];
uint8_t RX_buf[10];
uint8_t TX_flag = 0;
uint8_t LD_flag = 0;
uint8_t TIM_flag = 0;
uint8_t x ,y;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
		
		if(huart == &huart3)
		{
			if((x == 0xf0)&&(node != 1))
			{
				RX_buf[0] = x;
				HAL_UART_Receive(&huart3,RX_buf+1,9,100);
				
				if(RX_buf[1] == (node - 1))
				{
					TX_flag = 1;
				}
				//HAL_UART_Transmit(&huart1,RX_buf,10,10);
			}
			else
			{
				//HAL_UART_Transmit(&huart1,&x,1,10);
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
	if(GPIO_Pin == SW_Pin)
	{
		HAL_Delay(3);
		if((TIM_flag == 0)&&(HAL_GPIO_ReadPin(SW_GPIO_Port,SW_Pin) == GPIO_PIN_SET))
		{
			
			if(LD_flag == 0)
			{
				LD_flag = 1;
			}
			else
			{
				LD_flag = 0;
			}
			LD_task();
		}
	}
}


void TR_task(void)
{
	HAL_Delay(100);
	rh = TR_Get_rh();
	HAL_Delay(100);
	tmp = TR_Get_tmp();
	HAL_Delay(100);
}

void LD_task(void)
{
	if(LD_flag == 0)
	{
		Show_TP(&tmp);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,1);
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,0);
		
	}
	else
	{
		Show_RH(&rh);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,0);
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,1);
	}
}

void TX_task(void)
{
	TX_buf[0] = 0xf0;
	TX_buf[1] = node;
	memcpy(TX_buf+2,&tmp,4);
	memcpy(TX_buf+6,&rh,4);
	ZB_TX_BC(TX_buf,11,1);
	HAL_Delay(500);
}



