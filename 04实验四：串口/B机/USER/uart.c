#include "uart.h"

void sendByte( char c){
	SBUF = c;
	while(!TI);//Here�������־λ��ע��������������
	TI = 0;
}

char putchar(char c){
	sendByte(c);
	return c;
}