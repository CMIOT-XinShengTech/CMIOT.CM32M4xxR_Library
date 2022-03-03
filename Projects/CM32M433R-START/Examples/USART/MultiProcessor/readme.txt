1、功能说明

        1、该测例演示了如何使用USART多处理器模式。
        2、首先，分别设置USARTy和USARTz的地址为0x1和0x2。USARTy连续给USARTz发送字符0x33。USARTz收到0x33，便翻转LED1、LED2和LED3的引脚。
        一旦KEY1_INT_EXTI_LINE线检测到上升沿，则产生EXTI0中断，在EXTI0_IRQHandler中断处理函数中(the ControlFlag = 0)，USARTz进入静默模式。
        在静默模式中，LED引脚停止翻转，直到KEY1_INT_EXTI_LINE线再次检测到上升沿(the ControlFlag = 1)。
        在EXTI0_IRQHandler中断处理函数中，USARTy发送地址0x102唤醒USARTz。LED引脚重新启动翻转。
        3、USARTy和USARTz可以是USART1和USART2、USART3和UART4或UART6和UART7。

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板 */
        CM32M433R-START

3、使用说明
    
        /* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、USARTy配置如下：
                - 波特率 = 115200 baud
                - 字长 = 9数据位
                - 1停止位
                - 校验控制禁用
                - 硬件流控制禁用（RTS和CTS信号）
                - 接收器和发送器使能  
    
        3、USART引脚连接如下：
                - USART5_Tx.PB13    <------->   USART6_Rx.PB1
                - USART5_Rx.PB14    <------->   USART6_Tx.PB0 

        /* 描述Demo的测试步骤和现象 */
        1、编译后下载程序复位运行。
        2、观察LED1~3是否处于闪烁状态。
        3、按WKUP键，观察LED1~3是否停止闪烁。
        4、再次按WKUP键，观察LED1~3是否恢复闪烁。

4、注意事项
        无。