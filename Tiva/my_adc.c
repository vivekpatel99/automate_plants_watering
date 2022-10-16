/*
 * my_adc.c
 *
 *  Created on: 7 Oct 2022
 *      Author: viv
 */


#include <my_adc.h>

void ADCInit(void){
    /* reference https://microcontrollerslab.com/adc-tm4c123g-tiva-c-launchpad-measure-analog-voltage-signal/
     * https://www.youtube.com/watch?v=xkAT9MXh8UY
     * */
    //    1. Enable the ADC clock using the RCGCADC register (see page 352).
    SYSCTL_RCGCADC_R |= (1 << 0); /* Enable ADC0 */

    //    2. Enable the clock to the appropriate GPIO modules via the RCGCGPIO register (see page 340).
    //    To find out which GPIO ports to enable, refer to “Signal Description” on page 801.
    SYSCTL_RCGCGPIO_R |= (1 << 4); /* Setup GPIO PORT E */

    //    3. Set the GPIO AFSEL bits for the ADC input pins (see page 671). To determine which GPIOs to
    //    configure, see Table 23-4 on page 1344.
    GPIO_PORTE_AFSEL_R |= (1 << 3);

    //    4. Configure the AINx signals to be analog inputs by clearing the corresponding DEN bit in the
    //    GPIO Digital Enable (GPIODEN) register (see page 682).
    GPIO_PORTE_DEN_R = 0x00;

    //    5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
    //    the appropriate bits of the GPIOAMSEL register (see page 687) in the associated GPIO block.
    GPIO_PORTE_AMSEL_R |= (1 << 3);

}

void SequencerConfig(void){
    IntMasterDisable();
    IntDisable(INT_ADC0SS3);

    /* Sample Sequencer Configuration */

    //    1. Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
    //    ADCACTSS register. Programming of the sample sequencers is allowed without having them
    //    enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
    //    event were to occur during the configuration process.
    ADC0_ACTSS_R &= ~(1 << 3); /* Disabling Sampling sequencer 3 */

    //    2. Configure the trigger event for the sample sequencer in the ADCEMUX register.
    ADC0_EMUX_R |= (0xF << 12);

    //    3. When using a PWM generator as the trigger source, use the ADC Trigger Source Select
    //    (ADCTSSEL) register to specify in which PWM module the generator is located. The default
    //    register reset selects PWM module 0 for all generators.
    //    N/A

    //    4. For each sample in the sample sequence, configure the corresponding input source in the
    //    ADCSSMUXn register.
    ADC0_SSMUX3_R = 0x00; /*Table 13-1 page 801 AIN0-> PE3 hence 0x00 */

    //    5. For each sample in the sample sequence, configure the sample control bits in the corresponding
    //    nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
    //    is set. Failure to set the END bit causes unpredictable behavior.
    ADC0_SSCTL3_R = 0x6; /*b0110 Sample interrupt enable and End of Sequence */

    //    6. If interrupts are to be used, set the corresponding MASK bit in the ADCIM register.
    ADC0_IM_R |= (1 << 3); /* Mask bit 3 for SS3*/

    //    7. Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS
    //    register
    ADC0_ACTSS_R |= (1 << 3); /* Enable Sampling sequencer 3 */

    ADC0_ISC_R |= (1 << 3); /* ADC Interrupt Status and Clear */

    // Interrupt setup
    IntMasterEnable();
    IntEnable(INT_ADC0SS3);
}
