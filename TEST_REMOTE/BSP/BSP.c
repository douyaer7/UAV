/*******************************************************************************/
//Author:TJ
//Data:11/28/2104
//FILE:�ж��������ʼ��
/*************************************************************************************/
#include "stm32f10x.h"
#include "BSP.h"


void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* NVIC_PriorityGroup */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ѡ����鷽ʽ
	//����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// ������Ӧ�ж�������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 	//������Ӧ�ж���������Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);	  //��ʼ��
		//TIME3
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
