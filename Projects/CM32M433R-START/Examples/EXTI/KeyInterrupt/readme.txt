1、功能说明

	1、此例程展示通过外部触发中断，控制 LED 闪烁

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M433R-START

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、GPIO：PA0 选择作为外部中断入口，设置为上升沿触发中断，PB5 控制 LED6，PB6 控制 LED7 。


	/* 描述Demo的测试步骤和现象 */
        1. 编译后下载程序复位运行；
        2. 第一次按下按键 WKUP（PA0接地），LED6和LED7熄灭；
		    第一次松开按键WKUP（PA0接3.3V），LED6和LED7保持常量；
			第二次按下按键WKUP（PA0接地），LED6熄灭，LED7亮起；
			第二次松开按键WKUP（PA0接3.3V），LED6亮起，LED7熄灭。

4、注意事项
	无
	