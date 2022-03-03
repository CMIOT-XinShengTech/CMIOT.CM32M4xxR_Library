1、功能说明

	1、I2S 通过中断收发数据


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
	3、中断：I2S2 中断入口函数 SPI2_IRQHandler，I2S3 中断入口函数SPI3_IRQHandler，


	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.I2S 初始化成 16 位数据格式，48K 采样频率:I2S2有数据接收时进入 SPI2_I2S2_IRQHandler 函数接收数据，I2S3有数据发送时进入 SPI3_I2S3_IRQHandler 函数发送数据,运行完成后，查看 TransferStatus1 状态为 PASSED；
          I2S 初始化成 24 位数据格式，16K 采样频率:I2S2有数据接收时进入 SPI2_I2S2_IRQHandler 函数接收数据，I2S3有数据发送时进入 SPI3_I2S3_IRQHandler 函数发送数据,运行完成后，查看 TransferStatus2 状态为 PASSED；
        3.运行完成后，通过输出的log信息查看运行结果

4、注意事项
	上位机查看log信息需要J4按RX<->5TX、TX<->5RX的方式使用跳帽进行连接