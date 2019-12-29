#ifndef _OLED_USR_
#define _OLED_USR_

#include "oled.h"
\
void OLED_usr_init(void);
void OLED_show_UI(void);
void OLED_show_data(float tmp,float rh, uint8_t NODE);
void OLED_show_OV(uint8_t bmOV);
void OLED_Clear_OV();
void OLED_show_TH(uint8_t tmp,uint8_t rh,uint8_t tmph,uint8_t rhh,uint8_t THC_flag,uint8_t THR_flag);
void OLED_show_selecter(uint8_t slct_num,uint8_t mode);
void OLED_show_subselecter(uint8_t slct_num,uint8_t slct_sub,uint8_t mode);

#endif