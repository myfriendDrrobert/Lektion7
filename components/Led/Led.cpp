#include <stdio.h>
#include "Led.h"
#include "esp_log.h"

static const char *TAG = "LED";

Led::Led(gpio_num_t pin) : pin(pin)
{
    ESP_LOGI(TAG, "Created Led on pin %d", pin);
    esp_rom_gpio_pad_select_gpio(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
}

Led::~Led()
{
}

void Led::On() {
    ESP_LOGI(TAG, "Turn on Led on pin %d", pin);
    gpio_set_level(pin, 1);
}

void Led::Off(){
    ESP_LOGI(TAG, "Turn off Led on pin %d", pin);
    gpio_set_level(pin, 0);
}
