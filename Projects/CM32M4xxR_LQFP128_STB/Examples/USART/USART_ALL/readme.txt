1、功能说明

        1、该测例演示了USART1与USART2间通过DMA实现半双工模式的通信,USART3作为log单独输出，USART1、
        USART2和USART3：波特率配置115200，数据位8位，无校验位；USART4和USART5通过DMA收发通信
        （UART4的DMA收发完成中断触发，UART5的DMA收发完成轮询查询），波特率配置921600，数据位8位，
        偶校验位；UART6和UART7一个中断收发，一个轮询收发，波特率38400，数据位9位，奇校验位。
        2、首先，DMA传输TxBuffer1数据至USART1发送数据寄存器，随后数据发送至USART2。
        USART2接收从DMA传来的数据，存至RxBuffer2。比较收、发数据，比较结果存入TransferStatus1变量。
        随后，将TxBuffer2数据传输至USART2发送数据寄存器，随后数据发送至USART1。
        USART1接收从接收寄存器传来的数据，存至RxBuffer1。比较收、发数据，比较结果存入TransferStatus2变量。
        通过log口打印比较结果
        3、DMA传输TxBuffer4数据至USART4发送数据寄存器，随后数据发送至USART5。DMA传输完成产生中断。
        USART5接收从DMA传来的数据，存至RxBuffer5，轮询DMA传输完成状态。比较收、发数据，比较结果存入TransferStatus4变量。
        DMA传输TxBuffer5数据至USART5发送数据寄存器，随后数据发送至USART4。轮询DMA传输完成状态。
        USART4接收从DMA传来的数据，存至RxBuffer4，DMA传输完成产生中断。比较收、发数据，比较结果存入TransferStatus5变量。
        4、USART6通过中断的方式在发送中断中将数据发送给USART7，USART7通过中断的方式在接收中断中将数据接收存储.
        比较收、发数据，比较结果存入TransferStatus6变量。
        USART7通过轮询的方式在查询发送状态正确时将数据发送给USART7，USART7通过轮询的方式在查询有数据接收时将数据接收存储.
        比较收、发数据，比较结果存入TransferStatus7变量。

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板 */
        CM32M4xxR_LQFP128_STB

3、使用说明
    
        /* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、USART1和USART2配置如下：
                - 波特率 = 115200 baud
                - 字长 = 8数据位
                - 1停止位
                - 校验控制禁用
                - 硬件流控制禁用（RTS和CTS信号）
                - 发送器使能或接收器使能
                - 半双工模式使能
                - DMA发送或接收模式使能
          USART3配置如下：
                - 波特率 = 115200 baud
                - 字长 = 8数据位
                - 1停止位
                - 校验控制禁用
                - 硬件流控制禁用（RTS和CTS信号）
                - 发送器使能
                - 半双工模式禁能
          USART4和USART5配置如下：
                - 波特率 = 921600 baud
                - 字长 = 8数据位
                - 1停止位
                - 校验控制使能，偶校验
                - 硬件流控制禁用（RTS和CTS信号）
                - 发送器使能或接收器使能
                - 半双工模式禁能
                - DMA发送和或接收模式使能
          USART6和USART7配置如下：
                - 波特率 = 38400 baud
                - 字长 = 9数据位
                - 1停止位
                - 校验控制使能，奇校验
                - 硬件流控制禁用（RTS和CTS信号）
                - 发送器使能或接收器使能
                - 半双工模式禁能
    
        3、USART引脚连接如下：
                - USART1_Tx.PB6    <------->   USART2_Rx.PD5
                - USART3_Tx.PB10   <------->   log串口的RX
                - USART4_Tx.PC10   <------->   USART5_Rx.PB14
                - USART5_Tx.PB13   <------->   USART4_Rx.PC11
                - USART6_Tx.PB0    <------->   USART7_Rx.PG1
                - USART7_Tx.PB1    <------->   USART6_Rx.PG0

        /* 描述Demo的测试步骤和现象 */
        1、将PB6的拨码开关设置为ON。
        2、编译后打开调试模式。
        3、依次查看变量TransferStatus1、TransferStatus2、TransferStatus4、TransferStatus5、TransferStatus6、TransferStatus7，
        其中，PASSED为测试通过，FAILED为测试异常。

4、注意事项
        USART_Tx需外接上拉电阻(PB6已接)。
        #define LOG_ENABLE	0