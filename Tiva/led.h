/*
 * led.h
 *
 *  Created on: 7 Oct 2022
 *      Author: viv
 */

#ifndef LED_H_
#define LED_H_
#include "inc/tm4c123gh6pm.h"
#include <stdint.h>

void SetupLEDs(void);
void RedLED(uint32_t value);
void BlueLED(uint32_t value);
void GreenLED(uint32_t value);

#endif /* LED_H_ */
