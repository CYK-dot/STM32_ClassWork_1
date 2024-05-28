#include "adc.h"


#define  ADC1_DR_ADDRESS         ((uint32_t)0x4001204C) 

void adc_init(void)
{
    GPIO_InitTypeDef      GPIO_InitStructure;
		ADC_InitTypeDef       ADC_InitStructure;
		ADC_CommonInitTypeDef ADC_CommonInitStructure;
		
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	  
		ADC_DeInit();
		ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
		ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
		ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
		ADC_CommonInit(&ADC_CommonInitStructure);

		/* ADC1 Init ****************************************************************/
		ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; 
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfConversion = 1;
		ADC_Init(ADC1, &ADC_InitStructure);

	
		ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_3Cycles);
		ADC_Cmd(ADC1, ENABLE);	
		ADC_SoftwareStartConv(ADC1);

}




uint16_t RCS_Get_ADC(ADC_TypeDef *_ADCx, uint8_t ADC_Channel_x)
{
	ADC_RegularChannelConfig(_ADCx, ADC_Channel_x, 1, ADC_SampleTime_480Cycles); 
	ADC_SoftwareStartConv(_ADCx);
	while (!ADC_GetFlagStatus(_ADCx, ADC_FLAG_EOC)); 
	return ADC_GetConversionValue(_ADCx);
}

float RCS_Get_Voltage(ADC_TypeDef *_ADCx, uint8_t ADC_Channel_x)
{
	return (float)RCS_Get_ADC(_ADCx, ADC_Channel_x) * VOLTAGE_REFERANCE / MAX_RANGE;
}

	
	


