1、功能说明

	1、TIM2 周期门控TIM3 TIM4

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	CM32M4xxR_LQFP128_STB

3、使用说明

	系统配置；
		1、时钟源：
		            HSE=8M,AHB=8M,APB1=8M,APB2=8M,TIM2 CLK=8MHz， TIM3 CLK=31.25Khz，TIM4 CLK=31.25Khz
		2、端口配置：
					PA0选择为TIM2的CH1输出
					PA6选择为TIM3的CH1输出
					PB6选择为TIM4的CH1输出
	    3、TIM：
		            TIM2 周期触发门控TIM3 TIM4的CH1,即TIM3为10倍周期TIM2，即TIM4为5倍周期TIM2
	使用方法：
		1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM2 CH1、TIM3 CH1、TIM4 CH1的波形
	    2、TIM4周期5倍于TIM2，TIM3周期10倍于TIM2。
		3、TIM2 CH1（PA0）频率 31.25KHz，TIM3 CH1（PA6）频率3.125Khz、TIM4 CH1（PB6）频率6.25KHz

4、注意事项
	 由于PA0复用WKUP按键，测量时需要断开拨码开关4。