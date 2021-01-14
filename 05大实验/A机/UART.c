#include "UART.h"
extern unsigned char mech_step;
extern unsigned char recv_commond;
extern unsigned char safeState;

char putchar(char c){	//��д��putchar��������include stdio.h��Ϳ���ʹ��printf��
	SBUF = c;
	while(!TI);//Here���ȴ������־λ��ע��������������
	TI = 0;
	return c;
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