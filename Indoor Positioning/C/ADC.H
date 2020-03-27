#ifndef __ADC_H
#define __ADC_H

#include	"config.h"
#include  "intrins.h"
#define P1n_pure_input(bitn)		P1M1 |=  (bitn),	P1M0 &= ~(bitn)

u16	Get_ADC10bitResult(u8 channel);	//channel = 0~7


#endif