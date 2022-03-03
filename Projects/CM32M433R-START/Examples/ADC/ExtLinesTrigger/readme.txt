1、功能说明

        1、ADC1规则通道采样PC2、PC3引脚的模拟电压，注入通道采样PA6、PA3引脚的模拟电压。
        2、其中规则转换结果通过DMA1_CH1通道读取到变量ADC_RegularConvertedValueTab[64]数组，
        注入转换结果通过转换结束中断读取到变量ADC_InjectedConvertedValueTab[32]数组。

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板 */
        CM32M433R-START

3、使用说明
	
        /* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、时钟源：
               HSE=8M,PLL=144M,AHB=144M,APB1=36M,APB2=72M,ADC CLK=144M/16,ADC 1M CLK=HSE/8,DMA CLK=144M。
        2、中断：
               ADC1注入转换结果完成中断打开，优先级1。
               中断处理接收注入转换结果到ADC_InjectedConvertedValueTab[32]数组。
        3、端口配置：
                - PC2选择为模拟功能ADC1转换通道
                - PC3选择为模拟功能ADC1转换通道
                - PA6选择为模拟功能ADC1转换通道
                - PA3选择为模拟功能ADC1转换通道
                - PE11选择为外部EXTI事件上升沿触发
                - PB15选择为外部EXTI事件上升沿触发
        4、DMA：
               DMA1_CH1通道回环模式搬运64个半字的ADC1规则通道转换结果到ADC_RegularConvertedValueTab[64]数组。
        5、ADC：
               ADC1规则通道独立工作模式、扫描间断模式、EXTI11触发、12位数据右对齐，转换通道PC2和PC3的模拟电压数据。
               ADC1注入通道独立工作模式、扫描模式、EXTI15触发、12位数据右对齐，转换通道PA6和PA3的模拟电压数据。

        /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将变量ADC_RegularConvertedValueTab[64],ADC_InjectedConvertedValueTab[32]添加到watch窗口观察。
        2、通过PE11给上升沿可以触发规则通道数据采样，PB15给上升沿可以触发注入通道数据采样。

4、注意事项
        1、当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8)可以配置为HSE或者HSI。
        2、当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)只能配置为HSI。