#include "reg52.h"

#define GPIO_DIG P0
#define GPIO_KEY P1
extern unsigned char mode;
extern unsigned char speed;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit LED_const = P2^1;
void display_smg();
void weixuan(int i);