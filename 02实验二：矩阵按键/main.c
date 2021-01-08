

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

#define GPIO_DIG P0
#define GPIO_KEY P1

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit LED_const = P2^1;


u8 KeyValue;	//������Ŷ�ȡ���ļ�ֵ


u8 code smgduan[17]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//��ʾ0~F��ֵ


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
	if(GPIO_KEY!=0x0f)//��ȡ�����Ƿ���
	{
		delay(1);//��ʱ10ms��������
		if(GPIO_KEY!=0x0f)//�ٴμ������Ƿ���
		{	
			//������
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;//�õ�����һ�У��õ�����ƫ�������ڵõ��к󣬼������ƫ��������
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			//������
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;	//�ڵ�һ�У�����ƫ�ñ���
				case(0Xb0):	KeyValue=KeyValue+4;break;//�ڵڶ��У�4��ʼ������ƫ��
				case(0Xd0): KeyValue=KeyValue+8;break;//�ڵ����У�8��ʼ������ƫ��
				case(0Xe0):	KeyValue=KeyValue+12;break;//�ڵ����У�12��ʼ������ƫ��
			}
			
		}
	}
	/*while((a<50)&&(GPIO_KEY!=0xf0))	 //��ⰴ�����ּ��
	{
		delay(10);
		a++;
	}*/
	return KeyValue;
}
void weixuan(int i){
switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ
			case(1):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(2):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(3):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(4):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ 
			case(5):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ 
			case(6):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ 
			case(7):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ	
		}
	}

void main()
{	
	int k;
	int a = 0;
	//LED_const = 1;
	while(1)
	{	
		k = KeyDown();		   //�����жϺ���
		
		weixuan(0);
		GPIO_DIG=0x6d;	  //�ڵ�0λ��ʾ��ĸS
		delay(2);
		weixuan(1);
		GPIO_DIG=0x73;	  //�ڵ�0λ��ʾ��ĸP
		delay(2);
		weixuan(2);
		GPIO_DIG=0x79;	  //�ڵ�0λ��ʾ��ĸE
		delay(2);
		weixuan(3);
		GPIO_DIG=0x79;	  //�ڵ�0λ��ʾ��ĸE
		delay(2);
		weixuan(4);
		GPIO_DIG=~smgduan[13];	  //�ڵ�0λ��ʾ��ĸd
		delay(2);
		if(k<10){								//��С��10��ʱ���ڵ�3λ��ʾ�����������
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

			P2 = P2 & 0x1C | 0x00;        //Ϩ��LED  
   		delayus((k)*5);

   		P2 = P2 & 0x1C | 0xE3;        //����LED
  	  delayus((16-k)*5);
	}		
}