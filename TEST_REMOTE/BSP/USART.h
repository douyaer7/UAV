 /**************************************************************************************/
		/* author:TJ
		   TIME:10/11/2014
		   FILE:���ڳ�ʼ�������� ************/
 /*************************************************************************/
 #ifndef  _USART_H
 #define _USART_H

  #include "stm32f10x.h"

 /****************************************************************************************/
void Uart1_Init();
void Uart1_IRQ(void);
 uint8_t Uart1_Put_Char(unsigned char DataToSend);
 uint8_t Uart1_Put_Int16(uint16_t DataToSend);
 uint8_t Uart1_Put_Float(float DataToSend);
void Uart1_Put_String(u8 *Str);
void Uart1_Put_Buf(unsigned char *DataToSend , u8 data_num);
//extern u8 Rx_Buf[2][32];	//����32�ֽڵĴ��ڽ��ջ���
//extern u8 Rx_Ok0;		//������ϱ�־
//extern u8 Rx_Ok1;


 /********************************************************************/
 #endif
