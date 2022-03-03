1、功能说明

	1、I2S 通过外部decode进行音频的播放


2、使用环境

	软件开发环境：
        IDE工具：NucleiStudio IDE for C/C++ 2021-02
    
    硬件环境：
        开发板 CM32M4xxR_LQFP128_STB + 六类接口功能扩展板

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        1、SystemClock：144MHz
        2、GPIO：I2S3（WS--PD8、SCK--PD9、 MOSI--PD12、 MCLK--PC7）,
                 I2C3（SCL--PC0、SDA--PC1）
	3、中断：I2S3 中断入口函数SPI3_IRQHandler


	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.将耳机插到耳机插孔中，可以听到声音的播放

4、注意事项
	无