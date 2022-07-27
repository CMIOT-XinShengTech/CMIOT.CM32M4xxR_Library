1、功能说明

        本样例为ADC高速采样功能样例，实现了ADC 12bit 5M采样的功能

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板 */
        CM32M4xxR_LQFP128_STB

3、使用说明
        /* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、时钟源：
               HSE=8M,PLL=144M,AHB=144M,APB1=36M,APB2=72M,ADC CLK=144M/2,ADC 1M CLK=HSE/8,DMA CLK=144M。
        2、中断：
               DMA传输结果完成中断打开，优先级0。
        3、端口配置：
               PA0选择为模拟功能ADC1转换通道1。
               PA1选择为输出功能，用来在DMA传输后反转电平观察采样时间。
               PE8为串口输出引脚，波特率115200，用于信息的打印
        4、DMA：
               DMA1_CH1通道回环模式搬运一个半字的ADC1转换结果到ADC1ConvertedValue变量。
        5、ADC：
               ADC1独立工作模式、连续转换、软件触发、12位数据右对齐，转换通道1即PA0的模拟电压数据。

        /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将变量ADC1ConvertedValue添加到watch窗口观察。
        2、通过改变PA0引脚的电压，可以看到转换结果变量同步改变。
        3、通过log查看ADC采样的信息，每采样5M数据会进行一次打印
        4、也可以通过PA1的输出观测采样的频率，每采样50K数据会产生一次先拉高后拉低的脉冲

4、注意事项
        1、当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8)可以配置为HSE或者HSI。
        2、当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)只能配置为HSI。
        3、上位机查看log信息需要J4按RX<->5TX、TX<->5RX的方式使用跳帽进行连接
        4、可以通过改变bit数提高采样率，可以通过ADC_SetConvResultBitNum进行bit数的改变，此部分代码已预留