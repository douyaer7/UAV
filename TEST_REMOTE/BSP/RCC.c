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
  RCC_DeInit();				/* RCC system reset(for debug purpose) RCC寄存器恢复初始化值 */
  RCC_HSEConfig(RCC_HSE_ON);	  /* Enable HSE 使能外部高速晶振*/
  HSEStartUpStatus = RCC_WaitForHSEStartUp();	   /* Wait till HSE is ready 等待外部高速晶振使能完成*/
  if(HSEStartUpStatus == SUCCESS)
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); /*选择FLASH预取指缓存的模式*/
    FLASH_SetLatency(FLASH_Latency_2);/*设置FLASH存储器延时时钟周期数0-4MHz,Latency=0;24-8MHz,Latency=1;48~72MHz,Latency=2.	 */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); /*RCC_SYSCLK_Div1--AHB时钟 = 系统时钟(SYSCLK) = 72MHZ（外部晶振8HMZ）*/
    RCC_PCLK2Config(RCC_HCLK_Div1);   /* //RCC_HCLK_Div1--APB2时钟 = HCLK = 72MHZ（外部晶振8HMZ）*/
    RCC_PCLK1Config(RCC_HCLK_Div2); /*RCC_HCLK_Div2--APB1时钟 = HCLK/2 = 36MHZ（外部晶振8HMZ） */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);	 /*设置PLL=72MHZ */
    RCC_PLLCmd(ENABLE);	 			/*使能PLL*/
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
	//注：AHB主要负责外部存储器时钟。   
	//      APB2负责AD，I/O，高级TIM，串口1   
	//      APB1负责DA，USB，SPI，I2C，CAN，串口2，3，4，5，普通TIM   
	



