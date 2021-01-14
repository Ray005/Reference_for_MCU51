#include "disp.h"
#include "delay.h"


extern unsigned char DisplayData[5];
unsigned char code smgduan[17]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//显示0~F的值

void display_smg(){
		////显示程序段
		if(mode ==1){
		weixuan(0);
		GPIO_DIG=0x6d;	  //在第0位显示字母S
		delay(1);
		weixuan(1);
		GPIO_DIG=0x73;	  //在第0位显示字母P
		delay(1);
		weixuan(2);
		GPIO_DIG=0x79;	  //在第0位显示字母E
		delay(1);
		weixuan(3);
		GPIO_DIG=0x79;	  //在第0位显示字母E
		delay(1);
		weixuan(4);
		GPIO_DIG=~smgduan[13];	  //在第0位显示字母d
		delay(1);
		if(speed<10){								//在小于10的时候，在第3位显示按键序号数字
	  weixuan(7);
		GPIO_DIG=~smgduan[speed];	  
		delay(1);
		}
		
		if(speed>=10){		//显示速度等级0-16
		weixuan(6);
		GPIO_DIG=~smgduan[1];	  
		delay(1);
			
		weixuan(7);
		GPIO_DIG=~smgduan[speed-10];	  
		delay(1);
		}		
	}
	
		if(mode ==4){
		int duty = (0.2 + speed/20.0)*100;	
			
		weixuan(0);
		GPIO_DIG=0x5e;	  //在第0位显示字母d
		delay(1);
		weixuan(1);
		GPIO_DIG=0x3e;	  //在第0位显示字母u
		delay(1);
		weixuan(2);
		GPIO_DIG=0x78;	  //在第0位显示字母t
		delay(1);
		weixuan(3);
		GPIO_DIG=0x6e;	  //在第0位显示字母y
		delay(1);
		
		if(duty < 100&& duty > 20){	//显示占空比
		weixuan(6);
		GPIO_DIG=~smgduan[(int)(duty/10)];	  
		delay(1);
			
		weixuan(7);
		GPIO_DIG=~smgduan[(int)(duty%10)];	  
		delay(1);	
		}
		else if(duty >= 100){
		weixuan(5);
		GPIO_DIG=~smgduan[1];	  
		delay(1);
			
		weixuan(6);
		GPIO_DIG=~smgduan[0];	  
		delay(1);
			
		weixuan(7);
		GPIO_DIG=~smgduan[0];	  
		delay(1);	
		}
		else {
		weixuan(4);
		GPIO_DIG=~smgduan[5];	  //在第0位显示字母s
		delay(1);
		weixuan(5);
		GPIO_DIG=0x78;	  //在第0位显示字母t
		delay(1);
		weixuan(6);
		GPIO_DIG=0x5c;	  //在第0位显示字母o
		delay(1);
		weixuan(7);
		GPIO_DIG=0x73;	  //在第0位显示字母p
		delay(1);
		}
		
	}
		
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

void	temp_disp(){
	weixuan(0);
	GPIO_DIG=~smgduan[2];	  //在第0位显示第一位
	delayus(1);
	
	weixuan(1);
	GPIO_DIG=~smgduan[3];	  //在第0位显示第一位
	delayus(1);
	
		weixuan(3);
	GPIO_DIG=0xb9;	  //在第0位显示第一位
	delayus(1);
	}

	void DigDisplay()
{
	unsigned char i;
	for(i=0;i<6;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=1;LSB=1;LSC=1; break;//显示第0位
			case(1):
				LSA=0;LSB=1;LSC=1; break;//显示第1位
			case(2):
				LSA=1;LSB=0;LSC=1; break;//显示第2位
			case(3):
				LSA=0;LSB=0;LSC=1; break;//显示第3位
			case(4):
				LSA=1;LSB=1;LSC=0; break;//显示第4位
			case(5):
				LSA=0;LSB=1;LSC=0; break;//显示第5位
		}
		P0=DisplayData[i];//发送数据
		delayus(10); //间隔一段时间扫描	
		//P0=0x00;//消隐
	}		
}
