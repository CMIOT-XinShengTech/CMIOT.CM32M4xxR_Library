**应用指南**

**CM32M4xxR系列芯片**

**快速上手指南**

**V1.0**

目录

[一、概述](#_Toc86307366)

[二、SDK介绍](#_Toc86307367)

[三、开发板简介](#_Toc86307368)

[四、开发环境搭建](#_Toc86307369)

[4.1 NucleiStudio IDE下载和安装](#41-nucleistudio-ide下载和安装)

[4.2 调试工具配置](#42-调试工具配置)

[五、运行参考例程](#五运行参考例程)

[5.1 工程导入](#51-工程导入)

[5.2 编译](#52-编译)

[5.3 调试](#53-调试)

[5.4 下载](#54-下载)

[七、参考文档说明](#七参考文档说明)

[八、版本历史](#_Toc86307378)

# 一、概述

CM32M4xxR是芯昇科技RSIC-V内核MCU系列，该系列采用芯来N308内核，并搭载丰富的片上外设功能。本文档详细描述了CM32M4xxR系列MCU的SDK内容，并介绍了基于CM32M4xxR-LQFP128开发板进行开发环境搭建、应用样例运行等过程，以帮助用户快速掌握MCU的开发方法。

# 二、SDK介绍

SDK主要包括以下目录：

![](media/33718299157c21af3bb97b9513556247.png)

图 1 SDK目录结构

-   Board：开发板资料，包括原理图、PCB文件。

-   CMIOT.CM32M4xxR_Library:芯片软件库，包括标准驱动代码、参考例程以及一些工程模板。

-   Doc:包括芯片《芯片用户手册》、《芯片数据手册》、开发板使用指南及其他软件说明文档。

-   Tools:包括芯片支持包Support Pack工具和下载工具。

# 三、开发板简介

![](media/21c1d8a12ca4e3b4b783913fc9fa8226.png)

图 2开发板布局

开发板将所有的功能接口都连接到了排针上。提供有10Pin
JTAG烧写调试接口；两个触摸按键TSC；一个复位按键，一个Wakeup唤醒按键；一个触发RTC时间戳按键。

开发板可直接通过Micro_USB口供电与打印串口Log。

更详细的开发板硬件使用说明请见《CM32M4xxR-LQFP128开发板使用指南》。

# 四、开发环境搭建

## 4.1 NucleiStudio IDE下载和安装

Nuclei Studio
IDE为CM32M4xxR开发使用的主要IDE，该IDE为芯来基于开源的Eclipse框架开发的针对芯来处理器内核产品的集成开发工具。访问芯来科技官网下载最新版本的Nuclei
Studio IDE：<https://www.nucleisys.com/download.php>

![](media/7aaae9aa66a0d08307b147a159e2d7db.png)

图 3 Nuclei Studio IDE下载

Nuclei Studio
IDE为免安装程序，下载完成后打开目录，直接双击可执行文件（NucleiStudio.exe）即可。以下文档基于Nuclei
Studio IDE 2021-02版本进行说明。

![](media/013536de4809762ae537326c5a8f087a.png)

图 4 双击启动Nuclei Studio

第一次启动IDE，将会弹出对话框要求设置Workspace目录路径，该目录将会用于存放后续创建的项目工程文件。设置完成后点击Launch，将会启动Nuclei
Studio IDE。

![](media/9821967881c4cc8d6b695c937e54df0b.png)

图 5 设置workspace目录

关于IDE的详细使用说明可以参考《Nuclei Studio User Guide》。

## 4.2 调试工具配置

CM32M4xxR支持蜂鸟调试器和JLink调试器进行程序下载和调试，用户可以根据自己的调试工具选择一种方式。

![](media/3ae1ea5a5c96ed3c0216d826a0335abe.png)

图 6 JLink调试器和蜂鸟调试器

注意：目前CM32M4xxR-LQFP128开发板仅预留了JLink调试接口，如使用蜂鸟调试器需要飞线将调试器的TCK、TMS、TDO、TDI、VCC、GND信号与开发板JTAG插座的对应信号进行连接。

**使用JLink调试器：**访问Segger官网下载并安装JLink驱动。

注意：JLinkV9及以下版本不支持RSIC-V，推荐使用JLink V10以上版本。

**使用蜂鸟调试器 +
OpenOCD：**访问芯来官网下载蜂鸟调试器驱动<https://nucleisys.com/theme/package/HBird_Driver.exe>
并安装。将蜂鸟调试器接入PC的USB接口，检查windows设备管理器可以看到一个USB Serial
Port（COMxx）设备，表示安装完成。蜂鸟调试器可以将UART转换成USB，该接口可以用于调试输出接口。

然后双击SDK Tools目录下“CM32M4xxR Support
Pack.exe”安装文件，用户需要根据自己的调试方式在安装界面中进行选择，如使用JLink则勾选“安装JLink支持包”，并填写JLink安装目录；如使用蜂鸟+openocd则勾选“安装OpenOCD支持包”，并填写Nuclei
Studio IDE的目录。完成后点击下一步直至安装完成。

![](media/338a839c5ab129018c6cad069a3c08b0.png)

图 7 安装CM32M4xxR调试工具Pack包

# 五、运行参考例程

## 5.1 工程导入

1、打开Nuclei Studio IDE，选择菜单栏 File-\>Import,打开工程导入向导。

![](media/b08ad2898f563dd751ce027d0728841a.png)

2、选择Projects from Folder or Archive,然后点击next。

![](media/b92ef033b63695fbda4bfdd6c80eaab6.png)

3、点击Directory，选择CM32M4xxR_SDK_1.0.0\\CMIOT.CM32M4xxR_Library\\Projects\\CM32M4xxR_LQFP128_STB\\Examples\\GPIO\\LedBlink目录。之后会观察到Folder里会识别并显示LedBlink的Eclipse
project。点击Finish。

![](media/02c933a0514d78cfd8e6e78341900a90.png)

4、此时会在Project Explorer中看到LedBlink工程被导入并且打开。工程导入完成。

![](media/f919a7f1f5cd68eb7151371e1fad5eb7.png)

## 5.2 编译

1、检查编译配置，右键点击工程选择Properties打开工程属性界面。

2、在工程属性界面中选择C/C++
Build-\>Settings,可以查看和修改工程的相关编译配置。由于样例工程中已经进行过配置，此处可以不进行任何修改。

注：此界面为主要编译配置界面，会经常用到，用户可以查阅《Nuclei Studio User
Guide》的4.3.3章节了解各配置参数的详细含义。

![](media/5750a36e5b40727fbaf5f33c9a46b60c.png)

3、选择菜单栏Project-\>Build All进行工程编译，编译完成后，显示如下：

![](media/c9d86b5f8da8eb99060d49d8e4b079ff.png)

## 5.3 调试

1、检查调试配置。菜单栏选择Run-\>Debug
Configurations打开调试配置界面。样例工程中已经完成了调试配置，用户可以不用修改。

如果用户使用JLink进行调试，调试配置如下：

![](media/617644df034ac001d3ce7d1439dace95.png)

图 8 JLink调试配置--main

![](media/6cbfb553a879917f5a5c1bfdb2262f24.png)

图 9 JLink调试配置--Debugger

![](media/02ae95f412749b00531199905b7c9cad.png)

图 10 JLink调试配置—Startup

![](media/c69d8f0a3a09f82aa402f69b1fc16aba.png)

图 11 JLink调试配置--SVD Path

如果用户使用蜂鸟调试器+OpenOCD的方式进行调试，调试配置如下：

![](media/3dbfbcd42a513abaa2b1d8acc838f944.png)

图 12 OpenOCD调试配置—Main

![](media/8af46466bf140c3ca9c1bc9bfc1b1417.png)

图 13 OpenOCD调试配置—Debugger

![](media/cce96d2f81fa8c3072360b09120f6ae5.png)

图 14 OpenOCD调试配置—Startup

![](media/c839899039039caf510e84878049207f.png)

图 15 OpenOCD调试配置--SVD Path

2、检查开发板供电和调试器连接，然后点击Debug
Configurations，选择对应的调试配置，然后点击下面的Debug按钮，即可启动工程调试。

![](media/3c9b7c531a797481036a3eaec250c321.png)

3、如上图，1号位置为调试控制栏；2号位置为Registers窗口，可以查看RSIC-V内核的寄存器数值；3号位置为Peripherals窗口，可以选择查看MCU各个片上外设的寄存器，勾选其中一个外设以后，就会在Memory窗口中显示该外设的寄存器内容。以上窗口可以通过菜单栏Windows-\>Show
View中找到并打开。其他如变量查看、断点增删等内容不在此赘述，用户可以参考《Nuclei
Studio User Guide》。

4、点击调试控制栏里的运行按钮，然后启动程序运行，可以观察到CM32M4xxR-LQFP128开发板上三个LED进行闪烁。每个样例工程的目录下都配套一个readme.txt文件，该文件介绍了样例工程的功能说明、使用方法、注意事项等内容，建议详细阅读。

## 5.4 下载

Nuclei Studio
IDE没有单独的下载按钮功能，在启动调试的过程中，IDE会根据链接文件的配置将程序下载到特定的位置，如将程序烧写到flash，请在编译配置选项界面选择gcc_cm32m4xxr_flashxip.ld文件，并修改DOWNLOAD_MODE的宏值为0。

![](media/61c271f9a7b1824e8827f80e2590dc76.png)

图 16 选择链接脚本文件

![](media/824845ba4187dd6f89ac7c52bc3ce32d.png)

图 17 修改下载模式

另外程序还可以通过SDK中提供的下载工具进行下载，具体下载方式请查阅Tools\\CM32M4xxR
DownLoad Tool V1.0\\Help\\目录下的《CM32M4xxR Download Tool 使用指南》

# 七、参考文档说明

| 文档名称                          | 内容说明                                  | 获取方式                                                                                |
|-----------------------------------|-------------------------------------------|-----------------------------------------------------------------------------------------|
| 芯片手册                          | 技术手册、数据手册、应用笔记              | SDK/Doc目录下                                                                           |
| 驱动总体说明                      | 总体介绍芯片软件库Drivers目录内容         | SDK/Doc目录下                                                                           |
| 应用样例总体说明                  | 总体介绍芯片软件库Projects目录内容        | SDK/Doc目录下                                                                           |
| 从Cortex-M4到芯来N308应用移植说明 | 介绍应用移植注意点                        | SDK/Doc目录下                                                                           |
| 开发板使用指南                    | 介绍CM32M4xxR-LQFP128开发板及其扩展板     | SDK/Doc目录下                                                                           |
| 中断应用指南                      | 结合SDK介绍中断系统特点及使用凡是         | SDK/Doc目录下                                                                           |
| 硬件设计文件                      | CM32M4xxR-LQFP128开发板及其扩展板的原理图 | SDK/Board目录下                                                                         |
| CM32M4xxR Download Tool 使用指南  | 下载工具使用说明                          | Tools\\CM32M4xxR DownLoad Tool V1.0\\Help目录下                                         |
| Nuclei_N级别指令架构手册          | 内核架构说明                              | <https://www.riscv-mcu.com/quickstart-doc-u-nuclei_n_isa.html>                          |
| RISC-V ISA Specification          | RSIC-V指令集架构说明                      | <https://riscv.org/technical/specifications/>                                           |
| Nuclei Studio User Guide          | IDE使用说明                               | <https://www.nucleisys.com/upload/files/doc/nucleistudio/Nuclei_Studio_User_Guide.pdf>  |
| NMSIS documentation               | NMSIS参考文档                             | <https://doc.nucleisys.com/nmsis/>                                                      |
| GNU工具链相关文档                 | 工具链相关说明文档                        | https://gcc.gnu.org/onlinedocs/9.2.0/                                                   |

# 八、版本历史

| **版本** | **日期** | **修改内容** |
|----------|----------|--------------|
| V1.0     | 20211012 | 新建         |
|          |          |              |
|          |          |              |
