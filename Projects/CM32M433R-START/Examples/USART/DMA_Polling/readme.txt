1、功能说明

        1、该测例演示了USARTy与USARTz间通过DMA实现的基础通信。
        2、首先，DMA传输TxBuffer1数据至USARTy发送数据寄存器，随后数据发送至USARTz。USARTz接收从DMA传来的数据，存至RxBuffer2。比较收、发数据，比较结果存入TransferStatus2变量。
        同时，DMA传输TxBuffer2数据至USARTz发送数据寄存器，随后数据发送至USARTy。USARTy接收从DMA传来的数据，存至RxBuffer1。比较收、发数据，比较结果存入TransferStatus1变量。   
        3、USARTy和USARTz可以是USART1和USART2、USART3和UART4或UART6和UART7。

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板 */
        CM32M433R-START

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
                - DMA发送模式和DMA接收模式使能
    
        3、USART引脚连接如下：
                - USART5_Tx.PB13    <------->   USART6_Rx.PB1
                - USART5_Rx.PB14    <------->   USART6_Tx.PB0 

        /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式。
        2、依次查看变量TransferStatus1和TransferStatus2，其中，PASSED为测试通过，FAILED为测试异常。

4、注意事项
        无。