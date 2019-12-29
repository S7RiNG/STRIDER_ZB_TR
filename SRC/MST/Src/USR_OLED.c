#include "USR_OLED.h"
		
void OLED_usr_init(void)
{
	OLED_Init();			
	OLED_Clear(); 
}
void OLED_show_UI(void)
{
	//OLED_Clear();
	OLED_ShowString(0,0,"T|C:");
	OLED_ShowString(0,2,"R|%:");  
	OLED_ShowString(96,6,"ND:");   
	OLED_ShowString(8,4,"RT:"); 
	OLED_ShowString(8,6,"RH:"); 
}

void OLED_show_selecter(uint8_t slct_num,uint8_t mode)
{
	char *selecter;
	char selecter_h[] = "#";
	char selecter_a[] = ">";
	if(mode == 0)
	{
		selecter = selecter_a;
	}
	else
	{
		selecter = selecter_h;
	}
	
	if(slct_num == 1)
	{
		OLED_ShowString(0,4,selecter);
	}
	else
	{
		OLED_ShowString(0,4," ");
	}
	
	if(slct_num == 2)
	{
		OLED_ShowString(0,6,selecter);
	}
	else
	{
		OLED_ShowString(0,6," ");
	}
	
	if(slct_num == 3)
	{
		OLED_ShowString(88,6,selecter);
	}
	else
	{
		OLED_ShowString(88,6," ");
	}
	
}

void OLED_show_subselecter(uint8_t slct_num,uint8_t slct_sub,uint8_t mode)
{
	char *selecter;
	char selecter_h[] = "#";
	char selecter_a[] = "<";
	uint8_t y;
	
	if(slct_num == 1)
	{
		y = 4;
	}
	else
	{
		y = 6;
	}
	
	if(mode == 0)
	{
		selecter = selecter_a;
	}
	else
	{
		selecter = selecter_h;
	}
	
	if(slct_sub == 2)
	{
		OLED_ShowString(72,y,selecter);
	}
	else
	{
		OLED_ShowString(72,y," ");
	}
	
	if(slct_sub == 1)
	{
		OLED_ShowString(48,y,selecter);
	}
	else
	{
		OLED_ShowString(48,y," ");
	}
}

void OLED_show_OV(uint8_t bmOV) //bit t1,r1,t2,r2,t3,r3
{
	OLED_Clear_OV();
	if(bmOV)
	{
		OLED_ShowString(96,0,"OVER");
		OLED_ShowString(96,2,"T");
		OLED_ShowString(96,4,"H");
		for(uint8_t i = 0 ; i < 6; i++)
		{
			if(bmOV & 1<<i)
			{
				OLED_ShowNum(104+(8*(uint8_t)(i/2)),2+2*(i%2),1+(uint8_t)(i/2),1,8);
			}
		}
	}
}

void OLED_Clear_OV()
{
	OLED_ShowString(96,0,"    ");
	OLED_ShowString(96,4,"    ");
	OLED_ShowString(96,2,"    ");
}


void OLED_show_data(float tmp,float rh, uint8_t NODE)
{
	uint8_t TmpH;
	uint8_t TmpL;
	uint8_t RhH;
	uint8_t RhL;
	float TP = tmp;
	float RH = rh;
	TP *= 100;
	RH *= 100;
	
	TmpH = ((uint16_t)TP)/100;
	TmpL = ((uint16_t)TP)%100;
	
	RhH = ((uint16_t)RH)/100;
	RhL = ((uint16_t)RH)%100;
	
	OLED_ShowString(50,0,".");
	OLED_ShowString(50,2,"."); 
	OLED_ShowNum(32,0,TmpH,2,16);
	OLED_ShowNum(54,0,TmpL,2,16);
	OLED_ShowNum(32,2,RhH,2,16);
	OLED_ShowNum(54,2,RhL,2,16);
	OLED_ShowNum(120,6,NODE,1,16);
}



void OLED_show_TH(uint8_t tmp,uint8_t rh,uint8_t tmph,uint8_t rhh,uint8_t THC_flag,uint8_t THR_flag)
{
	
	
	if(THC_flag)
	{
		
		OLED_ShowString(48,4,"     ");
		OLED_ShowNum(32,4,tmph,2,16);
		OLED_ShowNum(54,4,tmp,2,16);
		
	}
	else
		OLED_ShowString(32,4," OFF ");
	
	if(THR_flag)
	{
		OLED_ShowString(32,6,"     ");
		OLED_ShowNum(32,6,rhh,2,16);
		OLED_ShowNum(54,6,rh,2,16);
	}
	else
		OLED_ShowString(32,6," OFF ");
}