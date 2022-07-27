1、功能说明

	1、COMP1的输出影响TIM3的PWM输出

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	CM32M4xxR_LQFP128_STB

3、使用说明
	系统配置：
		1、时钟源：
		            HSE=8M,AHB=8M,APB1=8M,APB2=8M,TIM3 CLK=8M

		2、端口配置：
					PB10选择为模拟功能COMP INP
					PA5选择为模拟功能COMP INM
					PC14选择为IO输出
					PC15选择为IO输出
					PA7选择为TIM3的CH2
	    3、COMP：
		            COMP1输入PB10，PA5，输出TIM3_OCrefclear
					
	使用方法：
		1、编译后打开调试模式，将PC14连接到PB10，PC15连接到PA5，利用示波器或者逻辑分析仪观察PA7输出波形
	    2、当软件输出PC14电平大于PC15时，TIM3_OCrefclear输出高电平TIM3不输出PWM方波，相反时，输出低电平TIM3输出PWM方波
		
4、注意事项
	无。