1、功能说明

        1、该测例演示了开发板1和开发板2间实现串行IrDA低功耗模式红外解码功能的基础通信。
        2、首先，板1的USARTy传送TxBuffer1数据至IrDA Transmitter，IrDA Transmitter通过IrDA发送数据至IrDA Receiver，IrDA Receiver再将数据传送至板2的USARTy。
        随后，比较接收数据与发送数据，比较结果存入TransferStatus变量。

2、使用环境

        /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：NucleiStudio IDE for C/C++ 2021-02

        /* 开发板 */
        CM32M4xxR_LQFP128_STB、六类接口功能扩展板

3、使用说明

        /* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：8MHz
        2、USART配置如下：
                - 波特率 = 9600 baud
                - 字长 = 8数据位
                - 1停止位
                - 校验控制禁用
                - 硬件流控制禁用（RTS和CTS信号）
                - 接收器和发送器使能
                - IrDA模式使能且设置为低功耗模式
    
        3、USART引脚连接如下（将六类接口功能扩展板板接在CM32M4xxR_LQFP128_STB板上即可，无需接线）：
                - 板1的USART1_Tx.PA9    <------->    IrDA Transmitter
                - 板2的USART1_Rx.PA10   <------->    IrDA Receiver

        /* 描述Demo的测试步骤和现象 */
        1、板1和板2分别接上六类接口功能扩展板，保持两个板子上的红外管正对。
        2、main.h中注掉IrDA_Receiver，定义IrDA_Transmitter，编译后下载程序到板1（板1作为发送端）。
        3、main.h中注掉IrDA_Transmitter，定义IrDA_Receiver，编译后下载程序到板2（板2作为接收端），并打开调试模式。
        4、板2运行调试程序，板1和板2的红外管对上，板1进行复位后，查看变量TransferStatus，其中，PASSED为测试通过，FAILED为测试异常。

4、注意事项
        无。