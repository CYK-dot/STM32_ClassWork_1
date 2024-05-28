#include "led.h"


void LED_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;    
  
  	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	
	
  	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);
	
	//按钮的初始化GPIOG0  和GPIOG1
	/*
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG , ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;    
  
  	GPIO_Init(GPIOG, &GPIO_InitStructure); 
	*/
}

void Sych_Init(void)
{
	
		GPIO_InitTypeDef GPIO_InitStructure;	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;    
  	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	
}

void pwm_init(u16 arr,u16 psc)
{		 					 
		
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
		GPIO_Init(GPIOB, &GPIO_InitStructure); 
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);

		TIM_TimeBaseStructure.TIM_Period = arr; 
		TIM_TimeBaseStructure.TIM_Prescaler =psc; 
		TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
			 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 	
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);  

		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  		
		TIM_Cmd(TIM3, ENABLE); 
	   										  
} 

void exti_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG ,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(GPIOG, &GPIO_InitStructure);

	  GPIO_SetBits(GPIOG, GPIO_Pin_0 | GPIO_Pin_1);

	
	
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

		
  	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource0);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	

 
  	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;		
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
  	NVIC_Init(&NVIC_InitStructure); 	
}
	u16 ix=700;
void EXTI0_IRQHandler(void)
{

	delay_ms(100);
	if(ix<1000)
	{
	    ix+=100;
	    TIM_SetCompare3(TIM3,ix);
  }

	EXTI_ClearITPendingBit(EXTI_Line0); 
}
 

void EXTI1_IRQHandler(void)
{
	delay_ms(100);
  if(ix>200)
	{
	    ix-=100;
	    TIM_SetCompare3(TIM3,ix);
	}
  EXTI_ClearITPendingBit(EXTI_Line1);
}

