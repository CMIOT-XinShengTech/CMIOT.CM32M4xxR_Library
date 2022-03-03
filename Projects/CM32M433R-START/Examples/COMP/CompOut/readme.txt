1、功能说明
	1、COMP5的输出PB11受输入INP PA3和INM PB10的影响
2、使用环境
	软件开发环境：  NucleiStudio IDE for C/C++ 2021-02
	硬件环境：      CM32M433R-START
3、使用说明
	系统配置；
		1、时钟源：
		            HSE=8M,PLL=144M,AHB=144M,APB1=36M,APB2=72M,COMP CLK=36M
		2、端口配置：
		            PA3选择为模拟功能COMP INP
					PB10选择为模拟功能COMP INM
					PB11选择为模拟功能COMP OUT
					PE2选择为IO输出
					PE3选择为IO输出
		3、COMP：
		            COMP5输入PA3，PB10，输出PB11
	使用方法：
		1、编译后打开调试模式，将PE2连接到PA3，PE3连接到PB10，利用示波器或者逻辑分析仪观察PB11输出波形
	    2、当软件输出PE2电平大于PE3时，PB11输出高电平，相反时，输出低电平
4、注意事项
	无