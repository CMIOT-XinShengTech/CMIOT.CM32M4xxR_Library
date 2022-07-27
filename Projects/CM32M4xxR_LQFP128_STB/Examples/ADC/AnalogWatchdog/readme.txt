1、功能说明

    1、ADC1采样转换PC2引脚的模拟电压，如果超过模拟看门狗定义的阈值范围，则跳入中断程序。

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板 */
        CM32M4xxR_LQFP128_STB

3、使用说明
	
        /* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、时钟源：
               HSE=8M,PLL=144M,AHB=144M,APB1=36M,APB2=72M,ADC CLK=144M/16,ADC 1M CLK=HSE/8。
        2、ADC：
               ADC1独立工作模式、连续转换、软件触发、12位数据右对齐，转换PC2引脚的模拟电压数据。
        3、端口配置：
               PC2选择为模拟功能ADC1转换通道8。
        4、中断：
               ADC1模拟看门狗中断打开，优先级1。

        /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将变量gCntAwdg添加到watch窗口观察。
        2、改变PC2引脚电压值，当电压值超出模拟看门狗定义的0x300到0xB00范围外，则进入一次中断，变量做累加操作。

4、注意事项
        1、当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8)可以配置为HSE或者HSI。
        2、当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)只能配置为HSI。