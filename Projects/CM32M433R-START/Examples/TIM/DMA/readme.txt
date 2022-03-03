1、功能说明

	1、TIM1 CH3 CH3N输出互补信号，每6个周期改变一次占空比。

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M433R-START

3、使用说明

	系统配置；
		1、时钟源：
		            HSE=8M,AHB=8M,APB1=8M,APB2=8M,TIM3 CLK=8M
		2、端口配置：
					PA10选择为TIM1 CH3输出
					PB15选择为TIM1 CH3N输出
	    3、TIM：
		            TIM1 CH3 CH3N互补输出，重复计数6次产生一个更新事件触发一次DMA传输。
		4、DMA：
		            DMA1_CH5通道回环模式搬运3个半字SRC_Buffer[3]变量到TIM1 CC3寄存器
	使用方法：
		1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1 CH3 CH3N的波形
	    2、TIM1的6个周期改变一次CH3 CH3N的占空比，循环改变。
		3、CH3和CH3N输出频率为17.58KHz，互补进行输出，CH3占空比变化50%->37.5%->25%。

4、注意事项
	无