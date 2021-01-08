#include "reg52.h"
#define GPIO_DIG P0
#define GPIO_KEY P1

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit LED_const = P2^1;


unsigned char KeyValue;	//������Ŷ�ȡ���ļ�ֵ


unsigned char code smgduan[17]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//��ʾ0~F��ֵ


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
	if(k1==0)		  //��ⰴ��K1�Ƿ���
	{	//k1 = 1;
		delay(10);   //�������� һ���Լ10ms
		if(k1==0)	 //�ٴ��жϰ����Ƿ���
		{	while(!k1);
			return 1;	  
		}
		
	}
		
	
		if(k2==0)		  //��ⰴ��K1�Ƿ���
	{	//k2 = 1;
		delay(10);   //�������� һ���Լ10ms
		if(k2==0)	 //�ٴ��жϰ����Ƿ���
		{	
			while(!k2)delay(10);
			return 2;	  //led״̬ȡ��
		}
	}
	
	
		if(k3==0)		  //��ⰴ��K1�Ƿ���
	{	
		delay(10);   //�������� һ���Լ10ms
		if(k3==0)	 //�ٴ��жϰ����Ƿ���
		{
			while(!k3);
			return 3;	  //led״̬ȡ��
		}
		
	}
	
	
		if(k4==0)		  //��ⰴ��K1�Ƿ���
	{	
		delay(10);   //�������� һ���Լ10ms
		if(k4==0)	 //�ٴ��жϰ����Ƿ���
		{
			while(!k4);
			return 4;	  //led״̬ȡ��
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
	return 65535-(int)(1000*dutycycle*11.0592/12.0);//pwm����Ϊ1000us��1ms��1kHz��
}

void Timer0Init()
{
	TMOD|=0X01;//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1������TR0��������

	TH0=0XCD;	//����ʱ������ֵ����ʱ1ms
	TL0=0XD4;	
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	TR0=1;//�򿪶�ʱ��			
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
		////��ʾ�����
		if(mode ==1){
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
		if(speed<10){								//��С��10��ʱ���ڵ�3λ��ʾ�����������
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
		GPIO_DIG=0x5e;	  //�ڵ�0λ��ʾ��ĸd
		delay(2);
		weixuan(1);
		GPIO_DIG=0x3e;	  //�ڵ�0λ��ʾ��ĸu
		delay(2);
		weixuan(2);
		GPIO_DIG=0x78;	  //�ڵ�0λ��ʾ��ĸt
		delay(2);
		weixuan(3);
		GPIO_DIG=0x6e;	  //�ڵ�0λ��ʾ��ĸy
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
		GPIO_DIG=~smgduan[5];	  //�ڵ�0λ��ʾ��ĸs
		delay(2);
		weixuan(5);
		GPIO_DIG=0x78;	  //�ڵ�0λ��ʾ��ĸt
		delay(2);
		weixuan(6);
		GPIO_DIG=0x5c;	  //�ڵ�0λ��ʾ��ĸo
		delay(2);
		weixuan(7);
		GPIO_DIG=0x73;	  //�ڵ�0λ��ʾ��ĸp
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
        moto_pos = 1;        //���øߵ�ƽ����ʱ��
        TH0 = TH0_ON;
        TL0 = TL0_ON;
    }
    else
    {		P2 = P2 & 0x1C | 0xE3;
        moto_pos = 0;        //���õ͵�ƽ����ʱ��         
			TH0 = TH0_OFF;
      TL0 = TL0_OFF;
    }
}
	
