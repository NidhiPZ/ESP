
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t task_send_Handle = NULL;
TaskHandle_t task_receive_Handle = NULL;

 /*QueueHandle_t variable that can be used as a parameter to xQueueSend(), xQueueReceive(), etc.*/
QueueHandle_t queue_H;

void task_send(void *arg)
{
   char string_send[9];
   sprintf(string_send, "data 1");
   xQueueSend(queue_H,    /* handle to the queue on which the item is to be posted.*/
             (void *)string_send, /* A pointer to the item that is to be placed on the queue.*/
             100);

   printf("Send:  %s \n", string_send);

   sprintf(string_send, "data 2");
   xQueueSend(queue_H, (void *)string_send, 100);
   printf("Send:  %s \n", string_send);

   sprintf(string_send, "data 3");
   xQueueSend(queue_H, (void *)string_send, 100);
   printf("Send:  %s \n\n", string_send);

   while (1)
   {
      vTaskDelay(100);
   }
}

void task_receive(void *arg)
{
   char string_receive[9];
   while (1)
   {
      if ( xQueueReceive(queue_H, &(string_receive), 100 ))
      {
         printf("Received:  %s \n", string_receive);
      }
   }
}

void app_main()
{
   // Queue creation
   /*QueueHandle_t variable that can be used as a parameter to xQueueSend(), xQueueReceive(), etc.*/
   queue_H = xQueueCreate(5, 10);

   // Available
   printf("\nAvailable at the begining: %d \n\n", uxQueueSpacesAvailable(queue_H));

   // Write data to queue
   xTaskCreate(task_send, "task_send", 4096, NULL, 10, &task_send_Handle);
   vTaskDelay(1000);
   
   // Available
   printf("Available after writing: %d \n\n", uxQueueSpacesAvailable(queue_H));

   // Read data from queue
   xTaskCreate(task_receive, "task_receive", 4096, NULL, 10, &task_receive_Handle);
   vTaskDelay(100);
   
   // Available
   printf("\nAvailable at the end: %d \n\n", uxQueueSpacesAvailable(queue_H));
}
