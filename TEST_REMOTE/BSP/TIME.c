/**********************************************************************************/
	//author:TJ
	//date:12/1/2014
	//FILE:初始化定时器，设定整个程序定时时间
/************************************************************************************/
#include "stm32f10x.h"
#include "TIME.h"

/*************************************************************************************/


void Tim3_Init(u16 period_num)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//基础设置，时基和比较输出设置，由于这里只需定时，所以不用OC比较输出
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	  //time3时钟使能
	
	TIM_DeInit(TIM3);  //复位time3时钟
/**********************************************************************************************/

	TIM_TimeBaseStructure.TIM_Period=period_num;//自动重装值
	/*	  period是计数次数，最后计时时间为
			period*（1/f）,如果period为500，则500us进一次中断	*/
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;//分频系数	 (1+prescaler)/72*(1+period)=time
	/*	   以f=72M/(Prescaler+1)为基准计数，
			每1/f秒定时器计数一次(这里为1us)	*/
/************************************************************************************************/
	//set clock division 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //or TIM_CKD_DIV2 or TIM_CKD_DIV4
	//count up
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	//clear the TIM2 overflow interrupt flag
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	//enable TIM2 overflow interrupt 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//enable TIM2
	TIM_Cmd(TIM3,ENABLE);
}



