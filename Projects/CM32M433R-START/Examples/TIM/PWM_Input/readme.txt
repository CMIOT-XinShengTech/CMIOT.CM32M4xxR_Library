1、功能说明

	1、TIM3 CH2捕获引脚通过CH1下降沿和CH2上升沿计算占空比和频率

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M433R-START

3、使用说明

	系统配置；
		1、时钟源：
		            HSE=8M,PLL=144M,AHB=144M,APB1=36M,APB2=72M,TIM2 CLK=2KHz， TIM3 CLK=1MHz
		2、中断：
		            TIM3 CC2比较中断打开
		3、端口配置：
					PC7选择为TIM3的CH2输入
					PA0选择为TIM2 PWM输出
	    4、TIM：
		            TIM3 CH1下降沿捕获CH2信号，CH2上升沿捕获CH2信号
	使用方法：
		1、编译后打开调试模式，连接PA0和PC7，将Frequency、DutyCycle添加到watch窗口
	    2、程序运行后，PA0输出周期为400Hz占空比为40%的PWM波形，PA7捕获该PWM波形并在中断中计算周期和频率。
	      在TIM3_IRQHandler函数中打断点，可以在watch窗口中观察到计算出的周期和频率值
4、注意事项
	 参考用户手册11.3.7 PWM 输入模式
	 开发板需要连接PA0和PC7
	 TIM3的频率不宜太高，否则无法准确捕获到数据。
	 