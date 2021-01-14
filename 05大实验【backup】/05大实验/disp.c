#include "disp.h"
#include "delay.h"


extern unsigned char DisplayData[5];
unsigned char code smgduan[17]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//��ʾ0~F��ֵ

void display_smg(){
		////��ʾ�����
		if(mode ==1){
		weixuan(0);
		GPIO_DIG=0x6d;	  //�ڵ�0λ��ʾ��ĸS
		delay(1);
		weixuan(1);
		GPIO_DIG=0x73;	  //�ڵ�0λ��ʾ��ĸP
		delay(1);
		weixuan(2);
		GPIO_DIG=0x79;	  //�ڵ�0λ��ʾ��ĸE
		delay(1);
		weixuan(3);
		GPIO_DIG=0x79;	  //�ڵ�0λ��ʾ��ĸE
		delay(1);
		weixuan(4);
		GPIO_DIG=~smgduan[13];	  //�ڵ�0λ��ʾ��ĸd
		delay(1);
		if(speed<10){								//��С��10��ʱ���ڵ�3λ��ʾ�����������
	  weixuan(7);
		GPIO_DIG=~smgduan[speed];	  
		delay(1);
		}
		
		if(speed>=10){		//��ʾ�ٶȵȼ�0-16
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
		GPIO_DIG=0x5e;	  //�ڵ�0λ��ʾ��ĸd
		delay(1);
		weixuan(1);
		GPIO_DIG=0x3e;	  //�ڵ�0λ��ʾ��ĸu
		delay(1);
		weixuan(2);
		GPIO_DIG=0x78;	  //�ڵ�0λ��ʾ��ĸt
		delay(1);
		weixuan(3);
		GPIO_DIG=0x6e;	  //�ڵ�0λ��ʾ��ĸy
		delay(1);
		
		if(duty < 100&& duty > 20){	//��ʾռ�ձ�
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
		GPIO_DIG=~smgduan[5];	  //�ڵ�0λ��ʾ��ĸs
		delay(1);
		weixuan(5);
		GPIO_DIG=0x78;	  //�ڵ�0λ��ʾ��ĸt
		delay(1);
		weixuan(6);
		GPIO_DIG=0x5c;	  //�ڵ�0λ��ʾ��ĸo
		delay(1);
		weixuan(7);
		GPIO_DIG=0x73;	  //�ڵ�0λ��ʾ��ĸp
		delay(1);
		}
		
	}
		
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

void	temp_disp(){
	weixuan(0);
	GPIO_DIG=~smgduan[2];	  //�ڵ�0λ��ʾ��һλ
	delayus(1);
	
	weixuan(1);
	GPIO_DIG=~smgduan[3];	  //�ڵ�0λ��ʾ��һλ
	delayus(1);
	
		weixuan(3);
	GPIO_DIG=0xb9;	  //�ڵ�0λ��ʾ��һλ
	delayus(1);
	}

	void DigDisplay()
{
	unsigned char i;
	for(i=0;i<6;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��0λ
			case(1):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��1λ
			case(2):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��2λ
			case(3):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��3λ
			case(4):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��4λ
			case(5):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��5λ
		}
		P0=DisplayData[i];//��������
		delayus(10); //���һ��ʱ��ɨ��	
		//P0=0x00;//����
	}		
}
