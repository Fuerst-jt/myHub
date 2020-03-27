/******************************************************************************
	作者：神秘藏宝室
	店铺：ILoveMCU.taobao.com
	功能：
		LCD1602液晶显示
		若液晶看不清楚字，请旋转对比度调节的电位器到字清晰为止
******************************************************************************/
#include "main.h"
#include "delay.h"
#include "lcd1602.h"
#include "led.h"
#include "adc.h"

/*************	功能说明	**************

本程序演示LED闪烁  


******************************************/

/*************	本地常量声明	**************/


/*************	本地变量声明	**************/
u8	i;
u16	j;
u16	Bandgap;

/*************	本地函数声明	**************/



/*************  外部函数和变量声明 *****************/



/******************** IO配置函数 **************************/
void	GPIO_config(void)
{
	P5M0 &= ~(1<<5);		//设置P5.5为准双向口
	P5M1 &= ~(1<<5);
}






/******************** 主函数 **************************/
void main(void)
{
	init();
	GPIO_config();

	Init_LCD1602();
	LCD1602_write_com(0x80);		//指针指向第1行第0个位置
	LCD1602_write_word("Welcome to use!");

	LCD1602_write_com(0x80+0x40);	//指针指向第2行第0个位置
	LCD1602_write_word("HelloWorld!");

	delay_ms(200);
	
	while(1)
	{
		
		#if (Cal_MODE == 0)
			//=================== 只读1次ADC, 10bit ADC. 分辨率0.01V ===============================
				P1ASF = 0;
				Get_ADC10bitResult(0);	//改变P1ASF后先读一次并丢弃结果, 让内部的采样电容的电压等于输入值.
				Bandgap = Get_ADC10bitResult(0);	//读内部基准ADC, P1ASF=0, 读0通道
				P1ASF = 1<<3;
				j = Get_ADC10bitResult(3);	//读外部电压ADC
				j = (u16)((u32)j * 123 / Bandgap);	//计算外部电压, Bandgap为1.23V, 测电压分辨率0.01V
			#endif
			//==========================================================================

			//===== 连续读16次ADC 再平均计算. 分辨率0.01V =========
			#if (Cal_MODE == 1)
				P1ASF = 0;
				Get_ADC10bitResult(0);	//改变P1ASF后先读一次并丢弃结果, 让内部的采样电容的电压等于输入值.
				for(j=0, i=0; i<16; i++)
				{
					j += Get_ADC10bitResult(0);	//读内部基准ADC, P1ASF=0, 读0通道
				}
				Bandgap = j >> 4;	//16次平均
				P1ASF = ADC_P13;
				for(j=0, i=0; i<16; i++)
				{
					j += Get_ADC10bitResult(3);	//读外部电压ADC
				}
				j = j >> 4;	//16次平均
				j = (u16)((u32)j * 123 / Bandgap);	//计算外部电压, Bandgap为1.23V, 测电压分辨率0.01V
			#endif

		LCD1602_write_com(0x80+0x40+13);  //指针指向第2行第13个位置
		LCD1602_write_data(j/100 + 0x30);	//显示百位
		LCD1602_write_data(j%100/10 + 0x30);//显示十位
		LCD1602_write_data(j%10 + 0x30);	//显示个位
		
	
	}
}

void Led_flash() interrupt 1
{
	TH0 = (65536 - 10000) / 256;
	TL0 = (65535 - 10000) % 256;
	temp = _crol_(temp,1);
	if(temp == 0x08)
		temp = 0x01;
	P1 = temp;
	LED = ~LED;
}

void init()
{
	P0M1 = 0;	P0M0 = 0;	//设置为准双向口
	P1M1 = 0;	P1M0 = 0;	//设置为准双向口
	P2M1 = 0;	P2M0 = 0;	//设置为准双向口
	P3M1 = 0;	P3M0 = 0;	//设置为准双向口
	P4M1 = 0;	P4M0 = 0;	//设置为准双向口
	P5M1 = 0;	P5M0 = 0;	//设置为准双向口
	P6M1 = 0;	P6M0 = 0;	//设置为准双向口
	P7M1 = 0;	P7M0 = 0;	//设置为准双向口
	P1M1 |= (1<<3);		// 把ADC口设置为高阻输入
	P1M0 &= ~(1<<3);
	P1ASF = (1<<3);		//P1.3做ADC
	ADC_CONTR = 0xE0;	//90T, ADC power on
	
	AUXR = 0x00;
	TMOD = 0x01;
	TH0 = (65536 - 10000) / 256;
	TL0 = (65535 - 10000) % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	temp = 0x01;
	LED = LED_OFF;
}




