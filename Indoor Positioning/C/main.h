#ifndef __MAIN_H
#define __MAIN_H

#include	"config.h"

sbit LED = P5^5;

#define LED_ON 0
#define LED_OFF 1
#define	Cal_MODE 	0	//ÿ�β���ֻ��1��ADC. �ֱ���0.01V
//	#define	Cal_MODE 	1	//ÿ�β���������16��ADC ��ƽ������. �ֱ���0.01V

#endif