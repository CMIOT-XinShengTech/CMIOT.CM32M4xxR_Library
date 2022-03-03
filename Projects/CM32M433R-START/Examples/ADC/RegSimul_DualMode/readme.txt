1、功能说明

        1、ADC1 ADC2规则通道同步采样，ADC1采样PC2、PC3引脚的模拟电压，ADC2采样PA4、PA7引脚的模拟电压。
        2、同步转换的结果通过DMA1_CH1传输到ADC_DualConvertedValueTab[16]数组，只传输16次。

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板 */
        CM32M433R-START

3、使用说明
	
        /* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、时钟源：
               HSE=8M,PLL=144M,AHB=144M,APB1=36M,APB2=72M,ADC CLK=144M/16,ADC 1M CLK=HSE/8,DMA CLK=144M。
        2、端口配置：
                - PC2选择为模拟功能ADC1转换通道
                - PC3选择为模拟功能ADC1转换通道
                - PA4选择为模拟功能ADC2转换通道
                - PA7选择为模拟功能ADC2转换通道
        3、DMA：
               DMA1_CH1通道正常模式搬运16个字的ADC1、ADC2同步规则通道转换结果到ADC_DualConvertedValueTab[16]数组。
        4、ADC：
               ADC1规则通道同步规则通道模式、连续扫描模式、软件触发、12位数据右对齐，转换通道PC2和PC3的模拟电压数据。
               ADC2规则通道同步规则通道模式、连续扫描模式、软件触发、12位数据右对齐，转换通道PA4和PA7的模拟电压数据。

        /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将变量ADC_DualConvertedValueTab[16]添加到watch窗口观察。
        2、全速运行前，在PC2 PC3 PA4 PA7给确定的电压信号，全速运行后，即可转换16次结果到ADC_DualConvertedValueTab[16]数组。

4、注意事项
        1、ADC转换虽然是连续的，但是DMA只存储前16次数据到数组。
        2、当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8)可以配置为HSE或者HSI。
        3、当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)只能配置为HSI。