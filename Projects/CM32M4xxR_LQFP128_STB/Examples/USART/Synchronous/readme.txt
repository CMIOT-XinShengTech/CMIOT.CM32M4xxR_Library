1、功能说明

        1、该测例演示了USARTy（同步模式）与SPIy间通过查询检测标识实现的基础通信。
        2、首先，通过TXC检测标志，USARTy发送TxBuffer1数据至SPIy，而SPIy接收数据，则查询RNE检测标志，接收的数据存至RxBuffer2。
        随后，SPIy通过查询TE检测标志，发送TxBuffer2数据至USARTy。USARTy则利用RXDNE检测标志接收数据，将其存入RxBuffer1。
        最后，分别比较两组收、发数据，比较结果存入TransferStatus1变量和TransferStatus2变量。
        3、USARTy和SPIy可以是USART1和SPI1、USART3和SPI1或USART2和SPI2。

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
                - 时钟使能
                - 时钟极性：不对外发送时保持高电平
                - 时钟相位：在第二个时钟边沿采样第一个数据
                - 最后一位时钟脉冲：最后一位数据的时钟脉冲从CK输出

        3、SPI配置如下：
                - 方向 = “双线双向”模式
                - 模式 = 从模式
                - 数据大小 = 8位数据帧
                - CPOL = 空闲状态时，时钟保持高电平
                - CPHA = 数据采样从第二个时钟边沿开始
                - NSS = 启用软件从设备管理
                - 第1位 = 第1位为LSB

        4、USART引脚连接如下：
                - USART1_Tx.PB6    <------->   SPI1_MOSI.PA7
                - USART1_Rx.PB7   <------->   SPI1_MISO.PA6
                - USART1_Clk.PA8   <------->   SPI1_SCK.PA5     
                或
                - USART3_Tx.PB10   <------->   SPI1_MOSI.PA7
                - USART3_Rx.PB11   <------->   SPI1_MISO.PA6
                - USART3_Clk.PB12  <------->   SPI1_SCK.PA5
                或
                - USART2_Tx.PA2    <------->   SPI2_MOSI.PB15
                - USART2_Rx.PA3    <------->   SPI2_MISO.PB14
                - USART2_Clk.PA4   <------->   SPI2_SCK.PB13

        /* 描述Demo的测试步骤和现象 */
        1、将PB6的拨码开关设置为ON。
        2、编译后打开调试模式。
        3、依次查看变量TransferStatus1和TransferStatus2，其中，PASSED为测试通过，FAILED为测试异常。

4、注意事项
        无。