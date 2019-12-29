#include "ZB_USR.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

uint8_t ZB_TX_buf[258];
uint8_t ZB_RX_buf[258];

void ZB_init_USR(void)
{
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+DEV=E",8,1000);
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+GROUP=2",10,1000);
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+CH=11",8,1000);
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+TXPOWER=4",12,1000);
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+SLEEP=0",10,1000);
	HAL_Delay(100);
	HAL_GPIO_WritePin(AT_HEX_GPIO_Port,AT_HEX_Pin,GPIO_PIN_RESET);
}

void ZB_reset(void)
{
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+PANID=1234",13,1000);
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+PANID=?",10,1000);
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+KEY=00000000000000000000000000000000",39,1000);
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+KEY=?",8,1000);
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+RESET",8,1000);
	HAL_Delay(100);
}

HAL_StatusTypeDef ZB_TX_BC(uint8_t* data, uint8_t size, uint8_t type)
{
	if(size < 254)
	{
		HAL_GPIO_WritePin(AT_HEX_GPIO_Port,AT_HEX_Pin,GPIO_PIN_RESET);
		HAL_Delay(10);
		ZB_TX_buf[0] = 0xfc;
		ZB_TX_buf[1] = size+2;
		ZB_TX_buf[2] = 0x01;
		ZB_TX_buf[3] = type;
		for(uint8_t cnt = 0; cnt < size; cnt++)
		{
			ZB_TX_buf[cnt + 4] = data[cnt];
		}
		HAL_UART_Transmit(&huartZB,ZB_TX_buf,size+4,1000);
		//HAL_GPIO_WritePin(AT_HEX_GPIO_Port,AT_HEX_Pin,GPIO_PIN_SET);
		return HAL_OK;
	}
	else
	{
		return HAL_ERROR;
	}
}

