#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Define task handles
TaskHandle_t Task1_Handle = NULL;
TaskHandle_t Task2_Handle = NULL;

// Task 1: Sender Task
void Task1(void *param)
{
    for(;;)
    {
        // Notify Task 2 (Task2_Handle) every 1 second
        printf("Task 1 sending notification to Task 2...\n");
        xTaskNotifyGive(Task2_Handle);
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay of 1 second
    }
}

// Task 2: Receiver Task
void Task2(void *param)
{
    for(;;)
    {
        // Wait for a notification
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // Block indefinitely until notification received
        printf("Task 2 received notification from Task 1!\n");
    }
}

void app_main(void)
{
    // Create Task 2 first so that its handle can be used by Task 1
    xTaskCreate(Task2, "Task2", 2048, NULL, 1, &Task2_Handle);

    // Create Task 1
    xTaskCreate(Task1, "Task1", 2048, NULL, 1, &Task1_Handle);
}
