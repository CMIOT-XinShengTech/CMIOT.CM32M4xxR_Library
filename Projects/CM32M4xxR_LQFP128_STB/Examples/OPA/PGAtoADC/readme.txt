1、功能说明

	1、OPA1 PGA模式，放大输入电压2倍后输出给ADC进行电压采集

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
					PA1选择为模拟功能OPA1 VP
					PA6为OPA1的输出
	    3、OPA：
		            OPA1 PGA功能，倍数2倍
					
	使用方法：
		1、编译后打开调试模式，用示波器观察OPA1 的输入和ADC的采集值
	    2、ADC的采集值电压=2*OPA输入
		
4、注意事项
	无。