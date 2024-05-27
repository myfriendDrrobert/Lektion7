#ifndef LED_H
#define LED_H
#include "driver/gpio.h"

class Led
{
private:
    gpio_num_t pin;
public:
    Led(gpio_num_t pin);
    ~Led();

    void On();

    void Off();
};




#endif
