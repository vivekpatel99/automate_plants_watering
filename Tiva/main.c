/**
 * main.c
 */
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
#include "led.h"
#include "main.h"
#include "my_spi.h"
#include "my_adc.h"
/*
 * TODO setup ADC using on PE3 using interrupt
 * TODO setup SPI
 */

volatile static uint32_t ui32ADC0Value;

const float MAX_SENSOR_VALUE_0 = 2.578; // when the sensor is in air
const float MIN_SENSOR_VALUE_0 = 0.915; // when the sensor is in water
const int SEQ_NUM = 0;
volatile static uint32_t ui32Percentage_sensor_0;
volatile float ui32MoistureValue_sensor_0;
const uint32_t SENSOR_NUMBER_0 = 0;
int main(void)
{
    uint32_t ui32ReceivedData_Sensor_0 = 0;

    SetupLEDs();
    ADCInit();

    SequencerConfig();

    spi_config();
    GreenLED(0);

    while (1)
    {

        SSIDataGet(SSI0_BASE, &ui32ReceivedData_Sensor_0);
        if (ui32ReceivedData_Sensor_0 == SENSOR_NUMBER_0)
        {
            GreenLED(1);
            SSIDataPut(SSI0_BASE, ui32Percentage_sensor_0);
            while (SSIBusy(SSI0_BASE))
            {
            }
            _delay();
            GreenLED(0);
            _delay();
            break;
        }

    }

}
//int main(void)
//{
//    SetupLEDs();
//    ADCInit();
//
//    SequencerConfig();
//
//    while (1)
//    {
//        if (ui32ADC0Value > 2048)
//        {
//            GreenLED(1);
//            _delay();
//
//        }
//        else
//        {
//            GreenLED(0);
//            _delay();
//        }
//    }
//}

/******************************************************************************************/
void _delay(void)
{
    SysCtlDelay(SysCtlClockGet()); // / 12);
}
/******************************************************************************************/
void ADC0SS3IntHandler(void)
{

    ui32ADC0Value = ADC0_SSFIFO3_R; /*Retrieved ADC value from SS3 FIFO*/
    ui32MoistureValue_sensor_0 = (ui32ADC0Value * 3.3) / 4096;
    ui32Percentage_sensor_0 = ((ui32MoistureValue_sensor_0 - MIN_SENSOR_VALUE_0)
            * 100 / (MAX_SENSOR_VALUE_0 - MIN_SENSOR_VALUE_0) - 100) * -1;

    if (ui32Percentage_sensor_0 > 100)
        ui32Percentage_sensor_0 = 100;

    ADC0_ISC_R |= (1 << 3); /* ADC Interrupt Status and Clear */

}
