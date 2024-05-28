/**
 @filename:upctrl.h
 @brief:实现实验一的全部功能
 @author:陈煜楷
**/

/* ----------.h head----------------------------*/
#ifndef upctrl_H_
#define upctrl_H_

/* ----------头文件------------------------------*/
#include "main.h"
#include "interpolation_functions.h"

/* ----------配置宏------------------------------*/
#define ADC_REF_VOLTAGE 5.0f    //ADC参考电压
#define OVERLOAD_VOLTAGE 4.5f   //报警电压

#define SAMPLE_BUFFER_LEN  400
#define SAMPLE_INTERP_RATE 4
#define SAMPLE_RATE        2

#define ADC_VALUE_MAX   4096    
#define ADC_VALUE_MID   2048

#define OLED_MAX_PIXEL_X 126
#define OLED_MAX_PIXEL_Y 64

#define WAVE_WIDE 10.0f
#define WAVE_CENTER 53

/* ---------导出接口----------------------------*/
void wave_main(void);
void wave_process_main(int16_t adc_value);

/* ----------.h head----------------------------*/
#endif