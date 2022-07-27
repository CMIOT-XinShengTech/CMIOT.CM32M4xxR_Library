1、功能说明

	1、COMP1的输出触发TIM3的CH1进行捕获

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
	    3、COMP：
		            COMP1输入PB10，PA5，输出TIM3_IC1
					
	使用方法：
		1、编译后打开调试模式，将PC14连接到PB10，PC15连接到PA5，将变量Capture加入WATCH窗口观察值的变化
	    2、当软件输出PC14电平大于PC15时，COMP1输出高电平，相反时，输出低电平，当电平变化时触发TIM捕获
		
4、注意事项
	在此用例中用到了CM32M4xxR_LQFP128_STB开发板的led功能作为指示中断触发的情况，需要在开发板上把拨码开关的第一个拨到ON上使LED功能生效。