 #ifndef _LED_H
 #define _LED_H
 //***********************************************************
 #include "stm32f10x.h"


#define LED1_OFF  GPIO_SetBits(GPIOA,  GPIO_Pin_0 )
#define LED1_ON GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define LED2_OFF  GPIO_SetBits(GPIOA,  GPIO_Pin_1 )
#define LED2_ON GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define LED3_OFF  GPIO_SetBits(GPIOA,  GPIO_Pin_2 )
#define LED3_ON GPIO_ResetBits(GPIOA,GPIO_Pin_2)


void delay_ms(u16 del);
void LED_INIT();
void LED1_LIGHT();
void LED1_DOWN();
void LED2_LIGHT();
void LED2_DOWN();
void LED3_LIGHT();
void LED3_DOWN();
void LED1_FLASH();
void LED2_FLASH();
void LED3_FLASH();
void LED_ALLOFF();




 //*************************************************************
 #endif