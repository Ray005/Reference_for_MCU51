//A机器
#include "reg51.h"
#include "stdio.h"
#include "intrins.h"
#define LocalHost 0x41
//#include "uart.h"

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

//--定义使用的IO口--//
sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;


u8 ledduan[]={0x00,0x06,0x38,0xC8,0x68,0x18,0x06,0x00};/*"A",0*/
u8 ledwei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};	//类似于动态数码管的位选
unsigned char mech_step = 1;
unsigned char recv_commond = 0;

void delay(long x){
	int i;
	for(i = 0; i < x ; i++){
	unsigned char i, j;
	i = 2;
	j = 199;
	do
	{		while (--j);
	} while (--i);
	} 
}

void UartInit(void)		//4800bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	//AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
	//AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	//stc中才有这个AUXR寄存器，没有的话，默认选定时器1、12T模式，再删去这一行即可
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	ES = 1;
	EA = 1;
	TR1 = 1;		//启动定时器1
}

char putchar(char c){	//重写了putchar函数，在include stdio.h后就可以使用printf了
	SBUF = c;
	while(!TI);//Here，等待清除标志位，注意这里是阻塞的
	TI = 0;
	return c;
}


void delay2(u16 i)
{
	while(i--);	
}

void LED1(u8 dat1)
{
	P0=dat1;
}
/*******************************************************************************
* 函 数 名         : Hc595SendByte(u8 dat1,u8 dat2)
* 函数功能		   : 通过595发送2个字节的数据
* 输    入         : dat1：第2个595输出数值
*                  * dat2: 第1个595输出数值
* 输    出         : 无
*******************************************************************************/
void Hc595SendByte(u8 dat)
{
	u8 a;

	SRCLK = 1;
	RCLK = 1;

	for(a=0;a<8;a++)		 //发送8位数
	{
		SER = dat >> 7;		 //从最高位开始发送
		dat <<= 1;

		SRCLK = 0;			 //发送时序
		_nop_();
		_nop_();
		SRCLK = 1;	
	}
	RCLK = 0;
	_nop_();
	_nop_();
	RCLK = 1;
}


void main(){
	int i;
	UartInit();
	//printf("Haojie");
		   
	while(1){
		for(i=0;i<8;i++)
	   {
	   		Hc595SendByte(ledduan[i]);
			 LED1(ledwei[i]);			
	   }
		if(recv_commond == '1'){
		P2 = 0x00;
		}
		else if(recv_commond == '0'){
		P2 = 0xFF;
		}

		
	}
}

void uart_ISR() interrupt 4
{
	unsigned char recv_data;
	if(RI){
		RI = 0;
		recv_data = SBUF;
		switch(mech_step){
			case 1:{
			if(recv_data == '^'){
			mech_step = 2;
			}
			}break;
			case 2:{
			if(recv_data == LocalHost){
			mech_step = 3;	
			}
			else {
			mech_step = 1;
			}
			}break;
			case 3:{
			recv_commond = recv_data;
			mech_step = 1;	//接收完毕
				//if(recv_commond == '1')
					{
				printf("【0x41】从机A应答！\r\n");
				}
			}break;
			default :break;
		}

	}
}	