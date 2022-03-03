1、功能说明

	1、TIM3 CH1 CH2 CH3 CH4 达到CC值后，输出ACTIVE电平
	
2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M433R-START

3、使用说明

	系统配置；
		1、时钟源：
		            HSE=8M,AHB=8M,APB1=8M,APB2=8M,TIM3 CLK=1KHz
		2、端口配置：
					PC6选择为TIM3 CH1输出
					PC7选择为TIM3 CH2输出
					PC8选择为TIM3 CH3输出
					PC9选择为TIM3 CH4输出
					PD6选择为IO 输出
	    3、TIM：
		            TIM3 CH1、CH2、CH3、CH4全部设置为匹配设置有效电平模式，有效电平设置为高电平。
					四个通道分别对应不同的比较值。
	使用方法：
		1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM2 CH1（PC6） CH2（PC7） CH3（PC8） CH4（PC9）和PD6的波形。
	    2、定时器运行到CC1 CC2 CC3 CC4之后，对应通道的输出变为Active。
		3、PD6上升沿为参考位置，观察TIM3各个通道的上升沿与参考上升沿的时间差。
		     PC6上升沿时间戳 - PD6上升沿时间戳 = 1000ms
			 PC7上升沿时间戳 - PD6上升沿时间戳 = 500ms
			 PC8上升沿时间戳 - PD6上升沿时间戳 = 250ms
			 PC9上升沿时间戳 - PD6上升沿时间戳 = 125ms

4、注意事项
	无