1、功能说明
	1、通过设定闹钟时间来触发闹钟中断。
	2、通过闹钟标志位来配置IO输出
	3、设备初始化后运行在standby休眠模式，通过设定闹钟时间来触发闹钟中断唤醒设备。
	
2、使用环境

	软件开发环境：  NucleiStudio IDE for C/C++ 2021-02
	硬件环境：      CM32M4xxR_LQFP128_STB


3、使用说明
	
	系统配置；
		1、RTC时钟源：LSE
                2、闹钟IO输出：PC13
		3、串口配置：
			- 串口为UART5（TX：PE8  RX：PE9）,可通过跳针连接U转串芯片后直接使用Micro USB与 MCU 进行串口通信
			- 数据位：8
			- 停止位：1
			- 奇偶校验：无
			- 波特率： 115200 


	使用方法：
		设置RTC_ALARM_TEST_TYPE为RTC_ALARM_TEST_TYPE_IRQ，编译后烧录到评估板，上电，串口按照闹钟设定时间进行打印输出。
		设置RTC_ALARM_TEST_TYPE为RTC_ALARM_TEST_TYPE_OUTPUT，编译后烧录到评估板，此时会切换到闹钟输出，在PC13口会出现翻转电平。
		设置RTC_ALARM_TEST_TYPE为RTC_ALARM_TEST_TYPE_IRQ_WAKEUP，编译后烧录到评估板，此时设备会根据闹钟设置的时间周期重启。


4、注意事项
	当配置PC13输出模式为开漏模式时需要外置上拉电路。
	当配置RTC_ALARM_TEST_TYPE为RTC_ALARM_TEST_TYPE_IRQ_WAKEUP模式烧录程序到评估板后，如果无法继续抄录程序请将Boot0拉高后重新尝试抄录固件。