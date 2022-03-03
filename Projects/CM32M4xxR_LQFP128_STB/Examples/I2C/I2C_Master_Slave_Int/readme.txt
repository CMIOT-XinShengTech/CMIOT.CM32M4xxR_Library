1、功能说明

    此例程展示了I2C模块中断模式的读写操作。   

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	CM32M4xxR_LQFP128_STB

3、使用说明
	
    1、时钟源：HSE+PLL
    2、主时钟：144MHz
    3、I2C1主配置：
            SCL   -->  PB6
            SDA   -->  PB7
            ADDR：0x30(7bit)
            CLOCK:100KHz

    4、I2C2从配置：
            SCL   -->  PB10
            SDA   -->  PB11
            ADDR：0xA0(7bit)
            CLOCK:100KHz         
   
    5、USART5配置：
            TX  -->  PE8
            波特率：115200
            数据位：8bit
            停止位：1bit
            无校验

    6、测试步骤与现象
        a，用杜邦线连接PB6-PB10和PB7-PB11
        b，编译下载代码复位运行
        c，从串口看打印信息，验证结果

4、注意事项
    PB6和PB7需要通过拨码开关连接上拉电阻。
	连接用的杜邦线不宜太长。