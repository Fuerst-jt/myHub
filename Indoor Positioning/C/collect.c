#include "collect.h"



//=================== ֻ��1��ADC, 10bit ADC. �ֱ���0.01V ===============================

	u16 coll_data_1()
	{
		u16	j;	
		u16	Bandgap;
		P1ASF = 0;
		Get_ADC10bitResult(0);	//�ı�P1ASF���ȶ�һ�β��������, ���ڲ��Ĳ������ݵĵ�ѹ��������ֵ.
		Bandgap = Get_ADC10bitResult(0);	//���ڲ���׼ADC, P1ASF=0, ��0ͨ��
		P1ASF = 1<<3;
		j = Get_ADC10bitResult(3);	//���ⲿ��ѹADC
		j = (u16)((u32)j * 123 / Bandgap);	//�����ⲿ��ѹ, BandgapΪ1.23V, ���ѹ�ֱ���0.01V
		return j;
	}

//==========================================================================


			