#include <stdio.h>
#include "Led.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"


static const char *TAG = "LED";

Led::Led(gpio_num_t pin) : pin(pin)
{
    ESP_LOGI(TAG, "Created Led on pin %d", pin);
    esp_rom_gpio_pad_select_gpio(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    state = LS_NONE;
}

Led::~Led()
{
    ESP_LOGI(TAG, "Delete Led on pin %d", pin);
}

void Led::On() {
    _on();
    state = LS_NONE;
}
void Led::_on(){
    ESP_LOGI(TAG, "Turn on Led on pin %d", pin);
    gpio_set_level(pin, 1);
}
void Led::_off(){
    ESP_LOGI(TAG, "Turn off Led on pin %d", pin);
    gpio_set_level(pin, 0);
}

void Led::Off(){
    _off();
    state = LS_NONE;
}

void Led::Update() {
    switch(state)
    {
        case LS_BLINKING_ON:
        if (( pdTICKS_TO_MS(xTaskGetTickCount()) - timer) > on ) 
        {
            _off();
            state = LS_BLINKING_OFF;
        }
        
        break;

        case LS_BLINKING_OFF:
            if (( pdTICKS_TO_MS(xTaskGetTickCount()) - timer) > (on + off)) 
            {
                timer = pdTICKS_TO_MS(xTaskGetTickCount());
                _on(); 
                state = LS_BLINKING_ON;
            }
            
            break;  

        default:
        break;
    }
}

void Led::Blink(unsigned int on, unsigned int off) {
    this-> on = on;
    this-> off = off;    
    timer = pdTICKS_TO_MS(xTaskGetTickCount());
    On();
    state = LS_BLINKING_ON;
}