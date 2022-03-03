1、功能说明

	1、TIM3 TIM4在TIM1周期下计数，并进行PWM输出。

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	CM32M4xxR_LQFP128_STB

3、使用说明

	系统配置；
		1、时钟源：
		            HSE=8M,PLL=144M,AHB=144M,APB1=36M,APB2=72M,TIM1 CLK=72*2M（APB Prescaler！=1）=144M
		2、端口配置：
					PA6选择为TIM3的CH1输出
					PB6选择为TIM4的CH1输出
					PA8选择为TIM1的CH1输出
	    3、TIM：
		            TIM1 周期触发TIM3 TIM4的门控
					TIM1/TIM3/TIM4 从CH1输出PWM波形。TIM1为PWM2模式，TIM3/TIM4为PWM1模式。
	使用方法：
		1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1 CH1、TIM3 CH1、TIM4 CH1的波形。
	    2、程序运行后，TIM3 15倍周期TIM1，TIM4 10倍周期TIM1。
		3、TIM1 CH1输出频率31.25KHz，占空比50%
		     TIM3 CH1输出频率2.08KHz，占空比33.3%
			 TIM4 CH1输出频率3.13KHz，占空比50%

4、注意事项

	无