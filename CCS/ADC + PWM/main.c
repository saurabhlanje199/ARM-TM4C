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
#include"driverlib/pwm.h"
#include"driverlib/pin_map.h"

// TO STORE THE VALUE IN VARIABLE ui32ADC0Value FOR EVERY SAMPLING
uint32_t ui32ADC0Value[1];
int main(void)

{
    volatile uint8_t ui8Adjust;//VARIABLE FOR PWM_WIDTH SET AS % FROM 0 TO 100
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

SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
//PERIPHERAL CONFIGURATION
SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); //PWM PERIPHERAL ENABLE
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //GPIO FOR PWM1
GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1); //GPIO PF1 FOR PWM1
GPIOPinConfigure(GPIO_PF1_M1PWM5); //PD0 AS M1PWM5
PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
//SET PWM GENERATOR WITH MODEOF OPERATION AS COUNTING
PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2,100); //SET PERIOD OF PWM GENERATOR
PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true); //ENABLE BIT5 OUTPUT
PWMGenEnable(PWM1_BASE, PWM_GEN_2); //ENABLE PWM_GEN_2 GENERATOR

while(1)
{
// TRIGGER IS GIVEN FOR ADC 0 MODULE, SEQUENCER 1
ADCProcessorTrigger(ADC0_BASE, 1);

// STORE THE CONVERTED VALUE FOR ALL DIFFERENT SAMPLING IN ARRAY
//ui32ADC0Value
ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
ui8Adjust = ui32ADC0Value[0]/40;
PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, ui8Adjust); //SET THE PULSE WIDTH
SysCtlDelay(4000000/3); //DELAY OF 300MILLISECONDS

}
}
