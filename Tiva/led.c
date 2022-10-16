/*
 * led.c
 *
 *  Created on: 7 Oct 2022
 *      Author: viv
 */

#include <led.h>



void SetupLEDs(void){
    //    1. Enable the clock to the port by setting the appropriate bits in the RCGCGPIO register (see
    //    page 340). In addition, the SCGCGPIO and DCGCGPIO registers can be programmed in the
    //    same manner to enable clocking in Sleep and Deep-Sleep modes.
    SYSCTL_RCGCGPIO_R |= (1<<5); /* enabling clock for GPIO port F */

    //    2. Set the direction of the GPIO port pins by programming the GPIODIR register. A write of a 1
    //    indicates output and a write of a 0 indicates input. page 663
    GPIO_PORTF_DIR_R = 0x0E; /* set as output */

    //    3. Configure the GPIOAFSEL register to program each bit as a GPIO or alternate pin. If an alternate
    //    pin is chosen for a bit, then the PMCx field must be programmed in the GPIOPCTL register for
    //    the specific peripheral required. There are also two registers, GPIOADCCTL and GPIODMACTL,
    //    which can be used to program a GPIO pin as a ADC or mueDMA trigger, respectively.
    GPIO_PORTF_AFSEL_R = 0x00; /* Set PORTF as GPIO */

    //    4. Set the drive strength for each of the pins through the GPIODR2R, GPIODR4R, and GPIODR8R
    //    registers.
    GPIO_PORTF_DR2R_R = 0x0E;

    //    5. Program each pad in the port to have either pull-up, pull-down, or open drain functionality through
    //    the GPIOPUR, GPIOPDR, GPIOODR register. Slew rate may also be programmed, if needed,
    //    through the GPIOSLR register.


    //    6. To enable GPIO pins as digital I/Os, set the appropriate DEN bit in the GPIODEN register. To
    //    enable GPIO pins to their analog function (if available), set the GPIOAMSEL bit in the
    //    GPIOAMSEL register.
    GPIO_PORTF_DEN_R = 0x0E; /* Set GPIO as Digital */
}

void RedLED(uint32_t value){
    if (value == 1) GPIO_PORTF_DATA_R = 0x02;
    else GPIO_PORTF_DATA_R = 0x00;
}

void BlueLED(uint32_t value){
    if (value == 1) GPIO_PORTF_DATA_R = 0x04;
    else GPIO_PORTF_DATA_R = 0x00;
}
void GreenLED(uint32_t value){
    if (value == 1) GPIO_PORTF_DATA_R = 0x08;
    else GPIO_PORTF_DATA_R = 0x00;
}
