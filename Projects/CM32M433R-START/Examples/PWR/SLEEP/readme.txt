﻿1、功能说明
	1、SLEEP模式的进入和退出。


2、使用环境
	软件开发环境：  NucleiStudio IDE for C/C++ 2021-02
    硬件环境：      CM32M433R-START
3、使用说明
	
	系统配置；
        1、时钟源：HSE+PLL
        2、时钟频率：144MHz
        3、唤醒源：按键WKUP(PA0)
        4、指示灯：PB6



	使用方法：
        编译后烧录到评估板，上电后，PB6控制的指示灯灭。每隔一会按下唤醒按键，
        指示灯PB6的电平都会翻转一次。


4、注意事项

