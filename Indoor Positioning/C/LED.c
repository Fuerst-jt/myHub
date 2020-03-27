#include"LED.h"

void main ()
{
	init();
	while(1);	
}

void Led_flash() interrupt 1
{
	TH0 = (65536 - 10000) / 256;
	TL0 = (65535 - 10000) % 256;
	temp = _crol_(temp,1);
	if(temp == 0x08)
		temp = 0x01;
	P1 = temp;
}

void init()
{
	TMOD = 0x01;
	TH0 = (65536 - 10000) / 256;
	TL0 = (65535 - 10000) % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	temp = 0x01;
}