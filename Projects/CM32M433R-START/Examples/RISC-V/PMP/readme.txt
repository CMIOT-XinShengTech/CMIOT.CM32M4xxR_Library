1、功能说明

	本示例展示了PMP内存保护单元的基本用法；
	样例中定义了一个test_array数组，并将其存放在0x2001A000地址，并且PMP将其所在地址定义为只读权限；
	在程序运行时分别进行变量访问及修改操作，当执行修改操作时将触发PMP异常；

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    	IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M433R-START

3、使用说明

	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、USART配置如下：
                - 波特率 = 115200 baud
                - 字长 = 8数据位
                - 1停止位
                - 校验控制禁用
                - 硬件流控制禁用（RTS和CTS信号）
                - 接收器和发送器使能
		- UART4_Tx.PD0
                - UART4_Rx.PD1
        3、通过Micro USB连接开发板，确保J6、J7跳帽短接；或使用外部USB Serial工具连接TX4,RX4管脚；
	
	使用方法：
		1.编译后下载程序复位运行；
	    	2.程序运行后，将在log串口打印访问test_array及修改test_array的日志信息；
		
4、注意事项
	PMP的最小slot单位为128bytes
	用例中定义的test_array所在地址为只读权限，并且PMP Lock表明该选项在机器模式下同样生效；
	用例中首先读取test_array将放行，在修改test_array变量时将触发PMP异常；
	