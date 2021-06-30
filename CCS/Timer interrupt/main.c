/*************************************************************
 * This is the code by Saurabh Lanje.
 *   YouTube Channel - www.youtube.com/saurabhlanje
 *   Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
int main(void)
{
uint32_t ui32Period;        //variable for storing clock rate

SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);   //set system clock to 40MHz

SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);        //Enable GPIOF peripheral since led connected to portF

GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //GPIO pins 1,2,3 are set as output pins

SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);       //enable timer peripheral before configuring it.

TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);    // timer is configured as Periodic timer.

ui32Period = (SysCtlClockGet());                    //Returns the Processor clock rate which is stored in "ui32Period" variable

TimerLoadSet(TIMER0_BASE,TIMER_A, ui32Period -1);   //timer0->timerA is loaded with the count value

IntEnable(INT_TIMER0A);                             //interrupt for timer0->timerA is enabled

TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);    //timer interrupt should be generated when timerA timeouts.

TimerEnable(TIMER0_BASE, TIMER_A);                  //enables timerA to start counting.

while(1)
    {
        };                                          //execute the while loop unless a timer interrupt is generated
}
void Timer0IntHandler(void)                         //Timer ISR
{
// Clear the timer interrupt
TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);     //Once interrupt is generated then first clear the interrupt.

// Read the current state of the GPIO pin and write back the opposite state

if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3))        //check for the current status of the GPIO pin
{
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0); //Turn off the LED
}
else
{
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x8);  //turn on the LED
}
}
