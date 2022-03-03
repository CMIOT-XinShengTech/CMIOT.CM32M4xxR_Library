1、功能说明

		这个例程配置并演示直接对FLASH进行读写操作


2、使用环境
	软件开发环境：  NucleiStudio IDE for C/C++ 2021-02
	硬件环境：      CM32M4xxR_LQFP128_STB

3、使用说明
		1、SystemClock：144MHz
		2、串口配置：
			- 串口为UART5（TX：PE8  RX：PE9）,可通过跳针连接U转串芯片后直接使用Micro USB与 MCU 进行串口通信
			- 数据位：8
			- 停止位：1
			- 奇偶校验：无
			- 波特率： 115200               

	使用方法：
		1.编译后下载程序复位运行；
        2.查看串口打印信息，程序通过EEPROM操作接口对变量地址直接进行读写，无需擦除过程；
		3.程序配置0x0800F000U和0x0800F800U两页FLASH来模拟EEPROM操作，并进行大量数据的写入和读出测试。


4、注意事项
	修改eeprom_in_flash.h文件配置eerpom。
	EEPROM_NUM_MAX：需要EEPROM存储的数据（16bit）个数。如果实际存储变量为32位，则应换算成2个数据；如果实际存储变量为8bit，则应扩展成1个16位数据。
	EEPROM_PART0_SIZE：EEPROM分区大小，应为flash页大小的整数倍，flash一页大小为2048（2K）。
	EEPROM_PART1_SIZE：EEPROM分区大小，应为flash页大小的整数倍，flash一页大小为2048（2K）。EEPROM需要两个分区。EEPROM_NUM_MAX不能超过(任何一个分区大小/4-2)
	PART0_BASE_ADDRESS：分区0的起始地址，用户应按照应用程序的FLASH空间划分选择合适的位置。
	PART1_BASE_ADDRESS：分区0的起始地址，用户应按照应用程序的FLASH空间划分选择合适的位置。