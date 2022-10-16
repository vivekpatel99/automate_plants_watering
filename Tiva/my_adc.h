/*
 * my_adc.h
 *
 *  Created on: 7 Oct 2022
 *      Author: viv
 */

#ifndef MY_ADC_H_
#define MY_ADC_H_

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include"driverlib/gpio.h"
#include "driverlib/interrupt.h"

void ADCInit(void);

void SequencerConfig(void);


#endif /* MY_ADC_H_ */
