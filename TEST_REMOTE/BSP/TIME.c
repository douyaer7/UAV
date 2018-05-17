/**********************************************************************************/
	//author:TJ
	//date:12/1/2014
	//FILE:��ʼ����ʱ�����趨��������ʱʱ��
/************************************************************************************/
#include "stm32f10x.h"
#include "TIME.h"

/*************************************************************************************/


void Tim3_Init(u16 period_num)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//�������ã�ʱ���ͱȽ�������ã���������ֻ�趨ʱ�����Բ���OC�Ƚ����
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	  //time3ʱ��ʹ��
	
	TIM_DeInit(TIM3);  //��λtime3ʱ��
/**********************************************************************************************/

	TIM_TimeBaseStructure.TIM_Period=period_num;//�Զ���װֵ
	/*	  period�Ǽ�������������ʱʱ��Ϊ
			period*��1/f��,���periodΪ500����500us��һ���ж�	*/
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;//��Ƶϵ��	 (1+prescaler)/72*(1+period)=time
	/*	   ��f=72M/(Prescaler+1)Ϊ��׼������
			ÿ1/f�붨ʱ������һ��(����Ϊ1us)	*/
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



