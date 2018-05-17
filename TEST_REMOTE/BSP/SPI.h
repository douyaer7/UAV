#ifndef _SPI_H_
#define _SPI_H_
#include "stm32f10x.h"
/*
6.2.4G:	        CE:PC14
		CSN:PC13
		SCK:PB13
		MOSI:PB15
		MISO:PB14
		IRQ:PC15
*/
#define SPI_SPEED_2   0
#define SPI_SPEED_4   1
#define SPI_SPEED_8   2
#define SPI_SPEED_16  3
#define SPI_SPEED_256 4

#define SPI_CE_H()   GPIO_SetBits(GPIOC, GPIO_Pin_14) 
#define SPI_CE_L()   GPIO_ResetBits(GPIOC, GPIO_Pin_14)

#define SPI_CSN_H()  GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define SPI_CSN_L()  GPIO_ResetBits(GPIOC, GPIO_Pin_13)
u16 ReadIRQData(u16 GPIO_Pin_X);
void SPI2_INIT(void);
u8 SPI_RW(u8 dat);
void SPI1_SetSpeed(u8 SpeedSet);

#endif

