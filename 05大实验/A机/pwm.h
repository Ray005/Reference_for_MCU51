#include "reg52.h"
sbit moto_pos = P1^0;
extern unsigned char speed;
extern unsigned char TL0_ON ,TH0_ON,TL0_OFF,TH0_OFF;//u16
void moto_turn(int turn);
unsigned int counterCul(float dutycycle);
void Timer0Init();