#ifndef _TASKS_ 
#define _TASKS_
#include "main.h"
#include "stdio.h"

void OLED_task();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
int fputc(int ch, FILE* stream);
void mode_task();
void TH_task();


#endif