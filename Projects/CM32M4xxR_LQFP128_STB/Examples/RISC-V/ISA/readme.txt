1、功能说明

	本示例展示获取当前芯片的RISC-V内核ISA架构;
	RISC-V内核中CSR_MISA寄存器存储了当前芯片的ISA配置定义，通过读取该寄存器并进行转义输出；

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    	IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	CM32M4xxR_LQFP128_STB

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
        3、通过USB Serial连接开发板或外置链接USART引脚连接如下：
                - UART5_Tx.PE8
                - UART5_Rx.PE9	
	
	使用方法：
		1.编译后下载程序复位运行；
	    	2.程序运行后，将在log串口打印“MISA: RV32IMACFSPU”
		
4、注意事项

	ISA: RV32IMACFSPU -> CM32M4xxR支持
	RV32I	基本整数指令集, 32位
	M	整数乘除法标准扩展
	A	不可中断指令(Atomic)标准扩展
	F	单精确度浮点运算标准扩展
	C	压缩指令标准扩展 
	P	DSP单指令多数据流（SIMD）运算标准扩展
	S	Supervisor模式支持
	U	用户模式支持