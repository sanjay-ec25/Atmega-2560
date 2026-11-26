#include "gpio_driver.h"
#include<stdint.h>

// This function is used to write a value to the entire PORT.
// VALUE contains the 8-bit data that will be written to the PORT.
void PORT_WRITE(volatile gpio_port_t* PORT,uint8_t VALUE)
{
    PORT->PORT=VALUE;
}


// This function is used to write HIGH or LOW to a specific pin.
// PIN selects which pin we want to control.
// STATE decides whether the pin should be HIGH or LOW.
void PIN_WRITE(volatile gpio_port_t* PORT,gpio_pin_t PIN,gpio_mode_t STATE)
{
    if (STATE==0)
    {
        // Clear the selected bit to make the pin LOW.
        PORT->PORT&=(~(1<<PIN));
    }

    else
    {
        // Set the selected bit to make the pin HIGH.
        PORT->PORT|=(1<<PIN);
    }
}


// This function is used to set the direction of a specific pin.
// PIN selects the pin.
// MODE decides whether the pin is INPUT or OUTPUT.
void PIN_INIT(volatile gpio_port_t* PORT,gpio_pin_t PIN,gpio_mode_t MODE)
{
    if(MODE==0)
    {
        // Clear the selected DDR bit to configure the pin as INPUT.
        PORT->DDR&=(~(1<<PIN));
    }

    else
    {
        // Set the selected DDR bit to configure the pin as OUTPUT.
        PORT->DDR|=(1<<PIN);
    }
}


// This function is used to toggle a specific pin.
// If the pin is HIGH, it becomes LOW.
// If the pin is LOW, it becomes HIGH.
void TOGGLE_PIN(volatile gpio_port_t* PORT,gpio_pin_t PIN)
{
    PORT->PIN=(1<<PIN);
}


// This function is used to read the value of a specific pin.
// It returns 1 if the pin is HIGH and 0 if the pin is LOW.
uint8_t PIN_READ(volatile gpio_port_t* PORT,gpio_pin_t PIN)
{
    // Shift the selected bit to position 0 and read its value.
    uint8_t bit=((PORT->PIN)>>PIN)&1;
    return bit;
}


// This function is used to read the entire PORT.
// It returns the values of all 8 pins together.
uint8_t PORT_READ(volatile gpio_port_t* PORT)
{
    uint8_t bit=PORT->PIN;
    return bit;
}


// This function is used to set the direction of all 8 pins.
// MODE decides whether all pins are INPUT or OUTPUT.
void PORT_INIT(volatile gpio_port_t* PORT,gpio_mode_t STATE)
{
    if(STATE==0)
    {
        // Set all 8 pins as INPUT.
        PORT->DDR=0x00;
    }
    else
    {
        // Set all 8 pins as OUTPUT.
        PORT->DDR=0xFF;
    }
}


// This function is used to toggle all 8 pins of the PORT.
// Each pin changes from HIGH to LOW or LOW to HIGH.
void PORT_TOGGLE(volatile gpio_port_t* PORT)
{
    PORT->PIN=0xFF;
}


// This function is used to enable the internal pull-up resistor
// for a specific pin.
// The pin should be configured as INPUT before enabling pull-up.
void PIN_PULLUP(volatile gpio_port_t* PORT,gpio_pin_t PIN)
{
    PORT->PORT|=(1<<PIN);
}
