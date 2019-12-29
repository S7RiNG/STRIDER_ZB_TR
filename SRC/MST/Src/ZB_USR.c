#include "ZB_USR.h"
#include "main.h"
uint8_t key[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void ZB_init_USR(void)//
{
	uint8_t buf[10];
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+GROUP=2",10,1000);
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+CH=11",8,1000);
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3,(uint8_t*)"AT+TXPOWER=4",12,1000);
	HAL_Delay(100);
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
