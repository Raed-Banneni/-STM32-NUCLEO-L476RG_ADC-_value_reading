#include <stdint.h>
#ifndef ADC_H_
#define ADC_H_

void pa1_adc1_init(void);
void start_conversion(void);
uint32_t adc_read(void);


#endif /* ADC_H_ */
