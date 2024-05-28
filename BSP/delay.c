#include "delay.h"

void delay_us(u32 x)//usÑÓÊ±
{ 
	u32 _dcnt; 
      _dcnt=(x*45); 
      while(_dcnt-- > 0) ;
}
void delay_ms(u32 x)
{
	delay_us(x*1000);
}

