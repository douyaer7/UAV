
#include "stm32f10x.h"
#include "LED.h"



 void delay_ms(u16 del)
 {
 	u16 i,j;
	for(i=0;i<del;i++)
		for(j=0;j<8500;j++);
 }

 void LED_INIT()
 {
	GPIO_InitTypeDef GPIO_InitStructure;
	//使能LED用的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); //打开外设A的时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

 }

 void LED1_LIGHT()
 {
 	LED1_ON;
 }
  void LED1_DOWN()
 {
 	LED1_OFF;
 }

 void LED2_LIGHT()
 {
 	LED2_ON;
 }
  void LED2_DOWN()
 {
 	LED2_OFF;
 }

 void LED3_LIGHT()
 {
 	 LED3_ON;
 }
 void LED3_DOWN()
 {
 LED3_OFF;
 }
 
 
 void LED1_FLASH()
 {
 	 	LED1_ON;
	delay_ms(50);
	  	LED1_OFF;
	delay_ms(50);

 }
  void LED2_FLASH()
  {
  	 	LED2_ON;
	delay_ms(500);
	  	LED2_OFF;
	delay_ms(500);
  }
	 void LED3_FLASH()
  {
  	 	LED3_ON;
	delay_ms(500);
	  	LED3_OFF;
	delay_ms(500);
  }

 void LED_ALLOFF()
 {
 	   	  	LED1_OFF;
	   	   	LED2_OFF;
 	   	  	LED3_OFF;

 }

