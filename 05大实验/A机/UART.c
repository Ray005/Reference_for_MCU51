#include "UART.h"
extern unsigned char mech_step;
extern unsigned char recv_commond;
extern unsigned char safeState;

char putchar(char c){	//重写了putchar函数，在include stdio.h后就可以使用printf了
	SBUF = c;
	while(!TI);//Here，等待清除标志位，注意这里是阻塞的
	TI = 0;
	return c;
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