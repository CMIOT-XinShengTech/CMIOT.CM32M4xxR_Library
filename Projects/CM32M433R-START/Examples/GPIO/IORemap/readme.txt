1、功能说明

	1、此例程展示读取端口高低电平，控制 LED6、LED7闪烁。
	2、将JTAG口作为普通IO输出进行电平翻转。

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M4xxR-START

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、GPIO：PA0 选择作为读取电平端口，PB5、PB6 控制 LED6、LED7.PA13、PA14、PA15、PB3 用于remap现象展示。

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.检查 PA0 口电平（WKUP按键）：
		   如果是高电平（释放WKUP按键），LED6熄灭，LED7常亮，PA13、PA14、PA15、PB3为JTAG功能。
		   如果是低电平（按下WKUP按键），LED6常亮，LED7熄灭，PA13、PA14、PA15、PB3为输出功能，输出电平间隔1秒进行翻转。

4、注意事项
	当检测到 PA0 口为低电平时，关闭了JTAG功能，会导致调试异常。
