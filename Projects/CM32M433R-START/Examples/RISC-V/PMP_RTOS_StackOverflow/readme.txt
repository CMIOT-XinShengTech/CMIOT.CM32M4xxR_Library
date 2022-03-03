1、功能说明

	这个例程以RTThread为例，展示了如何使用PMP进行RTOS的线程栈溢出检测

	本样例中实现了两个测试线程，
		其中red为正常线程，每隔1秒打印“red task is running”；
		其中green为陷阱线程在运行10次之后将触发递归调用造成栈溢出，并每隔1秒打印“green task is running”

	通过在线程切换时，在PMP中切换目标线程的堆栈保护信息，在栈底预留128bytes slot为只读权限；防止当前线程溢出导致其他线程栈干扰；

	因此在green线程运行10次之后，将在触发PMP异常并被捕获，同时删除green线程并进行调度，red线程将持续工作；
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
	    	2.程序运行后，green和red线程将交替打印线程与运行信息；在green线程运行10次之后将被PMP异常捕获并结束该线程，同时RED线程持续运行；
		
4、注意事项
	PMP的最小slot单位为128bytes
	由于默认机器模式下不被PMP控制器约束，因此为了实现机器模式下PMP生效，需将CSR_MSTATUS寄存器的MPRV置位；

	