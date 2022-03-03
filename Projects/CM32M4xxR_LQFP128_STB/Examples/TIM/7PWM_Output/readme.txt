1、功能说明
	1、TIM1和TIM8同时输出3路互补波形和一路CH4波形
2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	CM32M4xxR_LQFP128_STB
	
3、使用说明
	系统配置；
		1、时钟源：
		            HSE=8M,AHB=8M,APB1=8M,APB2=8M,TIM1 CLK=8M，TIM8 CLK=8M
		2、端口配置：
					PA8选择为TIM1 CH1输出
					PA9选择为TIM1 CH2输出
					PA10选择为TIM1 CH3输出
					PB13选择为TIM1 CH1N输出
					PB14选择为TIM1 CH2N输出
					PB15选择为TIM1 CH3N输出
					PA11选择为TIM1 CH4输出
					PC6选择为TIM8 CH1输出
					PC7选择为TIM8 CH2输出
					PC8选择为TIM8 CH3输出
					PA7选择为TIM8 CH1N输出
					PB0选择为TIM8 CH2N输出
					PB1选择为TIM8 CH3N输出
					PC9选择为TIM8 CH4输出
	    3、TIM：
		            TIM1 6路互补输出,CH4输出
					TIM8 6路互补输出,CH4输出
	使用方法：
		1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1 TIM8的输出波形
	    2、输出波形TIM1 3路互补加一路CH4，TIM8 3路互补加一路CH4
4、注意事项
	无