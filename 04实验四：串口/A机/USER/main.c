//A����
#include "reg51.h"
#include "stdio.h"
#include "intrins.h"
#define LocalHost 0x41
//#include "uart.h"

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

//--����ʹ�õ�IO��--//
sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;


u8 ledduan[]={0x00,0x06,0x38,0xC8,0x68,0x18,0x06,0x00};/*"A",0*/
u8 ledwei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};	//�����ڶ�̬����ܵ�λѡ
unsigned char mech_step = 1;
unsigned char recv_commond = 0;

void delay(long x){
	int i;
	for(i = 0; i < x ; i++){
	unsigned char i, j;
	i = 2;
	j = 199;
	do
	{		while (--j);
	} while (--i);
	} 
}

void UartInit(void)		//4800bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	//AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
	//AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	//stc�в������AUXR�Ĵ�����û�еĻ���Ĭ��ѡ��ʱ��1��12Tģʽ����ɾȥ��һ�м���
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFA;		//�趨��ʱ��ֵ
	TH1 = 0xFA;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	ES = 1;
	EA = 1;
	TR1 = 1;		//������ʱ��1
}

char putchar(char c){	//��д��putchar��������include stdio.h��Ϳ���ʹ��printf��
	SBUF = c;
	while(!TI);//Here���ȴ������־λ��ע��������������
	TI = 0;
	return c;
}


void delay2(u16 i)
{
	while(i--);	
}

void LED1(u8 dat1)
{
	P0=dat1;
}
/*******************************************************************************
* �� �� ��         : Hc595SendByte(u8 dat1,u8 dat2)
* ��������		   : ͨ��595����2���ֽڵ�����
* ��    ��         : dat1����2��595�����ֵ
*                  * dat2: ��1��595�����ֵ
* ��    ��         : ��
*******************************************************************************/
void Hc595SendByte(u8 dat)
{
	u8 a;

	SRCLK = 1;
	RCLK = 1;

	for(a=0;a<8;a++)		 //����8λ��
	{
		SER = dat >> 7;		 //�����λ��ʼ����
		dat <<= 1;

		SRCLK = 0;			 //����ʱ��
		_nop_();
		_nop_();
		SRCLK = 1;	
	}
	RCLK = 0;
	_nop_();
	_nop_();
	RCLK = 1;
}


void main(){
	int i;
	UartInit();
	//printf("Haojie");
		   
	while(1){
		for(i=0;i<8;i++)
	   {
	   		Hc595SendByte(ledduan[i]);
			 LED1(ledwei[i]);			
	   }
		if(recv_commond == '1'){
		P2 = 0x00;
		}
		else if(recv_commond == '0'){
		P2 = 0xFF;
		}

		
	}
}

void uart_ISR() interrupt 4
{
	unsigned char recv_data;
	if(RI){
		RI = 0;
		recv_data = SBUF;
		switch(mech_step){
			case 1:{
			if(recv_data == '^'){
			mech_step = 2;
			}
			}break;
			case 2:{
			if(recv_data == LocalHost){
			mech_step = 3;	
			}
			else {
			mech_step = 1;
			}
			}break;
			case 3:{
			recv_commond = recv_data;
			mech_step = 1;	//�������
				//if(recv_commond == '1')
					{
				printf("��0x41���ӻ�AӦ��\r\n");
				}
			}break;
			default :break;
		}

	}
}	