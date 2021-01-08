

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

#define GPIO_DIG P0
#define GPIO_KEY P1

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit LED_const = P2^1;


u8 KeyValue;	//用来存放读取到的键值


u8 code smgduan[17]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//显示0~F的值


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


u8 KeyDown(void)
{
	char a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//读取按键是否按下
	{
		delay(1);//延时10ms进行消抖
		if(GPIO_KEY!=0x0f)//再次检测键盘是否按下
		{	
			//测试列
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;//得到在哪一列，得到的列偏移量，在得到行后，加上这个偏移量即可
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			//测试行
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;	//在第一行，就是偏置本身
				case(0Xb0):	KeyValue=KeyValue+4;break;//在第二行，4开始加上列偏置
				case(0Xd0): KeyValue=KeyValue+8;break;//在第三行，8开始加上列偏置
				case(0Xe0):	KeyValue=KeyValue+12;break;//在第四行，12开始加上列偏置
			}
			
		}
	}
	/*while((a<50)&&(GPIO_KEY!=0xf0))	 //检测按键松手检测
	{
		delay(10);
		a++;
	}*/
	return KeyValue;
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

void main()
{	
	int k;
	int a = 0;
	//LED_const = 1;
	while(1)
	{	
		k = KeyDown();		   //按键判断函数
		
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
		if(k<10){								//在小于10的时候，在第3位显示按键序号数字
	  weixuan(7);
		GPIO_DIG=~smgduan[k];	  
		delay(2);
		}
		
		if(k>=10){
		weixuan(6);
		GPIO_DIG=~smgduan[1];	  
		delay(2);
			
		weixuan(7);
		GPIO_DIG=~smgduan[k-10];	  
		delay(1);
		}

			P2 = P2 & 0x1C | 0x00;        //熄灭LED  
   		delayus((k)*5);

   		P2 = P2 & 0x1C | 0xE3;        //点亮LED
  	  delayus((16-k)*5);
	}		
}