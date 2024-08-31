// FreeRTOS Queue simple example

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <portmacro.h>



TaskHandle_t Handler_1=NULL;
TaskHandle_t Handler_2=NULL;
QueueHandle_t QueueHandler=NULL;

void Sender(void)
{
	uint16_t i=0;
	for(;;)
	{
		if(xQueueSend(QueueHandler, &i, 1000))
		{
		     printf("Sent: %d\r\n", i);
		}
		else
		{
			printf("Failed to send!\r\n");
		}
        i++;
	    vTaskDelay(1000);
	}

}


void Receiver(void)
{
	uint16_t j=0;
	for(;;)
	{
	    if(xQueueReceive(QueueHandler, &j, portMAX_DELAY))
	    {
		    printf("Received: %d\r\n", j);
	    }
	    else
	    {
		    printf("Failed to Receive!\r\n");
	    }

	}
}


void app_main(void)
{
    BaseType_t xReturn =NULL;
    /* Creating the Queue having the size of int */
    QueueHandler = xQueueCreate(2, sizeof(int));
    if(QueueHandler==NULL)
    {
       printf("Failed to create the Queue!\r\n");
    }
	

	xReturn= xTaskCreate(Sender, "SenderThread", 2048, NULL, 1, &Handler_1);
	if(xReturn==NULL)
	{
		vTaskDelete(Handler_1);
	}

	xReturn= xTaskCreate(Receiver, "ReceiverThread", 2048, NULL, 2, &Handler_2);
	if(xReturn==NULL)
	{
		vTaskDelete(Handler_2);
	}

}