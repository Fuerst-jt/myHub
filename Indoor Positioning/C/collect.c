#include "collect.h"

u8	i;
u16	j;	
u16	Bandgap;

//=================== ֻ��1��ADC, 10bit ADC. �ֱ���0.01V ===============================
#if (Cal_MODE == 0)
	u16 coll_data_1()
	{
		P1ASF = 0;
		Get_ADC10bitResult(0);	//�ı�P1ASF���ȶ�һ�β��������, ���ڲ��Ĳ������ݵĵ�ѹ��������ֵ.
		Bandgap = Get_ADC10bitResult(0);	//���ڲ���׼ADC, P1ASF=0, ��0ͨ��
		P1ASF = 1<<3;
		j = Get_ADC10bitResult(3);	//���ⲿ��ѹADC
		j = (u16)((u32)j * 123 / Bandgap);	//�����ⲿ��ѹ, BandgapΪ1.23V, ���ѹ�ֱ���0.01V
		return j;
	}
#endif
//==========================================================================

//===== ������16��ADC ��ƽ������. �ֱ���0.01V =========
#if (Cal_MODE == 1)
	u16 coll_data_2()
	{
		P1ASF = 0;
		Get_ADC10bitResult(0);	//�ı�P1ASF���ȶ�һ�β��������, ���ڲ��Ĳ������ݵĵ�ѹ��������ֵ.
		for(j=0, i=0; i<16; i++)
		{
			j += Get_ADC10bitResult(0);	//���ڲ���׼ADC, P1ASF=0, ��0ͨ��
		}
		Bandgap = j >> 4;	//16��ƽ��
		P1ASF = ADC_P13;
		for(j=0, i=0; i<16; i++)
		{
			j += Get_ADC10bitResult(3);	//���ⲿ��ѹADC
		}
		j = j >> 4;	//16��ƽ��
		j = (u16)((u32)j * 123 / Bandgap);	//�����ⲿ��ѹ, BandgapΪ1.23V, ���ѹ�ֱ���0.01V
		return j;
	}
#endif
			