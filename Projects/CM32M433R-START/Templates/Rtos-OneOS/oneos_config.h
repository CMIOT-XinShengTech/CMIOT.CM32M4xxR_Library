#ifndef __ONEOS_CONFIG_H__
#define __ONEOS_CONFIG_H__

#define BOARD_LONGAN_NANO
#define ARCH_RISCV
#define ARCH_RISCV32
#define ARCH_RISCV_BUMBLEBEE

/* Kernel */

#define OS_NAME_MAX_15
#define OS_NAME_MAX 15
#define OS_ALIGN_SIZE 4
#define OS_TASK_PRIORITY_MAX 32
#define OS_MAX_CNT_PENDING_READY_TASK_64
#define OS_MAX_CNT_PENDING_READY_TASK 64
#define OS_USING_ROUNDROBIN
#define OS_TICK_PER_SECOND 100
#define OS_TASK_NULL_AS_SELF
#define OS_MAIN_TASK_STACK_SIZE 2048
#define OS_MAIN_TASK_PRIORITY 1
#define OS_USING_HOOK
#define OS_USING_IDLE_HOOK
#define OS_IDLE_HOOK_LIST_SIZE 4
#define OS_IDLE_TASK_STACK_SIZE 512
#define TIME_SLICE_IDLE_TASK 32
#define OS_USING_TIMER_SOFT
#define OS_TIMER_TASK_PRIO 2
#define OS_TIMER_TASK_STACK_SIZE 1024
#define OS_USING_WORKQUEUE
#define OS_USING_SYSTEM_WORKQUEUE
#define OS_SYSTEM_WORKQUEUE_STACK_SIZE 2048
#define OS_SYSTEM_WORKQUEUE_PRIORITY 8

/* Task communication */

#define OS_USING_SEMAPHORE
#define OS_SEM_LIMIT
#define OS_USING_COMPLETION
#define OS_USING_MUTEX
#define OS_USING_EVENT
#define OS_USING_QUEUE
#define OS_QUEUE_THRESHOLD
#define OS_QUEUE_EVT_NOTIFY
#define OS_QUEUE_VAR_SIZE
#define OPTI_DIRECT_SND_TO_WAIT_TASK
#define OS_USING_MAILBOX
#define OS_USING_MESSAGEQUEUE
#define OS_USING_DATAQUEUE
#define DATAQUEUE_IPC_FLAG_FIFO
#define OS_DATA_QUEUE_IPC_FLAG 0
#define OS_USING_WAITQUEUE
/* end of Task communication */

/* Memory management */

#define OS_USING_ALG_FIRSTFIT
#define OS_SYS_SINGLE_HEAP_WITH_ALG_FIRSTFIT
#define OS_USING_HEAP
#define OS_USING_MEM_SMALL
#define OS_USING_MULTI_HEAP
#define OS_USING_MEM_POOL
/* end of Memory management */

/* Kernel device object */

//#define OS_USING_DEVICE
//#define OS_USING_CONSOLE
#define OS_CONSOLE_DEVICE_NAME "uart0"
/* end of Kernel device object */

/* Enable assert */

#define OS_USING_ASSERT
/* end of Enable assert */
#define EVR_RTX_DISABLE

/* Kernel debug */

#define OS_USING_KERNEL_DEBUG
#define KLOG_GLOBAL_LEVEL_WARNING
#define KLOG_GLOBAL_LEVEL 1
#define KLOG_USING_COLOR
/* end of Kernel debug */
/* end of Kernel */

/* C standard library */

#define OS_USING_LIBC
/* end of C standard library */

/* Osal */

/* POSIX compatibility layer */

/* end of POSIX compatibility layer */

/* RT-Thread compatibility layer */

/* end of RT-Thread compatibility layer */

/* CMSIS compatibility layer */

/* end of CMSIS compatibility layer */

/* FreeRTOS compatibility layer */

/* end of FreeRTOS compatibility layer */
/* end of Osal */

/* Drivers */

/* HAL */

#define SOC_FAMILY_CM32M4XXR
#define SOC_SERIES_CM32M4XXR
#define SOC_CM32M4XXR
#define BSP_USING_PIN
#define BSP_USING_UART
#define OS_USING_USART0
#define OS_USING_USART1
#define BSP_USING_I2C
#define BSP_USING_I2C0
#define BSP_USING_I2C1

/* Select SPI port */

#define BSP_USING_SPI0
#define BSP_USING_SPI1
/* end of Select SPI port */
#define BSP_USING_FLASH
/* end of HAL */

/* Audio */

/* end of Audio */

/* MISC */

