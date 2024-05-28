/**
 @name:main.c
 @brief:实验一主函数
 @autor:陈煜楷
**/

/* ===========头文件==================================*/
#include "main.h"

/* ===========全局变量================================*/
double val=-23.45;
char buf[20];
char su;
u8 dotbyte=0;
int   gate1;            // 启动使能变量
int   TK = 5;						// 采样周期变量，等于TK*10ms
int   TC;							  // TK的变量
float kp = 0.20;				// 比例系数
int   ti = 30;					// 积分系数	
int   td = 1;						// 微分系数	
int   IBAND=4096;				// 积分分离值
int   EK;						    // 当前采样偏差值
int   EK_1;						  // 上一次采样偏差值
int   AEK;						  // 偏差值的变化量
int   UK,DAOUT;					// DA输出值
int  ZEK;
extern u8 AN1,AN2,AN3,AN4;
extern u16 ix;

/* ===========主任务================================*/
int main(void)
{  
	//debug初始化
	u8 i,j;
	TC     = 1;
	EK=EK_1= 0;							
	AEK=UK = 0;
	ZEK    = 0;
	
	//外设初始化
	LED_Init();
	exti_init();          //初始化按键外部中断改变PWM值
	Sych_Init();        //使能控制信号端口初始化
	bsp_InitDAC();
	adc_init();
	TIM_Configuration(1680); //定时器初始化，PID算法部分在定时器中断中执行
	
	//模块初始化
	OLED_Init();
	OLED_Clear();
	OLED_ShowNum(40,30,23,2,16);
	pwm_init(999,8399);      //初始化PWM，周期为100ms
	TIM_SetCompare3(TIM3,700);     //初始化PWM波的占空比为70%，但要注意驱动单允仟低电平有效的
	
	//主任务
  	while(1)
	{
		wave_main();
		delay_ms(20);
//			  for (j=0;j<63;j++)
//			    OLED_DrawPoint(j,j,1);
//			   
//			OLED_ShowNum(40,30,100-ix/10,2,16);
//			OLED_ShowCHinese(0,0,3);  //显示“都”
			/*
			  if (GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_0)==0) //KEY1按下=0
				 { 
					OLED_ShowNum(40,30,1,2,16);
				 }
			 if (GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_1)==0)  //KEY2按下=0
				 { 
					OLED_ShowNum(40,30,2,2,16);
				 }
			*/
				 /*
				GPIO_ResetBits(GPIOB,GPIO_Pin_10);
			  delay_ms(500);
			  GPIO_SetBits(GPIOB,GPIO_Pin_10);
			  delay_ms(500);
				 */
	}
}



