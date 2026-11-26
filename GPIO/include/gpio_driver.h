#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef enum
{
    LOW  = 0,
    HIGH = 1
} gpio_state_t;

typedef enum
{
    INPUT  = 0,
    OUTPUT = 1
} gpio_mode_t;

typedef struct
{
    volatile uint8_t PIN;
    volatile uint8_t DDR;
    volatile uint8_t PORT;
} gpio_port_t;


typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}gpio_pin_t;

#define PORT_A  ((volatile gpio_port_t *)0x20)
#define PORT_B  ((volatile gpio_port_t *)0x23)
#define PORT_C  ((volatile gpio_port_t *)0x26)
#define PORT_D  ((volatile gpio_port_t *)0x29)
#define PORT_E  ((volatile gpio_port_t *)0x2C)
#define PORT_F  ((volatile gpio_port_t *)0x2F)
#define PORT_G  ((volatile gpio_port_t *)0x32)
#define PORT_H  ((volatile gpio_port_t *)0x100)
#define PORT_J  ((volatile gpio_port_t *)0x103)
#define PORT_K  ((volatile gpio_port_t *)0x106)
#define PORT_L  ((volatile gpio_port_t *)0x109)



void PORT_WRITE(volatile gpio_port_t* PORT,uint8_t VALUE);

void PIN_WRITE(volatile gpio_port_t* PORT,gpio_pin_t PIN,gpio_mode_t STATE);

void TOGGLE_PIN(volatile gpio_port_t* PORT,gpio_pin_t PIN);

void PIN_INIT(volatile gpio_port_t* PORT,gpio_pin_t PIN,gpio_mode_t MODE);

uint8_t PIN_READ(volatile gpio_port_t* PORT,gpio_pin_t PIN);

uint8_t PORT_READ(volatile gpio_port_t* PORT);

void PORT_INIT(volatile gpio_port_t* PORT,gpio_mode_t STATE);

void PORT_TOGGLE(volatile gpio_port_t* PORT);

void PIN_PULLUP(volatile gpio_port_t* PORT,gpio_pin_t PIN);


#endif
