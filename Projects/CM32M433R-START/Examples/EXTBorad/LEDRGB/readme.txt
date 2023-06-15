1、功能说明

	定时翻转START板和扩展板上的所有LED灯。

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M433R-START + CM32M433R-EXTEND

3、使用说明
	1、下载程序即可观察现象
	2、修改RGBLEDValueCfg(20, 127, 255)参数值可以调整RGBLED的显示亮度。
	3、RGBLED使用TIM4输出PWM进行控制，
		
4、注意事项
	无