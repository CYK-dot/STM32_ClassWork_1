#ifndef __ADC_H
#define __ADC_H

#include "main.h"

#define VOLTAGE_REFERANCE	5.0f
#define	MAX_RANGE			  4096


void adc_init(void);
uint16_t RCS_Get_ADC(ADC_TypeDef *_ADCx, uint8_t ADC_Channel_x);
float RCS_Get_Voltage(ADC_TypeDef *_ADCx, uint8_t ADC_Channel_x);

#endif


