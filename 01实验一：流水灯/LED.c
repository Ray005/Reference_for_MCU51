#include "reg52.h"
#define led P2	//LED����P2

void Delay100ms();	//����ԭ��
void delay100msx(long x);	//����ԭ�ͣ��������x��ʾ��ʱ����100ms


void main(){						//������
	int i;//��������
	led=~0x01;
	P0 = 0;		//�ر����ֵ�����ܣ���ֹ��ʾ���󣨷Ǳ�Ҫ��
	delay100msx(5); //��ʱ
	while(1)
	{	
		for(i=0;i<8;i++)
		{
			P2=~(0x07<<i);	 //��1����iλ��Ȼ�󽫽����ֵ��P2��
			delay100msx(5); //��Լ��ʱ500ms
		}
}
}


void Delay100ms()		//@11.0592MHz
{//���������STC-ISP��������ҵ�
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void delay100msx(long x){
int i;//��������
for(i = 0; i < x ; i++){
	Delay100ms();
}
}