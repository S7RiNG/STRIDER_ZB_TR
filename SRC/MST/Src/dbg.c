#include "dbg.h"
uint8_t x1 = 0;
uint8_t line = 0;
void dbg_out_data(uint8_t *pdata)
{
	//OLED_ShowString(x1,line," ");
	OLED_ShowString(x1,line,pdata);
	OLED_ShowString(x1,line+2,".");
	x1 += 8;
	if (x1 > 112)
	{
		x1 = 0;
		line += 2;
	}
}
//void dbg_out_num(uint8_t *pdata,uint8_t size)
//{
//	//OLED_ShowString(x1,line," ");
//	OLED_ShowNum(x1,line,pdata[],3,8);
//	OLED_ShowString(x1,line+2,".");
//	x1 += 8;
//	if (x1 > 112)
//	{
//		x1 = 0;
//		line += 2;
//	}
//}