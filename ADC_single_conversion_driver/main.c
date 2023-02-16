#include "stm32l476xx.h"
#include "uart.h"
#include "adc.h"
#include <stdio.h>
#include <stdint.h>

uint32_t sensor_value;


int main(void)
{
	led_init();
	ledon();
	uart2_rxtx_init();
	pa1_adc1_init();

	while(1)
	{
		start_conversion();

		ledtoggle();

		sensor_value=adc_read();
		printf("%u \r\n",(unsigned int)sensor_value);
	}
}





