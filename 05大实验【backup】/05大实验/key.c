#include "reg52.h"
#include "key.h"
#include "delay.h"

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



