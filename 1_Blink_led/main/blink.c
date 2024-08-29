#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

void app_main(void)
{
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    
    while(1)
    {
        gpio_set_level(GPIO_NUM_2, 1);
        printf("LED ON\n");
        vTaskDelay(1000/portTICK_PERIOD_MS); 
        
        gpio_set_level(GPIO_NUM_2, 0);
        printf("LED OFF\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
