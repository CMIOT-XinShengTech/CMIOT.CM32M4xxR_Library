1、功能说明

	此例程实现DES ECB/CBC模式及3DES 2KEY(16bit)/3KEY(24bit)下ECB/CBC模式的加解密运算，测试数据通过log串口打印输出；

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

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.上电后查看串口助手输出串口，将打印DES/3DES加解密的过程数据；
        

4、注意事项
	无