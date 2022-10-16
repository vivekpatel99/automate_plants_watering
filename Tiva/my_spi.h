/*
 * my_spi.h
 *
 *  Created on: 9 Oct 2022
 *      Author: viv
 */

#ifndef MY_SPI_H_
#define MY_SPI_H_

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/ssi.h"
#include "inc/hw_ssi.h"
#include "driverlib/pin_map.h"



void spi_config(void);

#endif /* MY_SPI_H_ */
