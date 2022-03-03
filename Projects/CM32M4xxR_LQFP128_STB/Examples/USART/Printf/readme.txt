1、功能说明

        1、该测例演示了USARTx与PC间通过查询检测标识实现的基础通信。
        2、重定向printf函数至USARTx，并使用printf函数输出消息至终端。
        3、USARTx可以是USART1或USART2。

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板 */
        CM32M4xxR_LQFP128_STB

3、使用说明
    
        /* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、USART配置如下：
                - 波特率 = 115200 baud
                - 字长 = 8数据位
                - 1停止位
                - 校验控制禁用
                - 硬件流控制禁用（RTS和CTS信号）
                - 接收器和发送器使能
        3、USART引脚连接如下：
                - USART1_Tx.PB6 
                或
                - USART2_Tx.PA2

        /* 描述Demo的测试步骤和现象 */
        1、将PB6的拨码开关设置为ON；
        2、编译后下载程序；
        3、复位运行，查看串口打印信息：
               打印信息为 USART Printf Example: retarget the C library printf function to the USART

4、注意事项
        由于BSP/Source/log.c中也有重定向函数_put_char，因此需要在编译前排除log.c（已在.cproject文件中设置，在eclipse中可直接编译）。