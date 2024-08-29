#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

/*FreeRTOS Task handler */
TaskHandle_t th1=NULL;
TaskHandle_t th2=NULL;

void Thread1(void *p)
{
	char *str1 = (char *)p;
	for(;;)
	{
		printf("Thread1: %s\r\n", str1);
		vTaskDelay(250/portTICK_PERIOD_MS);
	}

}

void Thread2(void *p)
{
	char *str2 = (char *)p;
	for(;;)
	{
		printf("Thread2: %s\r\n", str2);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}

}



void app_main(void)
{
	/* Creating the FreeRTOS Task*/

	xTaskCreate(Thread1, "thread1", 1024*2, (char *)"Hello world\n",    1, &th1);

	xTaskCreate(Thread2, "thread2", 1024*2, (char *)"Hello Universe\n", 2, &th2);
	
}