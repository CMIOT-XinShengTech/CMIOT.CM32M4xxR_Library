1、功能说明

	1、TIM3 CH2上升沿计算频率

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	CM32M4xxR_LQFP128_STB

3、使用说明
	系统配置：
		1、时钟源：
		            HSE=8M,AHB=8M,APB1=8M,APB2=8M,TIM3 CLK=8M
		2、中断：
		            TIM3 CH2上升沿中断打开
		3、端口配置：
					PA7选择为TIM3 CH2输入
					PA3选择为IO 输出
	    4、TIM：
		            TIM3 CH2 上升沿捕获中断打开,捕获的频率范围最小为((TIM3 CLK)/0xffff)Hz,最大频率为((TIM3 CLK)/1)Hz
					
	使用方法：
		1、编译后打开调试模式，连接PA3与PA7，将变量TIM3Freq添加到watch窗口。
	    2、程序控制PA3电平翻转后，查看TIM3Freq计算的频率值。
		3、PA3输出波形中两个上升沿间隔为195us左右，两次上升沿捕获值相差1566，根据TIM3时钟8M进行计算，TIM3Freq = 8M/1566 = 5.108Khz，其周期为195us。
		
4、注意事项
	开发板将PA3与PA7连接。