#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "rtc.h" 


u16 signal=0;
u16 signal_RPM=0;
//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(WK_UP==1)	//WK_UP按键PA0
	{				 
		//BEEP=!BEEP;	
		RTC_Set(2016,5,20,0,0,0);		//时间复位 
	}		 
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
} 
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	signal++;
	EXTI->PR=1<<2;  //清除LINE3上的中断标志位  
}
//外部中断4服务程序  发动机转速测量 
//  一圈八个信号
void EXTI4_IRQHandler(void)
{
	signal_RPM++;
	EXTI->PR=1<<4;  //清除LINE4上的中断标志位  
}		   
//外部中断初始化程序
//初始化PA0/PE3/PE4为中断输入.
void EXTIX_Init(void)
{
	KEY_Init();
	Ex_NVIC_Config(GPIO_A,0,RTIR); 	//上升沿触发 
	Ex_NVIC_Config(GPIO_C,2,FTIR); 	//下降沿触发
 	Ex_NVIC_Config(GPIO_A,4,FTIR); 	//下降沿触发
	MY_NVIC_Init(2,3,EXTI0_IRQn,2);	//抢占2，子优先级3，组2  
	MY_NVIC_Init(2,1,EXTI2_IRQn,2);	//抢占2，子优先级1，组2	   
	MY_NVIC_Init(2,0,EXTI4_IRQn,2);	//抢占2，子优先级0，组2	   
}




///////////////////////////////////////
//外部中断9~5服务程序
//void EXTI9_5_IRQHandler(void)
//{			

//	signal++;						//传感器信号
// 	EXTI->PR=1<<5;     //清除LINE5上的中断标志位  
//}
//void EXTI15_10_IRQHandler(void)
//{			
//	 
//		RTC_Set(2016,5,20,0,0,0);		//时间复位  
//		EXTI->PR=1<<15; 						//清除LINE15上中断标志位
//}
////初始化PA0,PC5,PA15为中断输入.
//void EXTI_Init(void)
//{
//	RCC->APB2ENR|=1<<4;     //使能PORTC时钟
//	JTAG_Set(SWD_ENABLE);		//关闭JTAG,开启SWD
//	GPIOC->CRL&=0XFF0FFFFF;	//PC5设置成输入	  
//	GPIOC->CRL|=0X00800000;   
//	GPIOC->ODR|=1<<5;	   		//PC5上拉  
//	GPIOC->ODR|=1<<5;	   		//PC5上拉 
//	//Ex_NVIC_Config(GPIO_A,0,RTIR); 		//上升沿触发
//	Ex_NVIC_Config(GPIO_C,5,FTIR);		//下降沿触发
//	Ex_NVIC_Config(GPIO_A,15,FTIR);		//下降沿触发

////	MY_NVIC_Init(2,2,EXTI0_IRQn,2);    	//抢占2，子优先级2，组2
//	MY_NVIC_Init(2,1,EXTI9_5_IRQn,2);  	//抢占2，子优先级1，组2
//	MY_NVIC_Init(2,0,EXTI15_10_IRQn,2);	//抢占2，子优先级0，组2	   
//}

