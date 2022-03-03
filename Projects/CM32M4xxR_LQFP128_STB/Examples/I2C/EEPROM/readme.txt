1、功能说明

    此例程展示了通过I2C模块与外部EEPRON的通信，分别采用查询、中断、DMA方式进行EEPROM的读写。   

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：NucleiStudio IDE for C/C++ 2021-02
	
	/* 开发板 */
	CM32M4xxR_LQFP128_STB + 六类接口功能扩展板

3、使用说明
	
    1、时钟源：HSE+PLL
    2、主时钟：144MHz
    3、I2C1 配置：
            SCL   -->  PB8
            SDA   -->  PB9

            ADDR：0xA2(7bit)
            CLOCK:400KHz
            
    4、USART1配置：
            TX  -->  PE8
            波特率：115200
            数据位：8bit
            停止位：1bit
            无校验

    5、测试步骤与现象
        a，将六类接口功能扩展板和CM32M4xxR_LQFP128_STB进行连接
        b，编译下载代码复位运行
        c，从串口看打印信息，验证结果
		d，修改i2c_eeprom.h中的PROCESS_MODE宏值，0代表查询方式进行I2C通信，1代表中断方式进行I2C通信，2代表DMA方式进行I2C通信。
		e，重新编译下载代码，复位运行查看结果。

4、注意事项
    1，此处使用的EEPROM是AT24C02，32个page，每个page 8byte
    2，读写数据时若长度大于一个page，则器件地址会自动回卷
    3，SCL,SDA有1K的外部上拉电阻
	