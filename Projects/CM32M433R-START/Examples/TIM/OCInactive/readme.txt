1、功能说明

	1、TIM2 CH1 CH2 CH3 CH4 达到CC值后，对应拉低PC6 PC7 PC8 PC9的IO电平

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M433R-START


3、使用说明

	系统配置；
		1、时钟源：
		            HSE=8M,AHB=8M,APB1=8M,APB2=8M,TIM3 CLK=4M,TIM2 CLK=1KHz
		2、中断：
		            TIM2 比较中断打开
		3、端口配置：
					PC6选择为IO 输出
					PC7选择为IO 输出
					PC8选择为IO 输出
					PC9选择为IO 输出
	    4、TIM：
		            TIM2 配置好CH1 CH2 CH3 CH4的比较值，并打开比较中断
	使用方法：
		1、编译后打开调试模式，用示波器或者逻辑分析仪观察PC6 PC7 PC8 PC9的波形
	    2、定时器运进入CC1 CC2 CC3 CC4中断后,对应拉低PC6 PC7 PC8 PC9的IO。
		3、在比较输出为强制无效电平的模式下，中断依然可以产生。
		4、PC6输出1s的脉冲，PC7输出0.5s的脉冲，PC8输出0.25s的脉冲，PC9输出0.125s的脉冲。
		
4、注意事项

	无