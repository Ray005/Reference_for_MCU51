#include "reg52.h"

sbit moto_pos = P1^0;
//sbit moto_neg = P1^1;
sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;
sbit k4 = P3^3;
sbit led = P2^0;

unsigned char TL0_ON ,TH0_ON,TL0_OFF,TH0_OFF;//u16
unsigned char key_val;
unsigned char speed = 1,speed_old;
unsigned int  counter = 0xFFF0,counter_OFF = 0xFFF0;

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	//_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void delayus(long x){
int i;
	for(i = 0; i < x/10; i++){
	Delay10us();
	}
}

void delay(long x){
	int i;
	for(i = 0; i < x ; i++){
	Delay1ms();
	}
}



int keypros()
{
	if(k1==0)		  //检测按键K1是否按下
	{	//k1 = 1;
		delay(10);   //消除抖动 一般大约10ms
		if(k1==0)	 //再次判断按键是否按下
		{	while(!k1);
			return 1;	  
		}
		
	}
		
	
		if(k2==0)		  //检测按键K1是否按下
	{	//k2 = 1;
		delay(10);   //消除抖动 一般大约10ms
		if(k2==0)	 //再次判断按键是否按下
		{	
			while(!k2)delay(10);
			return 2;	  //led状态取反
		}
	}
	
	
		if(k3==0)		  //检测按键K1是否按下
	{	
		delay(10);   //消除抖动 一般大约10ms
		if(k3==0)	 //再次判断按键是否按下
		{
			while(!k3);
			return 3;	  //led状态取反
		}
		
	}
	
	
		if(k4==0)		  //检测按键K1是否按下
	{	
		delay(10);   //消除抖动 一般大约10ms
		if(k4==0)	 //再次判断按键是否按下
		{
			while(!k4);
			return 4;	  //led状态取反
		}
		while(!k4);
	}
	
	return -1;
}

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



void main(){
	Timer0Init();
	while(1){
	key_val = keypros();
		switch(key_val)
		{case 2: 
		if(speed<10){speed++;}
		else {speed = 10;}
		break;
		case 3: 
		if(speed>1){speed--;}
		break;
			default :break;
		}
		if(speed != speed_old)
		{
		counter = counterCul(speed/10.0);
		counter_OFF = 65535- (counter - 64613);
		TL0_ON = counter;
		TH0_ON = counter>>8;
		TL0_OFF = counter_OFF;
		TH0_OFF = counter_OFF>>8;
		//P2 = TL0_ON;
		speed_old = speed;
		}
	}
}

void Timer0() interrupt 1
{

	if(moto_pos == 0)
    {		
			led = 0;
        moto_pos = 1;        //设置高电平持续时间
        TH0 = TH0_ON;
        TL0 = TL0_ON;

    }
    else
    {		led = 1;
        moto_pos = 0;        //设置低电平持续时间         
			TH0 = TH0_OFF;
      TL0 = TL0_OFF;
    }
}
	
