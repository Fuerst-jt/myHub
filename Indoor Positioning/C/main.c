/******************************************************************************
	作者：神秘藏宝室
	店铺：ILoveMCU.taobao.com
	功能：
		LCD1602液晶显示
		若液晶看不清楚字，请旋转对比度调节的电位器到字清晰为止
******************************************************************************/
#include "main.h"


/*************	功能说明	**************

本程序演示LED闪烁  


******************************************/

/*************	本地常量声明	******		1									2							3						4								5						6								7							8							9							10						11						12					*/
u16 code fingerprint[10][12][3] =  {{{183,148,435},{207,186,435},{211,208,425},{220,234,406},{230,260,375},{235,281,353},{240,316,315},{230,347,275},{217,360,242},{199,375,210},{195,382,178},{189,377,172}},
																		{{196,153,435},{210,173,434},{218,198,432},{235,225,410},{240,253,383},{252,280,350},{252,311,310},{244,343,273},{231,366,245},{216,387,212},{208,395,180},{200,385,175}},
																		{{220,155,435},{234,174,434},{250,198,431},{264,224,412},{275,253,386},{280,276,351},{278,308,311},{268,338,273},{257,364,241},{252,380,215},{237,392,188},{219,381,172}},
																		{{232,152,430},{258,173,428},{276,196,417},{290,222,399},{306,250,373},{313,272,336},{307,300,303},{292,328,268},{284,350,236},{277,370,217},{259,380,200},{255,368,183}},
																	  {{257,150,398},{278,168,403},{300,192,393},{322,213,380},{338,238,353},{343,262,320},{340,284,288},{323,308,258},{318,330,230},{304,347,206},{275,362,182},{256,355,168}},
																	  {{282,146,368},{309,162,379},{336,183,368},{350,199,350},{365,227,328},{373,248,300},{367,268,268},{357,289,246},{347,306,218},{332,320,204},{305,334,182},{277,324,165}},
																	  {{296,144,340},{325,158,345},{356,180,338},{374,193,325},{388,218,296},{395,236,277},{390,254,257},{382,269,238},{367,282,212},{352,292,198},{328,296,178},{302,288,163}},
																	  {{310,136,302},{336,144,305},{365,162,303},{389,179,293},{405,220,272},{415,214,254},{409,233,236},{400,249,218},{382,260,204},{363,265,189},{342,266,171},{313,261,154}},
																	  {{306,128,271},{336,138,276},{362,154,274},{383,164,268},{406,185,258},{410,198,242},{410,215,221},{402,227,203},{383,238,188},{364,247,170},{338,242,152},{304,237,140}},
																	  {{296,118,254},{323,124,255},{349,142,254},{369,152,245},{387,162,228},{397,175,210},{395,194,200},{383,203,188},{370,217,170},{350,222,155},{325,223,142},{298,221,140}}};
	



/*************	本地变量声明	**************/
	u16 process_data[3];
	u8 coordinate[2];
	u16	RSS_data[3][10];
	u8 flag,m,n,x,y,z;
	u16 num,Difference,num1[3];


/*************	本地函数声明	**************/
void init()
{
	AUXR = 0x00;
	TMOD = 0x01;
	TH0 = (65536 - 2400) / 256;
	TL0 = (65535 - 2400) % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	temp = 0x01;
	m = 0;
	n = 0;
	flag = 0;
}



/*************  外部函数和变量声明 *****************/



/******************** IO配置函数 **************************/
void	GPIO_config(void)
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
}






/******************** 主函数 **************************/
void main(void)
{
	init();
	GPIO_config();
	Init_LCD1602();
	


	while(1)
	{
		if(flag)
		{
			flag = 0;
			for(y = 0; y < 3; y++)
				{
					for(x = 0; x < 10; x++)
					{
						process_data[y] += RSS_data[y][x];
					}
					process_data[y] /= 10;
				}
		}

		
		num = 25000;
		for(x = 0; x< 10; x++)
		{
			for(y = 0; y< 12; y++)
			{
				for(z = 0; z< 3; z++)
				{
					num1[z] = abs(fingerprint[x][y][z] - process_data[z]);
					Difference += num1[z];
				}
				if(num > Difference)
				{
					num = Difference;
					coordinate[0]=x+1;
					coordinate[1]=y+1;
				}
				Difference = 0;
			}
		}
		
		for(x = 0 ; x < 3 ; x++)
		{
			LCD1602_write_com(0x80+0x40+(5*x));  //指针指向第2行
			LCD1602_write_data((process_data[x])/100 + 0x30);	//显示百位
			LCD1602_write_data((process_data[x])%100/10 + 0x30);//显示十位
			LCD1602_write_data((process_data[x])%10 + 0x30);	//显示个位
		}
		for(x = 0 ; x < 2 ; x++)
		{
			LCD1602_write_com(0x80+(5*x));  //指针指向第1行
			LCD1602_write_data((coordinate[x])/10 + 0x30);//显示十位
			LCD1602_write_data((coordinate[x])%10 + 0x30);	//显示个位
		}
		LCD1602_write_com(0x80+10);  //指针指向第1行
		LCD1602_write_data(num/100 + 0x30);	//显示百位
		LCD1602_write_data(num%100/10 + 0x30);//显示十位
		LCD1602_write_data(num%10 + 0x30);	//显示个位
		delay_ms(1000);
	}
}

void Led_flash() interrupt 1
{
	TH0 = (65536 - 2400) / 256;		//128Hz
	TL0 = (65535 - 2400) % 256;
	temp = _crol_(temp,1);
	if(temp == 0x08)
		temp = 0x01;
	P0 = temp;
	
	Delay1ms();

	RSS_data[m][n] = coll_data_1();
	m++;
	if(m >= 3)
	{
		n++;
		m = 0;
	}
	if(n >= 10)
	{
		flag = 1;
		n = 0;
	}
}




