#include "temp.h"
#include "safe.h"
#include "delay.h"
unsigned char get_safe_sta(){

	if((Ds18b20ReadTemp_regular()*0.0625*100+0.5)/100 >= 29){
		delay(100);
		if((Ds18b20ReadTemp_regular()*0.0625*100+0.5)/100 >= 29){
		return 1;
		}
	}
	else{
	return 0;
	}
}