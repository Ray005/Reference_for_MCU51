#include "reg52.h"
#include "disp.h"
#include "delay.h"
#include "key.h"
#include "pwm.h"
#include "UART.h"
#include "safe.h"
#include "temp.h"

sbit beep=P1^5;	 

unsigned char KeyValue;	//用来存放读取到的键值
unsigned char TL0_ON ,TH0_ON,TL0_OFF,TH0_OFF;//u16
unsigned char key_val;
unsigned char speed = 1,speed_old;
unsigned int  counter = 0xFFF0,counter_OFF = 0xFFF0;
unsigned char mode = 1;
unsigned char mech_step = 1;
unsigned char recv_commond = 0;	//
unsigned char safeState = 0;
unsigned char DisplayData[10];
unsigned char beep_flag = 0;
int aa=0;

void main(){
	static unsigned int time_c = 1000; 
	delay(1000);
	Timer0Init();
	UartInit();
	printf("ON");
	while(1){
	printf("【%d】",(int)aa++);
	}
	while(1){
	if(recv_commond>=1 && recv_commond <=16){//串口调速
		speed = recv_commond;
		printf("【%d】",aa++);
	}
	if(!time_c--){	
	safeState = get_safe_sta();	//获取安全状态
		time_c = 1000;
	}
	
switch(safeState){
	case 0:{//正常模式
				
	recv_commond = 0;
	key_val = keypros();	//按键调速
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
		speed_old = speed;
		}
		display_smg();
	}break;
	case 1:{//告警模式
		float fp;
		static unsigned int cc =0;
		if(!beep_flag){
		beep_flag = 1;		
		datapros(fp = Ds18b20ReadTemp());
		}
		if(!cc--){
		datapros(fp = Ds18b20ReadTemp());
		printf("【0x41】OVERTEMP %.2f\r\n",(fp*0.0625*100+0.5)/100);
		cc = 100;
		}
		DigDisplay();
	}break;
	default:{}break;
	
	}
	}
}