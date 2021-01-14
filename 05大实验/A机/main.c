#include "reg52.h"
#include "disp.h"
#include "delay.h"
#include "key.h"
#include "pwm.h"
#include "UART.h"
#include "temp.h"

unsigned char KeyValue;	//用来存放读取到的键值
unsigned char TL0_ON ,TH0_ON,TL0_OFF,TH0_OFF;//u16
unsigned char key_val;
unsigned char speed = 1,speed_old;
unsigned int  counter = 0xFFF0,counter_OFF = 0xFFF0;
unsigned char mode = 1;
unsigned char mech_step = 1;
unsigned char recv_commond = 0;
unsigned char safeState = 0;
int tempre;
int cc = 5;
void main(){
	Timer0Init();
	UartInit();
	printf("ON");
	while(1){
				//printf("【%f】\r\n",(int)5);
		if(!cc--){
		tempre = Ds18b20ReadTemp()/16;
			//printf("【%d】\r\n",tempre);
		if(tempre>=29){
			safeState = 1;
			cc = 50;
		}
		else 
		{
		safeState = 0;
						cc = 50;
		}
		}

		//printf("%d\r\n",Ds18b20ReadTemp()/16);
		if(recv_commond-48>=1 && recv_commond-48 <=16){//串口调速
		speed = recv_commond-48;
		}
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
		speed_old = speed;
		}
		display_smg();
	}
}