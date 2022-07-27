1、功能说明
	1、STOP2模式的进入和退出。


2、使用环境
	软件开发环境：  NucleiStudio IDE for C/C++ 2021-02
    硬件环境：      CM32M433R-START
3、使用说明
	
	系统配置；
        1、时钟源：HSE+PLL
        2、时钟频率：144MHz
        3、唤醒源：按键WKUP


	使用方法：
        编译后烧录到评估板，接上电流表，上电后发现电流由mA降到了uA级别，
        按下唤醒按键,电流由回到了mA级别，过了一会又降到uA。


4、注意事项
    1.评估功耗时的软件要求：
        需要注释掉main函数中的DBG_ConfigPeriph(DBG_STOP, ENABLE);
        (该函数用于在debug时防止因进入STOP模式而导致debug连接中断，会引入额外的功耗)

