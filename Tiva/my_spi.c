/*
 * my_spi.c
 *
 *  Created on: 9 Oct 2022
 *      Author: viv
 */

#include "my_spi.h"

void spi_config(void){
    // reference  https://www.youtube.com/watch?v=VprofC5ssi4
    //    SSI0Clk 19 PA2 (2) I/O TTL SSI module 0 clock
    //    SSI0Fss 20 PA3 (2) I/O TTL SSI module 0 frame signal
    //    SSI0Rx 21 PA4 (2) I TTL SSI module 0 receive
    //    SSI0Tx 22 PA5 (2) O TTL SSI module 0 transmit
        //SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    //    1. Enable the SSI module using the RCGCSSI register (see page 346).
        SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

    //    2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 340).
    //    To find out which GPIO port to enable, refer to Table 23-5 on page 1351.
         SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //    3. Set the GPIO AFSEL bits for the appropriate pins (see page 671). To determine which GPIOs to
    //    configure, see Table 23-4 on page 1344.
         GPIOPinConfigure(GPIO_PA2_SSI0CLK);
         GPIOPinConfigure(GPIO_PA3_SSI0FSS);
         GPIOPinConfigure(GPIO_PA4_SSI0RX);
         GPIOPinConfigure(GPIO_PA5_SSI0TX);

    //    4. Configure the PMCn fields in the GPIOPCTL register to assign the SSI signals to the appropriate
    //    pins. See page 688 and Table 23-5 on page 1351.
         GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2);

    //    5. Program the GPIODEN register to enable the pin's digital function. In addition, the drive strength,
    //    drain select and pull-up/pull-down functions must be configured. Refer to “General-Purpose
    //    Input/Outputs (GPIOs)” on page 649 for more information.
    //    Note: Pull-ups can be used to avoid unnecessary toggles on the SSI pins, which can take the
    //    slave to a wrong state. In addition, if the SSIClk signal is programmed to steady state
    //    High through the SPO bit in the SSICR0 register, then software must also configure the
    //    GPIO port pin corresponding to the SSInClk signal as a pull-up in the GPIO Pull-Up
    //    Select (GPIOPUR) register.
         GPIO_PORTA_DEN_R |= (1<<5)|(1<<4)|(1<<3)|(1<<2);

    //    For each of the frame formats, the SSI is configured using the following steps:
    //    1. Ensure that the SSE bit in the SSICR1 register is clear before making any configuration changes.
         SSI0_CR1_R &= ~(1<<1); /*SSIDisable(GPIO_PORTA_BASE)*/

    //    2. Select whether the SSI is a master or slave:
    //        a. For master operations, set the SSICR1 register to 0x0000.0000
    //        b. For slave mode (output enabled), set the SSICR1 register to 0x0000.0004.
    //        c. For slave mode (output disabled), set the SSICR1 register to 0x0000.000C.

         SSI0_CR1_R = 0x00000004; /* Set Tiva as Slave */

    //    3. Configure the SSI clock source by writing to the SSICC register.
         //SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_SLAVE, 10000, 16)
         SSI0_CC_R = 0x00;

    //    4. Configure the clock prescale divisor by writing the SSICPSR register.
         SSI0_CPSR_R = 10; // frequency 1.6MHz

    //    5. Write the SSICR0 register with the following configuration:
    //        ■ Serial clock rate (SCR)
    //        ■ Desired clock phase/polarity, if using Freescale SPI mode (SPH and SPO)
    //        ■ The protocol mode: Freescale SPI, TI SSF, MICROWIRE (FRF)
    //        ■ The data size (DSS)

         /* BR=SysClk/(CPSDVSR * (1 + SCR)) -> 16MHz/(10*(1+0)) = 160000*/

         SSI0_CR0_R = 0x7; /*8bit data size page 970*/

    //    6. Optionally, configure the SSI module for μDMA use with the following steps:
    //        a. Configure a μDMA for SSI use. See “Micro Direct Memory Access (mueDMA)” on page 585 for
    //        more information.


    //        b. Enable the SSI Module's TX FIFO or RX FIFO by setting the TXDMAE or RXDMAE bit in the
    //        SSIDMACTL register.


    //    7. Enable the SSI by setting the SSE bit in the SSICR1 register
    //     SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_SLAVE, 10000, 16);
         SSIEnable(SSI0_BASE);
}

