#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>

// Timer handle
TimerHandle_t xTimerHandle = NULL;
int timerCounter=0;
// Timer callback function
void vTimerCallback(TimerHandle_t xTimer)
{
    timerCounter++;
    printf("Timer callback function runnnig...counetr: %d\n",timerCounter);
     // Reset the counter after reaching 2
    if (timerCounter >= 3)
    {
        // Reset the counter to 0
        timerCounter = 0;
        // Print a message to indicate the reset
        printf("Counter reset.\n");
    }
}

void app_main(void)
{
    // Create the timer
    xTimerHandle = xTimerCreate("MyTimer",            /*Timer name (optional)*/
                                pdMS_TO_TICKS(2000),  /*Timer period (in ticks)*/
                                pdTRUE,        /*Auto-reload flag (pdTRUE for periodic timer*/
                                NULL, 
                                vTimerCallback);    /*callback function*/

    if (xTimerHandle == NULL)
    {
        printf("Failed to create timer.\n");
    }
    else
    {
        // Start the timer if created
        // timer handle, Block time (how long to wait to start the timer, usually 0)
        if (xTimerStart(xTimerHandle, 0) != pdPASS)
        {
            printf("Failed to start timer.\n");
        }
    }
}
