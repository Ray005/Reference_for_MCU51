#include "pwm.h"

void moto_turn(int turn){
	if(turn == 0){
	moto_pos = 1;
	}
	else {
	moto_pos = 0;
	}
	

}
unsigned int counterCul(float dutycycle){//1kHz
	return 65535-(int)(1000*dutycycle*11.0592/12.0);//pwm周期为1000us即1ms（1kHz）
}

void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。
	TH0=0XCD;	//给定时器赋初值，定时1ms
	TL0=0XD4;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器			
}

void Timer0() interrupt 1
{
	if(speed ==0 ){
	moto_pos = 1;
	}
	if(moto_pos == 0)
    {		
			P2 = P2 & 0x1C | 0x00;
        moto_pos = 1;        //设置高电平持续时间
        TH0 = TH0_ON;
        TL0 = TL0_ON;
    }
    else
    {		P2 = P2 & 0x1C | 0xE3;
        moto_pos = 0;        //设置低电平持续时间         
			TH0 = TH0_OFF;
      TL0 = TL0_OFF;
    }
}
	