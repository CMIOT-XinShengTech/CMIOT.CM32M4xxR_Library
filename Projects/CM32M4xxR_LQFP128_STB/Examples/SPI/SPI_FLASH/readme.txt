1、功能说明

    1、SPI 读、写、擦除 GD25Q40


2、使用环境

	软件开发环境：
        IDE工具：NucleiStudio IDE for C/C++ 2021-02
    
    硬件环境：
        CM32M4xxR-LQFP128 开发板 + 六类接口功能扩展板

3、使用说明
    
    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    1、SystemClock：144MHz
    2、GPIO：SPI1: NSS--PA15、SCK--PB3、MISO--PB4、MOSI--PB5

    /* 描述Demo的测试步骤和现象 */
    1.编译后下载程序复位运行；
    2.程序等待WKUP键按下后继续执行
    3.通过 SPI1 读取 GD25Q40 的 ID，然后写数据，再读出来，比较读写数据，查看 TransferStatus1 状态为 PASSED，
      然后擦除块，检查擦除块正常。
    4.通过输出的log信息查看运行结果

4、注意事项
    1.WKUP按键的正常检测需将拨码开关ON1中PA0位进行连通
    2.其中PA15和PB3为JTAG引脚，所以在调试中会对这几个脚进行remap关闭JTAG功能，
      这会导致debug调试中断，运行结束后会将remap关闭重新打开JTAG功能
    3.上位机查看log信息需要J4按RX<->5TX、TX<->5RX的方式使用跳帽进行连接