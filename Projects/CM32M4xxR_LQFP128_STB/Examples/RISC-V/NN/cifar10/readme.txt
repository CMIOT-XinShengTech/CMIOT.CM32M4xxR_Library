1、功能说明

	示例演示如何使用NN库进行cifar10图像分类识别；

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称 */
    IDE工具：NucleiStudio IDE for C/C++ 
	
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
		1、通过宏#define TEST_IMAGE deer1选择要识别的图像，所有图像数据存储在image_data.h中
	    2、程序运行后，将通过日志log串口打印分类识别结果；
		
4、注意事项
	无