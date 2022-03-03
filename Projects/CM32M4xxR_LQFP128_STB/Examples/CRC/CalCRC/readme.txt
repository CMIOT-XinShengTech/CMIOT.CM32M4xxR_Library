1、功能说明

    此例程展示了硬件CRC的基本功能和算法。
    
    其中有16bit校验与32bit校验，
    

2、使用环境

	软件开发环境：
        IDE工具：NucleiStudio IDE for C/C++ 2021-02
    
    硬件环境：
        开发板 CM32M4xxR_LQFP128_STB


3、使用说明
	
    1、时钟源：HSE+PLL
    2、主时钟：144MHz
    3、通过输出的log信息查看CRC运算结果

4、注意事项
    上位机查看log信息需要J4按RX<->5TX、TX<->5RX的方式使用跳帽进行连接