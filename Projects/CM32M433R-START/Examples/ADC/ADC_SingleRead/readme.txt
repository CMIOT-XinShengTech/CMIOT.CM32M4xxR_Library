1、功能说明

        1、ADC1采样转换PA6 PC2引脚的模拟电压，ADC2采样转换PA7 PC3引脚的模拟电压，
        ADC3采样转换PE7 PE9引脚的模拟电压，ADC4采样转换PE8 PE14引脚的模拟电压。
        2、采用软件触发一次，采集一次的方式。

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板 */
        CM32M433R-START

3、使用说明
	
        /* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、时钟源：
               HSE=8M,PLL=144M,AHB=144M,APB1=36M,APB2=72M,ADC CLK=144M/16,ADC 1M CLK=HSE/8
        2、端口配置：
                - PA6选择为模拟功能ADC1转换通道
                - PC2选择为模拟功能ADC1转换通道
                - PA7选择为模拟功能ADC2转换通道
                - PC3选择为模拟功能ADC2转换通道
                - PE7选择为模拟功能ADC3转换通道
                - PE9选择为模拟功能ADC3转换通道
                - PE8选择为模拟功能ADC4转换通道
                - PE14选择为模拟功能ADC4转换通道
        3、ADC：
                - ADC1独立工作模式、软件触发转换、12位数据右对齐，转换PA6 PC2的模拟电压数据
                - ADC2独立工作模式、软件触发转换、12位数据右对齐，转换PA7 PC3的模拟电压数据
                - ADC3独立工作模式、软件触发转换、12位数据右对齐，转换PE7 PE9的模拟电压数据
                - ADC4独立工作模式、软件触发转换、12位数据右对齐，转换PE8 PE14的模拟电压数据

        /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将变量ADC1ConvertedValue,ADC2ConvertedValue,ADC3ConvertedValue,ADC4ConvertedValue添加到watch窗口观察。
        2、通过改变PC0,PC1,PC2,PC3,PD10,PD11,PD12,PD13引脚的电压，可以看到转换结果变量同步改变。

4、注意事项
        1、当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8)可以配置为HSE或者HSI。
        2、当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)只能配置为HSI。