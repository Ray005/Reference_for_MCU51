#include "reg52.h"
#define led P2	//LED接在P2

void Delay100ms();	//函数原型
void delay100msx(long x);	//函数原型：输入参数x表示延时几个100ms


void main(){						//主函数
	int i;//计数变量
	led=~0x01;
	P0 = 0;		//关闭数字的数码管，防止显示错误（非必要）
	delay100msx(5); //延时
	while(1)
	{	
		for(i=0;i<8;i++)
		{
			P2=~(0x07<<i);	 //将1右移i位，然后将结果赋值到P2口
			delay100msx(5); //大约延时500ms
		}
}
}


void Delay100ms()		//@11.0592MHz
{//这个函数在STC-ISP里面可以找到
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void delay100msx(long x){
int i;//计数变量
for(i = 0; i < x ; i++){
	Delay100ms();
}
}