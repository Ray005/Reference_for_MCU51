#include "reg52.h"
#include "key.h"
#include "delay.h"

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



