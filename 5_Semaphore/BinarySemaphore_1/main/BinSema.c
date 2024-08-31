#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/semphr.h"

SemaphoreHandle_t xSemaphore = NULL;  //create a Semaphore Handle 

TaskHandle_t myTaskHandle = NULL;
TaskHandle_t myTaskHandle2 = NULL;

void Task_1(void *arg)
{
    while(1)
    {
        printf("Message Sent! [%ld] \n", xTaskGetTickCount());   //TickCount() will display the time that passed since application started.
        xSemaphoreGive(xSemaphore);    //to give a semaphore
        vTaskDelay(1000);  //delay of 1 second
    }
}

void Task2(void *arg)
{
    while(1)
    {
    /*portMAX_DELAY, wait in Blocked state for the semaphore to become available,it's wait until it gets
     flag from Semaphore.*/ 
     if(xSemaphoreTake(xSemaphore, portMAX_DELAY)) // take a semaphore. 
     {
      printf("Received Message [%ld] \n", xTaskGetTickCount());
     }
    }
}

void app_main(void)
{
   xSemaphore = xSemaphoreCreateBinary();
   xTaskCreate(Task_1, "Demo_Task", 4096, NULL, 10, &myTaskHandle);
   xTaskCreate(Task2, "Demo_Task2", 4096, NULL,10, &myTaskHandle2);
 }