/*    
���ܣ�
1.SPI1��ʼ��
2.��NRF24L01�ӿ�
------------------------------------
*/
#include "SPI.h"
#include "stdio.h"

void SPI2_INIT(void)
{
    SPI_InitTypeDef SPI_InitStructure; 
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
     
    /*���� SPI_NRF_SPI�� SCK,MISO,MOSI���ţ�GPIOB^13,GPIOB^14,GPIOB^15 */ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���ù��� 
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /*����SPI_NRF_SPI��CE���ţ���SPI_NRF_SPI�� CSN ����:*/
    //NRF_CE--PC14,NRF_CSN--PC13,NRF_IRQ--PC15
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_Init(GPIOC, &GPIO_InitStructure);  
		//����NRF_IRQ����
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
    GPIO_Init(GPIOC, &GPIO_InitStructure);  
																								
   
    SPI_CSN_H();
    SPI_CE_L();
		
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //˫��ȫ˫�� 
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //��ģʽ 
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //���ݴ�С8λ 
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; //ʱ�Ӽ��ԣ�����ʱΪ�� 
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //��1��������Ч��������Ϊ����ʱ�� 
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS�ź���������� 
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //8��Ƶ��9MHz 
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //��λ��ǰ 
    SPI_InitStructure.SPI_CRCPolynomial = 7; 
    SPI_Init(SPI2, &SPI_InitStructure); 
    /* Enable SPI2 */ 
    SPI_Cmd(SPI2, ENABLE);
    //printf("SPI���߳�ʼ�����...\r\n");
}


u8 SPI_RW(u8 dat) 
{ 
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); 
    SPI_I2S_SendData(SPI2, dat); 
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);  
    return SPI_I2S_ReceiveData(SPI2); 
}

u16 ReadIRQData(u16 GPIO_Pin_X)
{
u16 IRQ;
IRQ=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_X);
return IRQ;	
}
/*void SPI2_SetSpeed(u8 SpeedSet)
{
	SPI2->CR1&=0XFFC7;//Fsck=Fcpu/256
	if(SpeedSet==SPI_SPEED_2)//???
	{
		SPI2->CR1|=0<<3;//Fsck=Fpclk/2=36Mhz	
	}else if(SpeedSet==SPI_SPEED_8)//??? 
	{
		SPI2->CR1|=2<<3;//Fsck=Fpclk/8=9Mhz	
	}else if(SpeedSet==SPI_SPEED_16)//????
	{
		SPI2->CR1|=3<<3;//Fsck=Fpclk/16=4.5Mhz
	}else			 	 //256??
	{
		SPI2->CR1|=7<<3; //Fsck=Fpclk/256=281.25Khz ????
	}
	SPI2->CR1|=1<<6; //SPI????	  
} */

