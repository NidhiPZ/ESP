// FreeRTOS Mutex Example

#include <stdio.h>
#include <stdlib.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

SemaphoreHandle_t GlobalHandler=NULL;

/* Precious resource function which might be the i2c/ spi or UART bus*/
void Precious_Resource(void)
{
     //Precious resource function which might be the i2c/ spi or UART bus
      //Both threads need to access this resource, but only one should do so at a time.
}

void Thread_1(void *p)
{
   for(;;)
   {
	   if(xSemaphoreTake(GlobalHandler, 250))  //to take mutex.
	   {
		   printf("Thread1 got the resource\n");
		   Precious_Resource();
		   xSemaphoreGive(GlobalHandler);   // to release mutex.
	   }
	   vTaskDelay(250);
   }

}

void Thread_2(void *p)
{
	for(;;)
	{
		if(xSemaphoreTake(GlobalHandler, 250))
		{
			printf("Thread2 got the resource\n");
			Precious_Resource();
			xSemaphoreGive(GlobalHandler);
		}
		vTaskDelay(250);
	}

}


void app_main(void)
{
	/* Creating the Mutex */
 GlobalHandler= xSemaphoreCreateMutex();   // The mutex handle is stored in GlobalHandler.
 if(GlobalHandler==NULL)
 {
	 printf("Failed to Create Mutex\n");
 }

 xTaskCreate(Thread_1, "Thread1", 1024, NULL, 1, NULL);

 xTaskCreate(Thread_2, "Thread2", 1024, NULL, 2, NULL);


}