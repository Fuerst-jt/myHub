#ifndef __MAIN_H
#define __MAIN_H

#include	"config.h"

sbit LED = P5^5;

#define LED_ON 0
#define LED_OFF 1
#define	Cal_MODE 	0	//每次测量只读1次ADC. 分辨率0.01V
//	#define	Cal_MODE 	1	//每次测量连续读16次ADC 再平均计算. 分辨率0.01V

#endif