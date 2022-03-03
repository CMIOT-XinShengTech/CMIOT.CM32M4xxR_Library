1、功能说明

	1、TIM4 CH2上升沿触发CH1输出一个单脉冲

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M433R-STAR

3、使用说明

	系统配置；
		1、时钟源：
		            HSE=8M,AHB=8M,APB1=8M,APB2=8M,TIM4 CLK=8M
		2、端口配置：
					PD12选择为TIM4的CH1输出
					PD13选择为TIM4的CH2输入
					PA3选择为IO输出
	    3、TIM：
		            TIM4 配置CH2上升沿触发CH1输出一个单脉冲
	使用方法：
		1、编译后打开调试模式，PA3连接PD13，程序运行后可以用示波器或者逻辑分析仪观察TIM4 的CH1 的波形。通过修改debug的gSendTrigEn变量值可以重复产生一个触发条件。
	    2、程序通过PA3的产生上升沿，并传送到TIM4 CH2（PD13），触发TIM4 CH1（PD12）输出一个单脉冲，脉冲宽度2.048ms。

4、注意事项
	 开发板PA3与PB7需要连接。