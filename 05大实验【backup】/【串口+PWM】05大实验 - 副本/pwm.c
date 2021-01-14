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
	