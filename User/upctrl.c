/**
 @filename:upctrl.c
 @brief:实现实验一的全部功能
 @author:陈煜楷
**/

/* ==========头文件=====================================*/
#include "upctrl.h"

/* ==========私有全局变量===============================*/
uint16_t oled_wave[128],wave_pointer;
uint16_t max_volt,min_volt;
uint64_t time_tick;
uint8_t  overload_flag;

float max_volt_f32,min_volt_f32,real_time,overload_time;
uint16_t freq_tick;

float32_t raw_adc_data[SAMPLE_BUFFER_LEN];
arm_linear_interp_instance_f32 s;

/* ===========静态函数声明===============================*/
static void wave_add(int16_t adc_value);
static void wave_process(int16_t adc_value);
static void wave_timetick_add(void);
static void wave_draw(void);
static void wave_show_char(void);
static float interportion(float index);
static uint8_t wave_sample(int16_t adc_value);

/* ===========导出函数接口===============================*/
/**
* @name:wave_add
* @brief:将一个adc采样点送入sample buffer
* @param:uint16_t adc采样到的数据  
**/
static void wave_add(int16_t adc_value)
{
	static uint32_t roll_sample_rate=1;
	static uint32_t sample_staus=1;
	
	//auto get sample rate
	roll_sample_rate= 1;
	
	//wait tick to arrive
	if (sample_staus<roll_sample_rate)
	{
		sample_staus++;
	}
	//add value to wave
	else
	{
		sample_staus=1;
		//溢出，则将数据向左平移一格
		if (wave_pointer >= OLED_MAX_PIXEL_X)
		{	
			for(uint8_t i=0;i<OLED_MAX_PIXEL_X;i++)
			{
				oled_wave[i]=oled_wave[i+1];
			}
			oled_wave[wave_pointer]=adc_value;
		}
		//未溢出，则直接将数据加入列表
		else
		{
			wave_pointer++;
			oled_wave[wave_pointer]=adc_value;
		}
	}
}


/**
* @name:wave_process
* @brief:处理和分析adc buffer数据
* @param:uint16_t adc采样到的数据   
**/
uint8_t sample_status=0;
static void wave_process(int16_t adc_value)
{
	static float last_adc_value;
	static int16_t sample_count; 
	
	float adc_volt=(((float)(adc_value-ADC_VALUE_MID))/ADC_VALUE_MID)*ADC_REF_VOLTAGE;
	//超电压检测
	if (((((float)(adc_value-ADC_VALUE_MID))/ADC_VALUE_MID)*ADC_REF_VOLTAGE)>OVERLOAD_VOLTAGE)
	{
		overload_flag=1;
		overload_time=real_time;//记录上次超电压的真实时间
	}
	
	//峰峰值检测
	max_volt=0;
	min_volt=0;
	for(int i=0;i<OLED_MAX_PIXEL_X;i++)
	{
		if (oled_wave[i]>max_volt)
		{
			max_volt=oled_wave[i];
			max_volt_f32=(((float)(max_volt-ADC_VALUE_MID))/((float)(ADC_VALUE_MID)))*ADC_REF_VOLTAGE;
		}
		if (oled_wave[i]<min_volt) 
		{
			min_volt=oled_wave[i];
			min_volt_f32=(((float)(min_volt-ADC_VALUE_MID))/((float)(ADC_VALUE_MID)))*ADC_REF_VOLTAGE;
		}
	}
	
	
	//frequency
	switch(sample_status)
	{
		//get up trigger
		case 0:
			sample_count=0;
			
			if (last_adc_value<ADC_VALUE_MID && adc_value>ADC_VALUE_MID)
			{
				sample_status++;
			}
		break;
		
		//get down trigger
		case 1:
			sample_count++;
		
			if (last_adc_value>ADC_VALUE_MID && adc_value<ADC_VALUE_MID)
			{
				sample_status++;
			}
		break;
		
		//output frequency
		case 2:
			freq_tick=sample_count;
			sample_count=0;
			
			sample_status=0;
		break;
	}
	last_adc_value=adc_value;
}

/**
* @name:wave_timetick_add
* @brief:记录定时中断的次数，并以此计算真实时间
**/
static void wave_timetick_add(void)
{
	time_tick++;
	real_time=time_tick*TIM_TICK_PERIOD;
}


/**
* @name:wave_process_main
* @brief:数据处理总成
**/
void wave_process_main(int16_t adc_value)
{
	static uint8_t sample_rating=0;
	
	wave_timetick_add();
	sample_rating++;
	
	if (sample_rating==SAMPLE_RATE)
	{
		wave_add(adc_value);
		wave_process(adc_value);
		sample_rating=0;
	}
}






/**
* @name:wave_draw
* @brief:在屏幕上画实时波形曲线
**/
static void wave_draw(void)
{
	for(uint8_t i=0;i<=126;i++)
	{
		uint8_t pixel=(((float)(oled_wave[i]-2048.0f))/2048.0f)*(WAVE_WIDE)+WAVE_CENTER;
		OLED_DrawPoint(i,pixel,1);
	}
}

/**
* @name:wave_show_char
* @brief:在屏幕上打印adc分析信息
**/
static void wave_show_char(void)
{
	char logs[40],logs2[40],logs3[40];
	
	sprintf(logs,"U=%.1f PP=%.1f",(((float)(oled_wave[126]-ADC_VALUE_MID))/ADC_VALUE_MID)*ADC_REF_VOLTAGE,(max_volt_f32-min_volt_f32));
	OLED_ShowString(0,35,logs);
	sprintf(logs2,"nt=%.2f f=%.2f",real_time,1.0f/(TIM_TICK_PERIOD*freq_tick*2.0f));
	OLED_ShowString(0,50,logs2);

}

/**
* @name:wave_main
* @brief:oled完整adc功能
**/
void wave_main(void)
{
	OLED_Clear();
	wave_draw();
	wave_show_char();
	
	delay_ms(20);//避免刷屏过于频繁看不到字
}








