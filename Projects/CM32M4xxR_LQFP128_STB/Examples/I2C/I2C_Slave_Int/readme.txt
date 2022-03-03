1、功能说明

    此例程展示了通过I2C模块作为从设备利用中断与外部I2C主设备通信。   

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	CM32M4xxR_LQFP128_STB

3、使用说明
	
    1、时钟源：HSE+PLL
    2、主时钟：144MHz
    3、I2C1从配置：
            SCL   -->  PB6		AF_OD
            SDA  -->  PB7   	AF_OD

            ADDR：0xA0(7bit)
            CLOCK:100KHz
            
    4、USART1配置：
            TX  -->  PE8
            波特率：115200
            数据位：8bit
            停止位：1bit
            无校验

    5、测试步骤与现象
        a，用两块CM32M4xxR_LQFP128_STB开发板，一块做主设备，另一块做从设备
        b，主设备烧录I2C_Master_Int程序，从设备烧录I2C_Slave程序
        c，将两块板子的PB6/PB7对应连接起来
        d，分别编译下载代码，先复位从设备，再复位主设备
        e，从两个板子的串口看打印信息，验证结果

4、注意事项
    a，需要在SDA和SCL上外接上拉电阻，拨码开关6和7需要配置连接，注意仅有一个板子连接上拉电阻即可。
    b，必须共地！
	c ,  由于通过连线进行通信，通信速度不宜太高。
    i2c主机和从机互不影响，所以在搭建环境的时候，主机选择I2C_Master或者I2C_Master_Int都可以，从机选择I2C_Slave或者I2C_Slave_Int都可以。
	此测试用例是与用例I2C_Slave用例配套使用，将相同的两款单板分别烧写I2C_Master与I2C_Slave镜像，将相同的管脚连接，就可以实现通讯