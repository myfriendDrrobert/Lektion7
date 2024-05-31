#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <Led.h>

#define LED_PIN GPIO_NUM_18

static const char *TAG = "MAIN";

Led *led1;

extern "C" void app_main(void)
{
    led1 = new Led(LED_PIN);

    led1->Blink(1000, 1000);
    for (size_t i=0; i < 10 * 200; i++)
    {        
        led1 -> Update();
        vTaskDelay(pdMS_TO_TICKS(20));
    }

    delete led1;
}