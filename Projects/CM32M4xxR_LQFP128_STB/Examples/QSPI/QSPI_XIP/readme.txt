1、功能说明
    通过QSPI接口操作板上的串行Flash（GD25Q40C）芯片，在四线XIP模式对Flash进行读取，并打印读取的数据，在XIP操作前通过普通四线模式写入数据。

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	六类接口功能扩展板

3、使用说明
    
    系统配置；
        1、时钟源：HSE+PLL
        2、系统时钟：144MHz
		3、QSPI时钟：HCLK
		4、QSPI通信时钟：HCLK/8
		5、QSPI端口：
			PA4: NSS	PA5: CLK	PA6: IO0	PA7: IO1	PC4: IO2	PC5: IO3

    使用方法：
        1、编译后烧录到全功能板，打开串口工具，通电，通过串口输出当前例程名
		2、紧接着输出一包数据，数据的内容是十六进制格式显示的从Flash中读取的一页（256 Bytes）的数据（程序中在读之前通过普通四线模式预先写入一包数据）

        
4、注意事项
	1、前述的使用双线或四线模式对Flash进行的读、写操作特指从Flash的页中读数据和向Flash的页中写数据，未特别说明时，其他针对Flash的任何操作均使用标准SPI模式。
	2、编译程序时不同的优化配置生成程序的执行效率不同，可能会影响QSPI的时序导致与Flash通信失败。例程中默认采用-O2的优化配置，如在其他配置下无法工作，可尝试：
	（1）降低QSPI通信时钟频率
		更改以下代码：
		Application/Source/qspi_flash.c中qFLASH_Init()函数中
		#ifdef QSPI_USE_36M
			QSPI_InitStructure.ClkDiv = 4;
		#else
			QSPI_InitStructure.ClkDiv = 8; //TODO:..To reduce the frequency, choose a larger even number.
		#endif
	（2）使用DMA方式（对Flash的所有操作均使用DMA方式）
		使用DMA方式可以将QSPI的通信下效率最大化，如要启用DMA方式需更改以下代码：
		Application/Source/qspi_flash.c中
		//#define QSPI_USE_36M //TODO:..Uncomment this line to use DMA.
		
		Application/Source/qspi_flash.c中qFLASH_Init()函数中
		#ifdef QSPI_USE_36M
			QSPI_InitStructure.ClkDiv = 4; //TODO:..Choose a suitable frequency.
		#else
			QSPI_InitStructure.ClkDiv = 8;
		#endif