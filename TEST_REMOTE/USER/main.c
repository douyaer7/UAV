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
	 /*TxBuf[0]=(Throttle>>8);//Throttle	//油门量装入待发送数组的前两个字节
      TxBuf[1]=(Throttle&0xff);     
      TxBuf[2]=(Pitch>>8); //Pitch      //俯仰角装入第2,3字节
      TxBuf[3]=(Pitch&0xff);                   
      TxBuf[4]=(Roll>>8);//Roll;        //横滚角转入第4,5字节                  
      TxBuf[5]=(Roll&0xff);
	    TxBuf[6]=(Yaw>>8);//Yaw           //偏航角装入第6,7字节       
      TxBuf[7]=(Yaw&0xff);
			 NRF_TxPacket(TxBuf,8);					
	  //TxBuf[31]=(Throttle<=5) ? 0:0xA5;//紧急熄火标志字节控制 */   
	 }
 }