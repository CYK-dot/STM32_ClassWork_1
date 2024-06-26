/**
 @filename:tim.h
 @brief:完善实验一的定时中断功能
 @author:陈煜楷
**/

/* ----------.h head----------------------------*/
#ifndef __TIM_H
#define __TIM_H

/* ----------头文件------------------------------*/
#include "main.h"

/* ----------配置宏------------------------------*/
# define TIM_TICK_PERIOD 0.0010f

/* ---------导出接口----------------------------*/
void TIM_Configuration(uint8_t count);

/* ----------.h head----------------------------*/
#endif



