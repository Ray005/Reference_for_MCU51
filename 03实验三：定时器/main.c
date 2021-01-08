#include "reg52.h"
#define GPIO_DIG P0
#define GPIO_KEY P1

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit LED_const = P2^1;


unsigned char KeyValue;	//用来存放读取到的键值


unsigned char code smgduan[17]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//显示0~F的值


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
unsigned char mode = 1;

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

void weixuan(int i){
switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=1;LSB=1;LSC=1; break;//显示第7位
			case(1):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(2):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(3):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(4):
				LSA=1;LSB=1;LSC=0; break;//显示第3位 
			case(5):
				LSA=0;LSB=1;LSC=0; break;//显示第2位 
			case(6):
				LSA=1;LSB=0;LSC=0; break;//显示第1位 
			case(7):
				LSA=0;LSB=0;LSC=0; break;//显示第0位	
		}
	}


void main(){
	Timer0Init();
	while(1){
	key_val = keypros();
	
		
		switch(key_val)
			{case 1:mode = 1; break;
			case 2: 
		if(speed<16){speed++;}
		else {speed = 16;}
		break;
		case 3: 
		if(speed>=1){speed--;}
		break;
		case 4:mode = 4;break;
			default :break;
		}
		if(speed != speed_old)
		{
		counter = counterCul(0.2 + speed/20.0);
		counter_OFF = 65535- (counter - 64613);
		TL0_ON = counter;
		TH0_ON = counter>>8;
		TL0_OFF = counter_OFF;
		TH0_OFF = counter_OFF>>8;
		//P2 = TL0_ON;
		speed_old = speed;
		}
		////显示程序段
		if(mode ==1){
		weixuan(0);
		GPIO_DIG=0x6d;	  //在第0位显示字母S
		delay(2);
		weixuan(1);
		GPIO_DIG=0x73;	  //在第0位显示字母P
		delay(2);
		weixuan(2);
		GPIO_DIG=0x79;	  //在第0位显示字母E
		delay(2);
		weixuan(3);
		GPIO_DIG=0x79;	  //在第0位显示字母E
		delay(2);
		weixuan(4);
		GPIO_DIG=~smgduan[13];	  //在第0位显示字母d
		delay(2);
		if(speed<10){								//在小于10的时候，在第3位显示按键序号数字
	  weixuan(7);
		GPIO_DIG=~smgduan[speed];	  
		delay(2);
		}
		
		if(speed>=10){
		weixuan(6);
		GPIO_DIG=~smgduan[1];	  
		delay(2);
			
		weixuan(7);
		GPIO_DIG=~smgduan[speed-10];	  
		delay(2);
		}		
	}
	
		if(mode ==4){
		int duty = (0.2 + speed/20.0)*100;	
			
		weixuan(0);
		GPIO_DIG=0x5e;	  //在第0位显示字母d
		delay(2);
		weixuan(1);
		GPIO_DIG=0x3e;	  //在第0位显示字母u
		delay(2);
		weixuan(2);
		GPIO_DIG=0x78;	  //在第0位显示字母t
		delay(2);
		weixuan(3);
		GPIO_DIG=0x6e;	  //在第0位显示字母y
		delay(2);
		
		if(duty < 100&& duty > 20){
		weixuan(6);
		GPIO_DIG=~smgduan[(int)(duty/10)];	  
		delay(2);
			
		weixuan(7);
		GPIO_DIG=~smgduan[(int)(duty%10)];	  
		delay(2);	
		}
		else if(duty >= 100){
		weixuan(5);
		GPIO_DIG=~smgduan[1];	  
		delay(2);
			
		weixuan(6);
		GPIO_DIG=~smgduan[0];	  
		delay(2);
			
		weixuan(7);
		GPIO_DIG=~smgduan[0];	  
		delay(2);	
		}
		else {
		weixuan(4);
		GPIO_DIG=~smgduan[5];	  //在第0位显示字母s
		delay(2);
		weixuan(5);
		GPIO_DIG=0x78;	  //在第0位显示字母t
		delay(2);
		weixuan(6);
		GPIO_DIG=0x5c;	  //在第0位显示字母o
		delay(2);
		weixuan(7);
		GPIO_DIG=0x73;	  //在第0位显示字母p
		delay(2);
		}
		
	}
	
	}
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
	
