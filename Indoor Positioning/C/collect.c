#include "collect.h"



//=================== 只读1次ADC, 10bit ADC. 分辨率0.01V ===============================

	u16 coll_data_1()
	{
		u16	j;	
		u16	Bandgap;
		P1ASF = 0;
		Get_ADC10bitResult(0);	//改变P1ASF后先读一次并丢弃结果, 让内部的采样电容的电压等于输入值.
		Bandgap = Get_ADC10bitResult(0);	//读内部基准ADC, P1ASF=0, 读0通道
		P1ASF = 1<<3;
		j = Get_ADC10bitResult(3);	//读外部电压ADC
		j = (u16)((u32)j * 123 / Bandgap);	//计算外部电压, Bandgap为1.23V, 测电压分辨率0.01V
		return j;
	}

//==========================================================================


			