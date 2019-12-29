#ifndef _MAIN_TASK_
#define _MAIN_TASK_
#include "main.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void LD_task(void);
void TX_task(void);
void TR_task(void);

#endif

