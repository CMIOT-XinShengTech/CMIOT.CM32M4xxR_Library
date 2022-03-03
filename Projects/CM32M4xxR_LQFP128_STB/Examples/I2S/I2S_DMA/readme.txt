1、功能说明

	1、I2S 通过 DMA 收发数据


2、使用环境

	软件开发环境：
        IDE工具：NucleiStudio IDE for C/C++ 2021-02
    
    硬件环境：
        开发板 CM32M4xxR_LQFP128_STB

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、GPIO：I2S2（SLAVE  SPI2 WS--PB12、SCK--PB13、MOSI--PB15），
	         I2S3（MASTER SPI3 WS--PD2、SCK--PC10、 MOSI--PC12）,
	3、DMA：I2S2 接收采用 DMA1_CH4 通道，I2S3 发送采用 DMA2_CH2 通道；


	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.I2S3 通过 DMA2_CH2 发送数据，I2S2 通过 DMA1_CH4 接收数据
        3.运行完成后，通过输出的log信息查看运行结果


4、注意事项
	上位机查看log信息需要J4按RX<->5TX、TX<->5RX的方式使用跳帽进行连接