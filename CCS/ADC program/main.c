/*************************************************************
 * This is the code by Saurabh Lanje.
 *   YouTube Channel - www.youtube.com/saurabhlanje
 *   Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/

#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"driverlib/gpio.h"
#include"inc/hw_types.h"
#include"driverlib/debug.h"
#include"driverlib/sysctl.h"
#include"driverlib/adc.h"
// TO STORE THE VALUE IN VARIABLE ui32ADC0Value FOR EVERY SAMPLING
uint32_t ui32ADC0Value[1];
int main(void)

{
SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ); // SYSTEM CLOCK AT 40MHZ

SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // ENABLE ADC0 MODULE

SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // ENABLE GPIO for ADC0 Module

GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_3);// ENABLE AN0 OF ADC0 MODULE

// ADC0 MODULE, TRIGGER IS PROCESSOR EVENT, SEQUENCER 1 IS CONFIGURED
ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);

// ADC0 MODULE, SEQUENCER 1 , FOR 1 SAMPLING, INPUT IS FROM CHANNEL 0 PE3
ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0);

// ENABLE THE SEQUENCE 1 FOR ADC0
ADCSequenceEnable(ADC0_BASE, 1);

while(1)
{
// TRIGGER IS GIVEN FOR ADC 0 MODULE, SEQUENCER 1
ADCProcessorTrigger(ADC0_BASE, 1);

// STORE THE CONVERTED VALUE FOR ALL DIFFERENT SAMPLING IN ARRAY
//ui32ADC0Value
ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
}
}

