#include "uart.h"

void sendByte( char c){
	SBUF = c;
	while(!TI);//Here，清除标志位，注意这里是阻塞的
	TI = 0;
}

char putchar(char c){
	sendByte(c);
	return c;
}