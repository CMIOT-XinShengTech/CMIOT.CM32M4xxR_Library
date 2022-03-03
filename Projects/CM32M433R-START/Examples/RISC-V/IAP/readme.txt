1、功能说明

	本示例展示了通过XMODEM协议实现在线应用编程方案：
	IAP_Boot为Boot阶段示例工程，该工程基于XMODEM协议实现用户程序bin文件的传输；
	IAP_User为用户示例代码，该应用为GPIO/LedBlink样例工程；
	PA0_WKUP按键用于进行模式选择，默认将自动进入Boot态，若按下WKUP按键上电运行则进入用户态；

	Flash空间分布：
	Bootloader ： 0x8000000-0x8010000	
	Application： 0x8010000-0x8080000
	
	若用户希望更改Flash分布，拟修改IAP_Boot/Application/Include/flash.h中 BOOT_FLASH_BASE/BOOT_FLASH_SIZE/USER_FLASH_BASE/USER_FLASH_SIZE定义
	IAP_Boot/gcc_cm32m4xxr.ld及IAP_User/gcc_cm32m4xxr.ld中ROM_BASE/ROM_SIZE的配置

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    	IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M433R-START

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
		- UART4_Tx.PD0
                - UART4_Rx.PD1
        3、通过Micro USB连接开发板，确保J6、J7跳帽短接；或使用外部USB Serial工具连接TX4,RX4管脚；
	4、GPIO配置：PA0选择为GPIO输入模式,PB5选择为GPIO输出模式

	使用方法：
		1.导入工程IAP_User，编译后将在IAP_User/Debug下生成IAP_User.bin用户固件烧录文件；
		2.导入工程IAP_Boot，编译后下载程序并复位运行；
		3.用户可选择使用Tera Term终端链接串口与开发板进行交互；
	    	4.程序运行后，将自动进入Bootloader状态，通过log串口打印选择菜单，用户可输入‘1’进入用户固件下载模式；
		5.在Tera Term下选择文件->传输->XMODEM->发送，选择目标下载文件IAP_User.bin，等待发送完成；
		6.下载完成后将会带主菜单，用户可输入‘2’进入用户代码，进入用户代码后将运行LEDBlink样例，LED6将持续闪烁；
		

4、注意事项

	无