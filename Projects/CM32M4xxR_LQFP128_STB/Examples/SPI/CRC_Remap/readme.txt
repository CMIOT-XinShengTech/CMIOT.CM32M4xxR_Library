1、功能说明

	1、SPI 重映射后发送接收数据进行 CRC 校验


2、使用环境

	软件开发环境：
        IDE工具：NucleiStudio IDE for C/C++ 2021-02
    
    硬件环境：
        开发板 CM32M4xxR_LQFP128_STB

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、GPIO：SPI1: SCK--PA5、MISO--PA6、MOSI--PA7,
                 SPI2: SCK--PC7、MISO--PC8、MOSI--PC9，

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.SPI1 和 SPI2 重映射初始化完成以后，SPI1 发送数据，SPI2 接收数据 ，传输完成后，发送 CRC 数据，检查数据和 CRC 值，查看 TransferStatus1 和 TransferStatus2 状态为 PASSED，
          再查看 CRC 值；
        3.通过输出的log信息查看运行结果

4、注意事项
    1.上位机查看log信息需要J4按RX<->5TX、TX<->5RX的方式使用跳帽进行连接
    2.因需要使用杜邦线进行连接，线间存在干扰，即使正确连接也有传输失败的可能，可调整杜邦线摆放位置后再进行测试