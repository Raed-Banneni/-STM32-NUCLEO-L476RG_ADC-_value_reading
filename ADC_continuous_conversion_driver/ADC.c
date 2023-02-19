#include "stm32l476xx.h"
#include "adc.h"
#define ADC1_SEQL1 0X00
void pa1_adc1_init(void)
{
	/**************configure adc gpio pin ******************/
	//enable clock access to GPIOA
	RCC->AHB2ENR |= (1U<<0);
	//set the mode of pa1 to analog  mode
	GPIOA->MODER |=(1U<<2);
	GPIOA->MODER |=(1U<<3);
	/****************configure adc periph ******************/
	// enable clock access to adc module
	RCC->AHB2ENR |=(1U<<13);

	RCC->CCIPR |= (3U << 28); // select system clock for adc

	for (volatile int i=0;i<10000;i++){}
	/*******configure adc parameters****************/
	//conversion sequence start
	ADC1->SQR1 |=(1U<<7);
	ADC1->SQR1 |=(1U<<8);
	//conversion sequence length
	ADC1->SQR1 &= 0xFFFFFFF0UL;
	//Enable adc module
	// Check voltage regulator status
	ADC1->CR &= 0x00000000;
	ADC1->CR |= ADC_CR_ADVREGEN;

	while (!(ADC1->CR & ADC_CR_ADVREGEN)) {
		// Wait for voltage regulator startup time to pass
	}

	//  make sure Set ADVREGEN bit is set to 1
	ADC1->CR |= ADC_CR_ADVREGEN;

   //ENABLE ADC MODULE
	ADC1->CR |= ADC_CR_ADEN;
	while (!(ADC1->ISR & ADC_ISR_ADRDY)) {
	  // Wait for ADC startup time to pass
	}

	ADC1->CFGR &=~ ADC_CFGR_DISCEN;
	ADC1->CR &=~ADC_CR_ADSTART;

	//enable continuous conversion mode
	ADC1->CFGR |=ADC_CFGR_CONT;

	while (!(ADC1->CFGR & ADC_CFGR_CONT)){}
}

void start_conversion(void)
{

	/*start adc conversion 	 */
	ADC1->CR |=ADC_CR_ADSTART;


}

uint32_t adc_read(void)
{


	// wait for conversion to be complete
	while (!(ADC1->ISR & ADC_ISR_EOC)){}
	//read converted result from ADC1 data register
	return (ADC1->DR);
}
