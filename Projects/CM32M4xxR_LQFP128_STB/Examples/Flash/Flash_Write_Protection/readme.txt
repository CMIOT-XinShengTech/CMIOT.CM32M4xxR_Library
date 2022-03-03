1、功能说明

        这个例程配置并演示开启FLASH写保护


2、使用环境
	软件开发环境：  NucleiStudio IDE for C/C++ 2021-02
	硬件环境：      CM32M4xxR_LQFP128_STB

3、使用说明
	
		1、SystemClock：144MHz
		2、DMA：数据传输方向为SRAM到FLASH
		3、串口配置：
			- 串口为UART5（TX：PE8  RX：PE9）,可通过跳针连接U转串芯片后直接使用Micro USB与 MCU 进行串口通信
			- 数据位：8
			- 停止位：1
			- 奇偶校验：无
			- 波特率： 115200               

	使用方法：
		1.编译后下载程序复位运行；
		2.开启FLASH写保护，查看串口信息，当FLASH数据写入失败时，打印信息为测试通过；


4、注意事项