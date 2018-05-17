/*
	  DATE:2015/1/20
	  AUTHOR:TJ
	  FILE:摇杆电位器数据采集
	  						*/
///////////////////////////////////////////////////////////////////////////////////////
#include "stm32f10x.h"
#include "AD.h"
#include "DTLOAD.h"
#include "USART.h"
#include "LED.h"
///////////////////////////////////////////////////////////////////////////////////////
//定义相关数据变量
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

u16 Throttle;
s16 Yaw;
s16 Pitch;
s16 Roll;
u16 Battery;
u8 data_to_send[50];
vs32 Alt;


////////////////////////////////////////////////////////////////////////////////////////

void Get_AD()
{
      Throttle=2000-1000*(Get_Adc_Average(5,15))/4096;
   Throttle=(Throttle<=0)?0:Throttle;
   Throttle=(Throttle>=2000)?2000:Throttle;

      Roll=2000-1000*(Get_Adc_Average(7,15))/4096;
   Roll=(Roll<=0)?0:Roll;
   Roll=(Roll>=2000)?2000:Roll;

   	  Pitch=2000-1000*(Get_Adc_Average(6,15))/4096;//2000-1000*(Get_Adc_Average(6,15))/4096;
   Pitch=(Pitch<=0)?0:Pitch;
   Pitch=(Pitch>=2000)?2000:Pitch;

}

void Data_Send_Status(void)
{
	u8 _cnt=0;
	u8 sum=0;
	u8 i;
	vs16 _temp;
	vs32 _temp2=Alt;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAF;
	data_to_send[_cnt++]=0x03;
	data_to_send[_cnt++]=0;
	//vs16 _temp;
	_temp = Throttle;	 
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0;//yaw;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = Roll;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = Pitch;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	//_temp2= 0;//Alt;						//altitude
	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);
		
	//if(Rc_C.ARMED==0)			data_to_send[_cnt++]=0xA0;	//锁定
//	else if(Rc_C.ARMED==1)		data_to_send[_cnt++]=0xA1;
	
//	data_to_send[3] = _cnt-4;
	
	//u8 sum = 0;
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	Uart1_Put_Buf(data_to_send,_cnt);
}

