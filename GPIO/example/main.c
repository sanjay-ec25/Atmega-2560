#include "gpio_driver.h"
#include <stdio.h>
#include <util/delay.h>

#define F_CPU 16000000UL

int main(void)
{
    PORT_INIT(PORT_B,OUTPUT);
  
   while(1)
   {	   
    PORT_WRITE(PORT_B,0XFF);
    _delay_ms(1000);
    PORT_TOGGLE(PORT_B);
    _delay_ms(1000);
   }
}
