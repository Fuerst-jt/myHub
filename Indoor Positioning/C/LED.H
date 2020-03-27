#ifndef __LED_H_
#define __LED_H_

#include"intrins.h"

sbit LED1 = P3^0;
sbit LED2 = P3^1;
sbit LED3 = P3^2;

unsigned char temp;

void init();
void Led_flash();

#endif