#ifndef _ZB_USR_
#define _ZB_USR_

#include "main.h"


#define huartZB huart3

void ZB_init_USR(void);
void ZB_reset(void);
HAL_StatusTypeDef ZB_TX_BC(uint8_t* data, uint8_t size, uint8_t type);

#endif