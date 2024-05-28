/**
 @name:main.c
 @brief:ʵ��һ������
 @autor:���Ͽ�
**/

/* ===========ͷ�ļ�==================================*/
#include "main.h"

/* ===========ȫ�ֱ���================================*/
double val=-23.45;
char buf[20];
char su;
u8 dotbyte=0;
int   gate1;            // ����ʹ�ܱ���
int   TK = 5;						// �������ڱ���������TK*10ms
int   TC;							  // TK�ı���
float kp = 0.20;				// ����ϵ��
int   ti = 30;					// ����ϵ��	
int   td = 1;						// ΢��ϵ��	
int   IBAND=4096;				// ���ַ���ֵ
int   EK;						    // ��ǰ����ƫ��ֵ
int   EK_1;						  // ��һ�β���ƫ��ֵ
int   AEK;						  // ƫ��ֵ�ı仯��
int   UK,DAOUT;					// DA���ֵ
int  ZEK;
extern u8 AN1,AN2,AN3,AN4;
extern u16 ix;

/* ===========������================================*/
int main(void)
{  
	//debug��ʼ��
	u8 i,j;
	TC     = 1;
	EK=EK_1= 0;							
	AEK=UK = 0;
	ZEK    = 0;
	
	//�����ʼ��
	LED_Init();
	exti_init();          //��ʼ�������ⲿ�жϸı�PWMֵ
	Sych_Init();        //ʹ�ܿ����źŶ˿ڳ�ʼ��
	bsp_InitDAC();
	adc_init();
	TIM_Configuration(1680); //��ʱ����ʼ����PID�㷨�����ڶ�ʱ���ж���ִ��
	
	//ģ���ʼ��
	OLED_Init();
	OLED_Clear();
	OLED_ShowNum(40,30,23,2,16);
	pwm_init(999,8399);      //��ʼ��PWM������Ϊ100ms
	TIM_SetCompare3(TIM3,700);     //��ʼ��PWM����ռ�ձ�Ϊ70%����Ҫע����������Ǫ�͵�ƽ��Ч��
	
	//������
  	while(1)
	{
		wave_main();
		delay_ms(20);
//			  for (j=0;j<63;j++)
//			    OLED_DrawPoint(j,j,1);
//			   
//			OLED_ShowNum(40,30,100-ix/10,2,16);
//			OLED_ShowCHinese(0,0,3);  //��ʾ������
			/*
			  if (GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_0)==0) //KEY1����=0
				 { 
					OLED_ShowNum(40,30,1,2,16);
				 }
			 if (GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_1)==0)  //KEY2����=0
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



