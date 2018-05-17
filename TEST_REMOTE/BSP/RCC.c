  /************************************************************************************
  	data:11/6/2014
  	author:TJ
  	file:RCC.H
  	functon:
 
 / ***************************************************************************/
 #include "RCC.h"
 #include "stm32f10x_flash.h"
 /***************************************************/
 void RCC_Configuration(void)
{

  ErrorStatus HSEStartUpStatus;
  RCC_DeInit();				/* RCC system reset(for debug purpose) RCC�Ĵ����ָ���ʼ��ֵ */
  RCC_HSEConfig(RCC_HSE_ON);	  /* Enable HSE ʹ���ⲿ���پ���*/
  HSEStartUpStatus = RCC_WaitForHSEStartUp();	   /* Wait till HSE is ready �ȴ��ⲿ���پ���ʹ�����*/
  if(HSEStartUpStatus == SUCCESS)
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); /*ѡ��FLASHԤȡָ�����ģʽ*/
    FLASH_SetLatency(FLASH_Latency_2);/*����FLASH�洢����ʱʱ��������0-4MHz,Latency=0;24-8MHz,Latency=1;48~72MHz,Latency=2.	 */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); /*RCC_SYSCLK_Div1--AHBʱ�� = ϵͳʱ��(SYSCLK) = 72MHZ���ⲿ����8HMZ��*/
    RCC_PCLK2Config(RCC_HCLK_Div1);   /* //RCC_HCLK_Div1--APB2ʱ�� = HCLK = 72MHZ���ⲿ����8HMZ��*/
    RCC_PCLK1Config(RCC_HCLK_Div2); /*RCC_HCLK_Div2--APB1ʱ�� = HCLK/2 = 36MHZ���ⲿ����8HMZ�� */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);	 /*����PLL=72MHZ */
    RCC_PLLCmd(ENABLE);	 			/*ʹ��PLL*/
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }

  } 
  //RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA, ENABLE);
 //	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
   
}
	//ע��AHB��Ҫ�����ⲿ�洢��ʱ�ӡ�   
	//      APB2����AD��I/O���߼�TIM������1   
	//      APB1����DA��USB��SPI��I2C��CAN������2��3��4��5����ͨTIM   
	