//#define OS_USING_PUSH_BUTTON
//#define OS_USING_LED
/* end of MISC */

/* PIN */

//#define OS_USING_PIN
#define OS_PIN_MAX_CHIP 1
/* end of PIN */

/* Serial */

#define OS_USING_SERIAL
#define OS_SERIAL_RX_BUFSZ 64
#define OS_SERIAL_TX_BUFSZ 64
/* end of Serial */

/* WDG */

/* end of WDG */

/* RTC */

/* end of RTC */

/* CAN */

/* end of CAN */

/* I2C */

#define OS_USING_I2C
#define BSP_USING_I2C_AT24CXX
#define BSP_AT24CXX_I2C_BUS_NAME "i2c1"
#define BSP_AT24CXX_I2C_ADDR 0x50
/* end of I2C */

/* SPI */

#define OS_USING_SPI
#define BSP_USING_AT45DBXX
#define BSP_AT45DBXX_SPI_BUS "spi1"
#define BSP_AT45DBXX_SPI_CS 28
/* end of SPI */

/* FAL */

#define OS_USING_FAL
/* end of FAL */

/* RTT */

/* end of RTT */

/* Timer */

/* end of Timer */

/* HwCrypto */

/* end of HwCrypto */

/* SDIO */

/* end of SDIO */

/* WLAN */

/* end of WLAN */

/* Graphic */

/* end of Graphic */

/* Touch */

/* end of Touch */

/* Sensors */

/* end of Sensors */

/* USB */

/* end of USB */

/* Infrared */

/* end of Infrared */

/* Low power manager */

/* end of Low power manager */

/* NAND */

/* end of NAND */

/* DMA */

#define OS_USING_DMA
/* end of DMA */
#define OS_USING_DRIVERS_SAMPLES
#define OS_FAL_TEST_DEMO
/* end of Drivers */

/* Components */

/* AI */

/* chaoTTS */

/* end of chaoTTS */
/* end of AI */

/* Atest */

/* end of Atest */

/* BLE */

/* end of BLE */

/* Cloud */

/* Aliyun */

/* end of Aliyun */

/* AWS */

/* end of AWS */

/* CTWing */

/* MQTT */

/* end of MQTT */
/* end of CTWing */

/* Huawei */

/* end of Huawei */

/* OneNET */

/* MQTT kit */

/* end of MQTT kit */

/* NB-IoT kit */

/* end of NB-IoT kit */

/* EDP */

/* end of EDP */
/* end of OneNET */
/* end of Cloud */

/* Diagnose */

/* end of Diagnose */

/* Dlog */

/* end of Dlog */

/* FileSystem */

/* end of FileSystem */

/* Gadget */

/* openCC */

/* end of openCC */
/* end of Gadget */

/* GUI */

/* end of GUI */

/* Network */

/* LwIP */

/* end of LwIP */

/* Molink */

/* end of Molink */

/* Protocols */

/* LWM2M */

/* end of LWM2M */

/* CoAP */

/* end of CoAP */

/* MQTT */

/* end of MQTT */

/* Websocket */

/* end of Websocket */

/* Httpclient */

/* end of Httpclient */
/* end of Protocols */

/* Socket */

/* end of Socket */
/* end of Network */

/* OTA */

/* Fota by CMIOT */

/* end of Fota by CMIOT */
/* end of OTA */

/* OnePos */

/* end of OnePos */

/* Ramdisk */

/* end of Ramdisk */

/* Security */

/* end of Security */

/* Shell */

//#define OS_USING_SHELL
#define SHELL_TASK_NAME "tshell"
#define SHELL_TASK_PRIORITY 20
#define SHELL_TASK_STACK_SIZE 2048
#define SHELL_USING_HISTORY
#define SHELL_HISTORY_LINES 5
#define SHELL_USING_DESCRIPTION
#define SHELL_CMD_SIZE 80
#define SHELL_ARG_MAX 10
/* end of Shell */
/* end of Components */

/* Thirdparty */

/* MicroPython */

/* end of MicroPython */

/* cJSON */

/* end of cJSON */

/* Easyflash */

/* end of Easyflash */

/* Netutils */

/* NTP */

/* end of NTP */
/* end of Netutils */

/* WebClient */

/* end of WebClient */
/* end of Thirdparty */

/* Boot Config */

/* end of Boot Config */

/* Debug */

//#define OS_DEBUG
#define OS_DEBUG_LOG_WITH_FUNC_LINE
#define LOG_BUFF_SIZE_256
#define OS_LOG_BUFF_SIZE 256
/* end of Debug */

#endif /* __ONEOS_CONFIG_H__ */

