1、功能说明

        1、该测例演示了USARTy与USARTz间使用硬件流控制实现的基础通信。
        2、板1的USARTy发送TxBuffer1至板2的USARTz，USARTz间隔6毫秒左右的时间依次接收每个数据存至RxBuffer2。
        随后，分别比较接收数据与发送数据，比较结果存入TransferStatus变量。
        3、USARTy和USARTz可以是USART1和USART2。

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板两块 */
        CM32M4xxR_LQFP128_STB(板1)
        CM32M4xxR_LQFP128_STB(板2)

3、使用说明
    
        /* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、USART配置如下：
                - 波特率 = 115200 baud
                - 字长 = 8数据位
                - 1停止位
                - 校验控制禁用
                - 硬件流控制使能（RTS和CTS信号）
                - 接收器和发送器使能
    
        3、USART引脚连接如下：
                - USART1_Tx.PB6(板1)    <------->   USART2_Rx.PA3(板2)
                - USART1_CTS.PA11(板1)   <------->   USART2_RTS.PA1(板2)

        /* 描述Demo的测试步骤和现象 */
        1、将PB6的拨码开关设置为ON。
        2、编译Transmit_CTS，下载程序到板1。
        3、编译Receive_RTS，下载程序到板2，并打开调试模式。
        4、运行板2的调试程序到等待接收数据的位置，复位板1，将变量TransferStatus添加到watch窗口观察，其中，PASSED为测试通过，FAILED为测试异常。

4、注意事项
        USART_Tx需外接上拉电阻(PB6已接)。