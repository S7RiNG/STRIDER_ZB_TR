#ifndef _LD_H_
#define _LD_H_

#include "main.h"

void LD_init();
void LD_Set_GRID_SEG(uint8_t Grid,uint8_t SEG);
void LD_Set_brightness(uint8_t toggle, uint8_t bright_level);
void LD_Set_Dsiplay_Mode(void);
void LD_Set_Data_Mode(uint8_t Mode);


#endif
