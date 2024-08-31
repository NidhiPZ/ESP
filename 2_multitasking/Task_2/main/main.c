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
		vTaskDelay(250);
	}

}

void Thread2(void *p)
{
	char *str2 = (char *)p;
	for(;;)
	{
		printf("Thread2: %s\r\n", str2);
		vTaskDelay(500);
	}

}



void app_main(void)
{
	/* Creating the FreeRTOS Task*/

	xTaskCreate(Thread1,              /*Thread callback func*/
				"thread1",            /*Thread name for ease debug */
				1024*2,                 /*Thread allocate stack memory*/
				(char *)"Hello world\n",  /*Thread arg para*/   
				1,                   /*thread priority*/
				&th1);               /*Thread handler*/

	xTaskCreate(Thread2, "thread2", 1024*2, (char *)"Hello Universe\n", 2, &th2);
	
}