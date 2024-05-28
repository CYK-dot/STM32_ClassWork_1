#include "tim.h"

extern int gate1;
extern int TK;						
extern int TC;	
extern float kp;				
extern int ti;						
extern int td;							
extern int IBAND;											
extern int EK_1;						
extern int AEK;							
extern int  ZEK;					
extern int  UK,DAOUT;							
extern int  EK;							
u16 ADCVALUE;
u8 AN1,AN2,AN3,AN4,ANBAK1;
float P,D,I,TEMP;
unsigned int key,keyL1,keyL2,keyL3,keyL4;
unsigned char Lcount=0; 

//������168M=168000000 ��Ƶ1000 �õ�168000 ����1680 �൱��10ms
void TIM_Configuration(uint8_t count)
{		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
		NVIC_InitTypeDef  NVIC_InitStructure; 	

	 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 , ENABLE);
		TIM_TimeBaseStructure.TIM_Period = count-1;//1679;      //����1680   
		TIM_TimeBaseStructure.TIM_Prescaler = 999;   //��Ƶ1000
		TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;     
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
		TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 

		TIM_ClearFlag(TIM8, TIM_FLAG_Update); 
		
		NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn ; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure); 
		TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);
		TIM_Cmd(TIM8,ENABLE);
	
}



void TIM8_UP_TIM13_IRQHandler(void)
{
	  TIM_ClearITPendingBit(TIM8,TIM_IT_Update);
		ADCVALUE=ADC_GetConversionValue(ADC1) ;	
	
		wave_process_main(ADCVALUE);
	  
	/*
  //����GPIOA�ĵ�4λɨ�裨D0--D3) ����D4--D7)��ȡ�������� �ܹ�16��ť������һ��int��������
    switch (Lcount) 
		{
			case 0: //���ĳһ�е͵�ƽ
				GPIO_ResetBits(GPIOA,GPIO_Pin_0);
			  GPIO_SetBits(GPIOA,GPIO_Pin_1);
			  GPIO_SetBits(GPIOA,GPIO_Pin_2);
			  GPIO_SetBits(GPIOA,GPIO_Pin_3);
				//GPIO_Write(GPIOA,0xfffe);
				keyL1=GPIO_ReadInputData(GPIOA);
		
			 	break;
			case 1: //���ĳһ�е͵�ƽ
			ANBAK1=AN1;
	    AN1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1);
			if ((ANBAK1|AN1)==0)
			 {
			 }
			  GPIO_SetBits(GPIOA,GPIO_Pin_0);
			  GPIO_ResetBits(GPIOA,GPIO_Pin_1);
			  GPIO_SetBits(GPIOA,GPIO_Pin_2);
			  GPIO_SetBits(GPIOA,GPIO_Pin_3);
				//GPIO_Write(GPIOA,0xfffd);
				
				break;
			case 2: //���ĳһ�е͵�ƽ
				GPIO_Write(GPIOA,0xfffb);
				keyL3=GPIO_ReadInputData(GPIOA);
				break;
			case 3: //���ĳһ�е͵�ƽ
				GPIO_Write(GPIOA,0xfff7);
				keyL4=GPIO_ReadInputData(GPIOA);
				break;
			default: break;
		}
			
		Lcount++;
    if (Lcount>=4) Lcount=0;	
		
		if ((keyL1&0x0010)==0) //��ť����
		{
			
		}
    				
		
		
	
	  
	*/
		
//		gate1 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15);
//		
//	 if(gate1==1)								
//	  {
//	
//    	EK=EK_1=0;
//		  UK=AEK=0;
//		  ZEK=0;
//	    DAC_SetChannel1Data(DAC_Align_12b_R,2048);
//		  TC=1;
//	  }
//  else //TC�ǲ���ʱ�䣬ʱ�䵽�Ͷ�ȡADת������ֵ
//    {
//		TC--;							
//  	  if(TC==0)
//   		{
//			   ADCVALUE=ADC_GetConversionValue( ADC1) ;	    
//         EK = ADCVALUE-2048;		//		
//			   AEK =EK-EK_1;  
//			   EK_1=EK;
//			   if(fabs(EK)> IBAND) 
//			    	I=0;	
//     		else
//     		   {
//				    ZEK=EK+ZEK;    			
//     		   	I=ZEK*TK;
//			    	I=I/ti;
//			     }
//			   P=EK;
//     		 D=AEK*td;				
//			   D=D/TK;
//         TEMP=(P+I+D)*kp;		
//   		   if(TEMP>0)					
//	 	      {
//	   			  if(TEMP>=2047)
//	      		   	UK=2047;
//	   		  	else
//	      			UK=(int)TEMP;
//	 		    }
//      	  else
//	 	    	{
//	  			if(TEMP<-2048)
//	       			UK=-2048;
//	   			else
//	       			UK=(int)TEMP;
//	 		    }
//      DAOUT=UK+2048;						 
//		  DAC_SetChannel1Data(DAC_Align_12b_R,DAOUT);	

//			TC=TK;							
//		  }
//	 }
	
}

