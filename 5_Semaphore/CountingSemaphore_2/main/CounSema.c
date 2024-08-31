#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

// Define the counting semaphore handle
SemaphoreHandle_t CountingSemaphore = NULL;

void Task_1(void)
{
    for(;;)
    {
        // Wait for the semaphore (decrement it)
        if(xSemaphoreTake(CountingSemaphore, portMAX_DELAY))
        {
            printf("Task 1 is running...\n");
            // Simulate some work by delaying
            vTaskDelay(pdMS_TO_TICKS(1000));
            // After work, give the semaphore back (increment it)
            xSemaphoreGive(CountingSemaphore);
        }
    }
}

void Task_2(void)
{
    for(;;)
    {
        // Wait for the semaphore (decrement it)
        if(xSemaphoreTake(CountingSemaphore, portMAX_DELAY))
        {
            printf("Task 2 is running...\n");
            // Simulate some work by delaying
            vTaskDelay(pdMS_TO_TICKS(1000));
            // After work, give the semaphore back (increment it)
            xSemaphoreGive(CountingSemaphore);
        }
    }
}

void Task_3(void)
{
    for(;;)
    {
        // Wait for the semaphore (decrement it)
        if(xSemaphoreTake(CountingSemaphore, portMAX_DELAY))
        {
            printf("Task 3 is running...\n");
            // Simulate some work by delaying
            vTaskDelay(pdMS_TO_TICKS(1000));
            // After work, give the semaphore back (increment it)
            xSemaphoreGive(CountingSemaphore);
        }
    }
}

void app_main(void)
{
    // Create a counting semaphore with a maximum count of 2 and an initial count of 2
    CountingSemaphore = xSemaphoreCreateCounting(3, 3);
    
    if(CountingSemaphore == NULL)
    {
        printf("Failed to create counting semaphore\n");
        return;
    }

    // Create tasks
    xTaskCreate(Task_1, "task1", 2048, NULL, 1, NULL);
    xTaskCreate(Task_2, "task2", 2048, NULL, 1, NULL);
    xTaskCreate(Task_3, "task3", 2048, NULL, 1, NULL);
}
