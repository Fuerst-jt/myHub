#include<reg52.h>
#include<intrins.h>

sbit LED1 = P1^0;
sbit LED2 = P1^1;
sbit LED3 = P1^2;

unsigned char temp;

void init();
void Led_flash();

void main ()
{
	init();
	while(1);	
}

void Led_flash() interrupt 1
{
	TH0 = (65536 - 1000) / 256;
	TL0 = (65535 - 1000) % 256;
	temp = _crol_(temp,1);
	if(temp == 0x08)
		temp = 0x01;
	P1 = temp;
}

void init()
{
	TMOD = 0x01;
	TH0 = (65536 - 1000) / 256;
	TL0 = (65535 - 1000) % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	temp = 0x01;
}