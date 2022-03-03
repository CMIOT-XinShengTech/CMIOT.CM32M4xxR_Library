1、功能说明

    此例程展示了I2C模块10bit地址模式的读写操作。   

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M433R-START

3、使用说明
	
    1、时钟源：HSE+PLL
    2、主时钟：144MHz
    3、I2C4主配置：
            SCL   -->  PA9
            SDA   -->  PA10
            ADDR：0x230(10bit)
            CLOCK:100KHz

    4、I2C2从配置：
            SCL   -->  PG2
            SDA   -->  PG3
            ADDR：0x2A0(10bit)
            CLOCK:100KHz            

    5、USART1配置：
            TX  -->  PD0
            波特率：115200
            数据位：8bit
            停止位：1bit
            无校验

    6、测试步骤与现象
        a，用杜邦线连接PA9-PG2和PA10-PG3,并添加外部上拉电阻。
        b，编译下载代码复位运行
        c，从串口看打印信息，验证结果
		     ←◆-----this is a i2c(10bit) master/slave demo
			i2c(10bit) master->slave test pass!
			i2c(10bit) master<-slave test pass!

4、注意事项
    由于START开发板没有板载上拉电阻，需要用户在SDA和SCL上外接上拉电阻，注意仅有一个板子连接上拉电阻即可。
	板级连线时注意不要选用太长的杜邦线。
	由于I2C通信与总线上的上拉电阻大小和等效电容有相关性，如果样例无法正常运行，可以尝试调整管脚驱动能力和上拉电阻大小。
	