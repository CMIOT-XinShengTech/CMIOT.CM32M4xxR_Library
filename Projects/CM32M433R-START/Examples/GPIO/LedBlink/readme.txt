1、功能说明

	1、此例程展示通过GPIO控制 LED（D4、D5、D6）闪烁
	2、控制 IO 口电平翻转

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
	IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M4xxR-START

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、GPIO：PB5、PB6、PB7 控制 LED6、LED7、LED8 闪烁

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.上电后LED6、LED7、LED8闪烁，其中LED7、LED8同时闪烁；
        3.用示波器观察PB5、PB6和PB7管脚可以测得方波；

4、注意事项
	无