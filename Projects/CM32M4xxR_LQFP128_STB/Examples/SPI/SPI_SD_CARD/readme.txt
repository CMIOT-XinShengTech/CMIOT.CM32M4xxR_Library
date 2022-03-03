1、功能说明

	1、SPI 进行SD CARD的读写操作


2、使用环境

	软件开发环境：
        IDE工具：NucleiStudio IDE for C/C++ 2021-02
    
    硬件环境：
        开发板 CM32M4xxR_LQFP128_STB

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、GPIO：SPI1: SCK--PA5、 MISO--PA6、MOSI--PA7,NSS--PA4（soft）

	/* 描述Demo的测试步骤和现象 */
        1.按照线序将sd卡（标准SD卡，非micro）与单片机进行连接：
          SD卡  MCU
          PIN1：PA4
          PIN2：PA7
          PIN3：GND
          PIN4：3V3
          PIN5：PA5
          PIN6：空
          PIN7：PA6
          PIN8：空
          PIN9：空

        2.编译后下载运行程序
        3.程序会将"XinSheng Tech SD Card I/O Example via SPI\n"和"test!!!\n"写入到卡中first.txt文件并读出后进行打印
        4.通过输出的log信息查看打印信息

4、注意事项
    1.上位机查看log信息需要J4按RX<->5TX、TX<->5RX的方式使用跳帽进行连接
    2.因可能需要使用杜邦线进行连接，线间存在干扰，即使正确连接也有传输失败的可能，可调整线摆放位置后再进行测试