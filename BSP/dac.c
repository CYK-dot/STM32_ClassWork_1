#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "dac.h"

void DAC_GPIOConfig(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStructure;  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);     
}


void DAC_Ch1_SineWaveConfig(void) 
{ 
    DAC_InitTypeDef  DAC_InitStructure;   
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_None ; 
	
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable; 
	
    DAC_Init(DAC_Channel_1, &DAC_InitStructure); 
	
    DAC_Cmd(DAC_Channel_1, ENABLE);  
	
	  DAC_SetChannel1Data(DAC_Align_12b_R,2048);
    
}







		
void bsp_InitDAC(void) 
{    
    DAC_GPIOConfig();  
    DAC_Ch1_SineWaveConfig(); 
}		
		







