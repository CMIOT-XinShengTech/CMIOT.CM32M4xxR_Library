1、功能说明
	1、systick 100ms触发TIM1输出6步换相波形
2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	CM32M4xxR_LQFP128_STB
	
3、使用说明
	系统配置；
		1、时钟源：
		            HSE=8M,AHB=8M,APB1=8M,APB2=8M,TIM1 CLK=8M，TIM8 CLK=8M
		2、中断：
		            TIM1 COM事件中断打开，抢断优先级0，子优先级1
					Systick 100ms中断，优先级0
		3、端口配置：
					PA8选择为TIM1 CH1输出
					PA9选择为TIM1 CH2输出
					PA10选择为TIM1 CH3输出
					PB13选择为TIM1 CH1N输出
					PB14选择为TIM1 CH2N输出
					PB15选择为TIM1 CH3N输出
					PB12选择为TIM1 Breakin输入
	    4、TIM：
		            TIM1 6路互补冻结输出模式，有刹车，开COM中断
	使用方法：
		1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1的输出波形
	    2、每隔100ms systick触发COM中断，在TIM的COM中断里面输出AB AC BC BA CA CB的6步换相波形
		
4、注意事项
	无