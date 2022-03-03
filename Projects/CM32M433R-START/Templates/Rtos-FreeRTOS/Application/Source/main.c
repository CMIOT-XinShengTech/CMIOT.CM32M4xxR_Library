/*******************************************************************************
*
* COPYRIGHT(c) 2020, China Mobile IOT
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*	1. Redistributions of source code must retain the above copyright notice,
*	   this list of conditions and the following disclaimer.
*	2. Redistributions in binary form must reproduce the above copyright notice,
*	   this list of conditions and the following disclaimer in the documentation
*	   and/or other materials provided with the distribution.
*	3. Neither the name of China Mobile IOT nor the names of its contributors
*	   may be used to endorse or promote products derived from this software
*	   without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/

/**
 * @file main.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#include "FreeRTOS.h" /* Must come first. */
#include "queue.h"    /* RTOS queue related API prototypes. */
#include "semphr.h"   /* Semaphore related API prototypes. */
#include "task.h"     /* RTOS task related API prototypes. */
#include "timers.h"   /* Software timer related API prototypes. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "nuclei_sdk_soc.h"

#include "main.h"
#include "log.h"


/** @addtogroup CM32M4XXR_StdPeriph_Examples
 * @{
 */

/** @addtogroup USART_Printf
 * @{
 */

/**
 * @brief Main function
 */
#define mainSOFTWARE_TIMER_PERIOD_MS    pdMS_TO_TICKS(1000)
#define mainQUEUE_LENGTH                (1)

static void prvSetupHardware(void);
extern void idle_task(void);
static void vExampleTimerCallback(TimerHandle_t xTimer);

/* The queue used by the queue send and queue receive tasks. */
static QueueHandle_t xQueue = NULL;

static TaskHandle_t StartTask1_Handler;
static TaskHandle_t StartTask2_Handler;

void prvSetupHardware(void)
{
	log_init();
}

void start_task1(void* pvParameters);
void start_task2(void* pvParameters);

int main(void)
{
    TimerHandle_t xExampleSoftwareTimer = NULL;

    /* Configure the system ready to run the demo.  The clock configuration
    can be done here if it was not done before main() was called. */
    prvSetupHardware();

    xQueue = xQueueCreate(/* The number of items the queue can hold. */
                 mainQUEUE_LENGTH,
                 /* The size of each item the queue holds. */
                 sizeof(uint32_t));

    if (xQueue == NULL) {
        printf("Unable to create xQueue due to low memory.\n");
        while (1);
    }
    xTaskCreate((TaskFunction_t)start_task1, (const char*)"start_task1",
                (uint16_t)256, (void*)NULL, (UBaseType_t)2,
                (TaskHandle_t*)&StartTask1_Handler);

    xTaskCreate((TaskFunction_t)start_task2, (const char*)"start_task2",
                (uint16_t)256, (void*)NULL, (UBaseType_t)1,
                (TaskHandle_t*)&StartTask2_Handler);

    xExampleSoftwareTimer =
        xTimerCreate((const char*)"ExTimer", mainSOFTWARE_TIMER_PERIOD_MS,
                     pdTRUE, (void*)0, vExampleTimerCallback);

    xTimerStart(xExampleSoftwareTimer, 0);
    printf("Before StartScheduler\r\n");

    vTaskStartScheduler();

    printf("OS should never run to here\r\n");

    while (1);
}

void start_task1(void* pvParameters)
{
    int cnt = 0;
    printf("Enter to task_1\r\n");
    while (1) {
        printf("task1 is running %d.....\r\n", cnt++);
        vTaskDelay(200);
    }
}

void start_task2(void* pvParameters)
{
    int cnt = 0;
    printf("Enter to task_2\r\n");
    while (1) {
        printf("task2 is running %d.....\r\n", cnt++);
        vTaskDelay(200);
    }
}

static void vExampleTimerCallback(TimerHandle_t xTimer)
{
    /* The timer has expired.  Count the number of times this happens.  The
    timer that calls this function is an auto re-load timer, so it will
    execute periodically. */
    static int cnt = 0;
    printf("timers Callback %d\r\n", cnt++);
}

void vApplicationTickHook(void)
{
    // BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* The RTOS tick hook function is enabled by setting configUSE_TICK_HOOK to
    1 in FreeRTOSConfig.h.

    "Give" the semaphore on every 500th tick interrupt. */

    /* If xHigherPriorityTaskWoken is pdTRUE then a context switch should
    normally be performed before leaving the interrupt (because during the
    execution of the interrupt a task of equal or higher priority than the
    running task was unblocked).  The syntax required to context switch from
    an interrupt is port dependent, so check the documentation of the port you
    are using.

    In this case, the function is running in the context of the tick interrupt,
    which will automatically check for the higher priority task to run anyway,
    so no further action is required. */
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook(void)
{
    /* The malloc failed hook is enabled by setting
    configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.

    Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
    printf("malloc failed\n");
    while (1);
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName)
{
    /* Run time stack overflow checking is performed if
    configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected.  pxCurrentTCB can be
    inspected in the debugger if the task name passed into this function is
    corrupt. */
    printf("Stack Overflow\n");
    while (1);
}
/*-----------------------------------------------------------*/

extern UBaseType_t uxCriticalNesting;
void vApplicationIdleHook(void)
{
    // volatile size_t xFreeStackSpace;
    /* The idle task hook is enabled by setting configUSE_IDLE_HOOK to 1 in
    FreeRTOSConfig.h.

    This function is called on each cycle of the idle task.  In this case it
    does nothing useful, other than report the amount of FreeRTOS heap that
    remains unallocated. */
    /* By now, the kernel has allocated everything it is going to, so
    if there is a lot of heap remaining unallocated then
    the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
    reduced accordingly. */
}
