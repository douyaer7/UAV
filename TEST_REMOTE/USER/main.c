 #include "stm32f10x.h"
  #include "USART.h"
  #include "LED.h"
  #include "TIME.h"
  #include "BSP.h"
	#include "AD.h"
  #include "DTLOAD.h"
  #include "SPI.h"
  #include "NRF24L01.h"

 int main()
 {
	 LED_INIT();
	 Nvic_Init();
	 Uart1_Init();
	 NRF24L01_INIT();
	 SetTX_Mode();
	 Adc_Init();
	 Tim3_Init(500);
	 LED_ALLOFF();
	 LED1_LIGHT();

	 while(1)
	 {
		 Get_AD();
	 /*TxBuf[0]=(Throttle>>8);//Throttle	//������װ������������ǰ�����ֽ�
      TxBuf[1]=(Throttle&0xff);     
      TxBuf[2]=(Pitch>>8); //Pitch      //������װ���2,3�ֽ�
      TxBuf[3]=(Pitch&0xff);                   
      TxBuf[4]=(Roll>>8);//Roll;        //�����ת���4,5�ֽ�                  
      TxBuf[5]=(Roll&0xff);
	    TxBuf[6]=(Yaw>>8);//Yaw           //ƫ����װ���6,7�ֽ�       
      TxBuf[7]=(Yaw&0xff);
			 NRF_TxPacket(TxBuf,8);					
	  //TxBuf[31]=(Throttle<=5) ? 0:0xA5;//����Ϩ���־�ֽڿ��� */   
	 }
 }