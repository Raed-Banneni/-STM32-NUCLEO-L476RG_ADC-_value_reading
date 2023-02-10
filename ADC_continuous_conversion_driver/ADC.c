#include "stm32l476xx.h"
#define ADC3EN	 (1U<<13)
#define GPIOFEN  (1U<<5)
#define ADC3_CH6 (1U<<6)
#define ADC3_SEQL1 0X00

void pf3_adc3_init(void)
{
	/********configure ad the adc gpio pin******************/

	// enable clock access to GPIOF
	RCC->AHB2ENR |= GPIOFEN;
	// set the mode of pf3 to analog mode
	GPIOF->MODER |=(1U<<6);
	GPIOF->MODER |=(1U<<7);

	/*********************configure the adc peripheral************/
	// enable clock access to adc module:
	RCC->AHB2ENR |=ADC3EN;
	/*********** configure adc parameters **************/
	//conversion sequence start
	ADC3->SQR2 |= ADC3_CH6;
	//conversion sequence length
	ADC3->SQR2	= ADC3_SEQL1;
	//enable adc module
	/*
	 * due to low power mode provided by nucleo l476rg
	 * The software is allowed to set ADEN only when all bits of ADC_CR registers are 0
	 * (ADCAL=0, JADSTART=0, ADSTART=0, ADSTP=0, ADDIS=0 and ADEN=0) except for
	 * bit ADVREGEN which must be 1
	 */
	ADC3->CR &= (1U<<28);
	// Check voltage regulator status
	while ((ADC3->CR & ADC_CR_ADVREGEN) == 0) {
	// Wait for voltage regulator startup time to pass
	}

	// Set ADVREGEN bit to 1
	ADC3->CR |= ADC_CR_ADVREGEN;

	// Wait for voltage regulator startup time to pass

	// Set ADEN bit to 1
	ADC3->CR |= ADC_CR_ADEN;

}
void start_conversion(void)
{
	/*start adc conversion 	 */
}
