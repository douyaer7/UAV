 /**************************************************************************************/
		/* author:TJ
		   date:11/10/2014
		   FILE:���ڳ�ʼ�������� ************/
/****************************************************************************/
  #include "stm32f10x.h"
 #include "USART.h"
 #include "LED.h"
#include <stdio.h>


#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))


//typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef union {unsigned char byte[4];float num;}t_floattobyte;
t_floattobyte floattobyte;

 /*********************************************************************************/

void Uart1_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //����USART1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	
	//����PA9��ΪUSART1��Tx
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	//����PA10��ΪUSART1��Rx
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	//����USART1
	//�жϱ�������
	USART_InitStructure.USART_BaudRate = 115200;//br_num;       //�����ʿ���ͨ������վ����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8λ����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;   //��֡��β����1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;    //������żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������ʧ��
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //���͡�����ʹ��
	//����USART1ʱ��
//	USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  //ʱ�ӵ͵�ƽ�
//	USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;  //SLCK������ʱ������ļ���->�͵�ƽ
//	USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;  //ʱ�ӵڶ������ؽ������ݲ���
//	USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; //���һλ���ݵ�ʱ�����岻��SCLK���
	
	USART_Init(USART1, &USART_InitStructure);
//	USART_ClockInit(USART1, &USART_ClockInitStruct);

	//ʹ��USART1�����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//ʹ��USART1 
	USART_Cmd(USART1, ENABLE); 	 
}

/***********printf�ض���********************************************************************/
   //δ�õ�printf
  /*int fputc(int ch,FILE*f)
  {
  	USART_SendData(USART1,(u16)ch);//�������
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //�ж������Ƿ��Ѿ�������
	return ch;
  }	 */


  /**************ʵ�ֺ���****************************************/



/************************************************************************************/
u8 TxBuffer[32];
u8 TxCounter=0;
u8 count=0; 
u8 Rx_Buf[2][32];	//����32�ֽڵĴ��ڽ��ջ���
u8 Rx_Act=0;		//����ʹ�õ�buf��
u8 Rx_Adr=0;		//���ڽ��յڼ��ֽ�
u8 Rx_Ok0 = 0;
u8 Rx_Ok1 = 0;
u8 ARMED ;//extern u8 ARMED ;
u8 WaitForStart ;//extern u8 WaitForStart ;
u8 com_data;//extern	u8 com_data;	



void Uart1_IRQ()
{
	if(USART1->SR & USART_IT_ORE)
	{
		USART1->SR;
	}
	//�����ж�
	if((USART1->SR & (1<<7))&&(USART1->CR1 & USART_CR1_TXEIE))//if(USART_GetITStatus(USART1,USART_IT_TXE)!=RESET)
	{
	 
		USART1->DR = TxBuffer[TxCounter++]; //дDR����жϱ�־          
		if(TxCounter == count)
		{
			USART1->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�ж�
			//LED3_LIGHT();
			//USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
		}
	}
	//�����ж� (���ռĴ����ǿ�) 
	if(USART1->SR & (1<<5))//if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)    
	{
		WaitForStart = 0;
	 com_data = USART1->DR;
		if(Rx_Adr==0)		//Ѱ��֡ͷ0X8A
		{
			if(com_data==0x8A)	//�������������0X8A,��д�뻺��
			{
				Rx_Buf[Rx_Act][0] = com_data;
				Rx_Adr = 1;
			}
		}
		else		//���ڽ�������
		{
			Rx_Buf[Rx_Act][Rx_Adr] = com_data;
			Rx_Adr ++;
		}		
	  if(Rx_Adr==32)		//���ݽ������
		{
			Rx_Adr = 0;
			if(Rx_Act)	
			{ 
				Rx_Act = 0; 			//�л�����
				Rx_Ok1 = 1;
			}
			else 				
			{
				Rx_Act = 1;
				Rx_Ok0 = 1;
			}
		}
	}
} 

 /**************************ʵ�ֺ���********************************************
*******************************************************************************/
 

uint8_t Uart1_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;  
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE); 
	return DataToSend;
}
uint8_t Uart1_Put_Int16(uint16_t DataToSend)
{
	uint8_t sum = 0;
	TxBuffer[count++] = BYTE1(DataToSend);
	TxBuffer[count++] = BYTE0(DataToSend);
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	sum += BYTE1(DataToSend);
	sum += BYTE0(DataToSend);
	return sum;
}
uint8_t Uart1_Put_Float(float DataToSend)
{
	uint8_t sum = 0;
	floattobyte.num=DataToSend;
	TxBuffer[count++] = floattobyte.byte[3];  
	TxBuffer[count++] = floattobyte.byte[2];  
	TxBuffer[count++] = floattobyte.byte[1];  
	TxBuffer[count++] = floattobyte.byte[0];  
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	sum += BYTE3(DataToSend);
	sum += BYTE2(DataToSend);
	sum += BYTE1(DataToSend);
	sum += BYTE0(DataToSend);
	return sum;	
}
void Uart1_Put_String(unsigned char *Str)
{
	//�ж�Strָ��������Ƿ���Ч.
	while(*Str)
	{
	//�Ƿ��ǻس��ַ� �����,������Ӧ�Ļس� 0x0d 0x0a
	if(*Str=='\r')Uart1_Put_Char(0x0d);
		else if(*Str=='\n')Uart1_Put_Char(0x0a);
			else Uart1_Put_Char(*Str);
	//ָ��++ ָ����һ���ֽ�.
	Str++;
	}
}

void Uart1_Put_Buf(unsigned char *DataToSend , u8 data_num)
{
	u8 i=0;	
	for(i=0;i<data_num;i++)
		TxBuffer[count++] = *(DataToSend+i);
	if(!(USART1->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE); 
			//LED3_LIGHT();

}
	
 

