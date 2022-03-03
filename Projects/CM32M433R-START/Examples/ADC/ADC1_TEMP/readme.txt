1、功能说明

        1、ADC1采样转换内部温度传感器的模拟电压，并转换为温度值。

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板 */
        CM32M433R-START

3、使用说明
	
        /* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、时钟源：
               HSE=8M,PLL=144M,AHB=144M,APB1=36M,APB2=72M,ADC CLK=144M/16,ADC 1M CLK=HSE/8,DMA CLK=144M。
        2、DMA：
               DMA1_CH1通道回环模式搬运一个半字的ADC1转换结果到ADCConvertedValue变量。
        3、ADC：
               ADC1独立工作模式、连续转换、软件触发、12位数据右对齐，转换通道16即内部温度传感器的模拟电压数据。
        4、端口配置：
               PD0选择为UART4的TX引脚
               PD1选择为UART4的RX引脚
        5、UART：
               UART5 115200波特率、8位数据位、1位停止位、无奇偶校验位、无硬件流控、发送和接收使能。
        6、功能函数：
               TempValue = TempCal(ADCConvertedValue)函数将温度ADC原始格式数据转为度的单位的格式。

        /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将变量ADCConvertedValue,TempValue添加到watch窗口观察。
        2、全速运行，可以看到温度变量的数值在常温下接近25度左右，同时串口工具显示实时芯片内的温度值。

4、注意事项
        1、当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8)可以配置为HSE或者HSI。
        2、当系统采用SI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)只能配置为HSI。
        3、printf打印float参数需要勾选Use float with nano printf，设置路径如下：
        工程右键 -> Properties -> C/C++ Build -> Settings -> Tool Settings -> GNU RISC-V Cross Linker -> Miscellaneous -> 勾选Use float with nano printf。