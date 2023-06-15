1、功能说明

	SD卡挂载了FAT32系统，用来展示SD卡挂载文件系统之后的操作
	用例先在SD卡的文件系统里创建文件：first.txt，首先读取文件里的文本
	然后写入文本：XinSheng Tech SD Card I/O Example via SPI，并关闭
	最后再次打开文件：first.txt，读取文件里的文本并打印

2、使用环境

	/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
	IDE工具：NucleiStudio IDE for C/C++ 2022-01
	
	/* 开发板 */
	CM32M433R-START + CM32M433R-EXTEND

3、使用说明
	1、下载程序
	2、打开串口工具，复位运行程序可以看到成功打印写入后的文本信息
	3、多次复位可以看到每次打印的文本信息在增加，每次增加一行XinSheng Tech SD Card I/O Example via SPI文本的显示
	
4、注意事项
	需要在sd卡创建first.txt文件，写入初始内容后插入sd卡槽中