#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "FreeRTOSConfig.h"

void task_LED1(void *param);
void task_LED2(void *param);
void task_LED3(void *param);

void app_main(void)
{
    xTaskCreate(task_LED1, "task1", 1024*2, NULL, 4, NULL);
    xTaskCreate(task_LED2, "task2", 1024*2, NULL, 3, NULL);
    xTaskCreate(task_LED3, "task3", 1024*2, NULL, 2, NULL);

}

//task1 handler or function
void task_LED1(void *param)
{
    while(1)
    {
        printf("-this is task1-\n");
        vTaskDelay(10000/portTICK_PERIOD_MS); // Delay of 10 second
    }
    vTaskDelete(NULL);
}



//task2 handler or function
void task_LED2(void *param)
{
    while(1)
    {
        printf("--this is task2--\n");
        vTaskDelay(1000/portTICK_PERIOD_MS); // Delay of 1 second
    }
    vTaskDelete(NULL);
    }
void task_LED3(void *param)
{
    while(1)
    {
        printf("---this is task3---\n");
        vTaskDelay(100/portTICK_PERIOD_MS); // Delay of 0.1 second
    }
    vTaskDelete(NULL);
}