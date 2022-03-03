1、功能说明
	1、通过RTC闹钟来唤醒STOP2。
	2、串口打印进入退出状态

2、使用环境
	软件开发环境：  NucleiStudio IDE for C/C++ 2021-02
    硬件环境：      CM32M433R-START
3、使用说明
	
	系统配置；
        1、RTC时钟源：LSI
        2、低功耗模式：STOP2
        3、串口配置：
            - 串口为USART5（TX：PE8  RX：PE9）:
            - 数据位：8
            - 停止位：1
            - 奇偶校验：无
            - 波特率： 115200 


    使用方法：
        编译后烧录到评估板，通电，过了一会串口打印start low power，说明进入低功耗模式了。
        当串口打印输出Exit low power，说明此时闹钟唤醒STOP2了。


4、注意事项
    上位机查看log信息需要J4按RX<->5TX、TX<->5RX的方式使用跳帽进行连接