1、功能说明

	1、外部信号通过CH2门控TIM1 CH1的输出
	2、TIM1通过内部触发门控TIM3 CH1的输出
	3、TIM3通过内部触发门控TIM4 CH1的输出

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	CM32M4xxR_LQFP128_STB

3、使用说明

	系统配置；
		1、时钟源：
		            HSE=8M,AHB=8M,APB1=8M,APB2=8M,TIM1/TIM3/TIM4 CLK=8M
		2、端口配置：
					PA8选择为TIM1 CH1输出
					PA9选择为TIM1 CH2输入
					PA6选择为TIM3 CH1输出
					PB6选择为TIM4 CH1输出
	    3、TIM：
		            TIM1主从模式，外部信号通过 CH2 门控TIM1的CH1输出；
					TIM3主从模式，TIM1通过内部触发门控TIM3的CH1输出；
					TIM4从模式，TIM3通过内部触发门控TIM4的CH1输出。
	使用方法：
		1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1 CH1,TIM3 CH1,TIM4 CH1的波形
	    2、当TIM1 CH2（PA9）为高电平时，所有定时器开始计数，且各个定时器同步，周期为27Khz。当低电平停止。

4、注意事项
	开发板上将PA9和3V3连接