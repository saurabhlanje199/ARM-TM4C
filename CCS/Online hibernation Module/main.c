/*************************************************************
 * This is the code by Saurabh Lanje.
 *   YouTube Channel - www.youtube.com/saurabhlanje
 *   Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/

#include <stdint.h>                     // Integer declaration
#include <stdbool.h>                    // Boolean declaration
#include "utils/ustdlib.h"              //
//#include "inc/hw_types.h"
#include "inc/hw_memmap.h"              // memory mapped peripherals
#include "driverlib/sysctl.h"           // system control peripherals api's
#include "driverlib/pin_map.h"          // Each and every Pin is mapped
#include "driverlib/debug.h"            // for debug purpose
#include "driverlib/hibernate.h"        // hibernate peripherals api's
#include "driverlib/gpio.h"             // GPIO peripherals api's

int main(void)
{
SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);   //Setting the clock to 40MHz

SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);                                        //Enable the peripheral

GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);           //Enable GPIO pin 3 as Output

GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);               //Write a value to the GPIO pin

SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);                                    //enable the Hibernation module.

HibernateEnableExpClk(SysCtlClockGet());                                            /*SysCtlClockGet returns the processor clock value.
                                                                                     Clock is been supplied for the hibernation module.*/

HibernateGPIORetentionEnable();                                                      /* This function enables the GPIO pin state to be maintained
                                                                                        during hibernation and remain active even when waking from hibernation. */

SysCtlDelay(64000000);                                                               // 4Seconds Delay

HibernateRTCSet(0);                                                                  //set the value of Real time clock counter.

HibernateRTCEnable();                                                                //enable the real time clock of hibernation module.

HibernateRTCMatchSet(0,5);                                                           //set the index value and match value

HibernateWakeSet(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC);                           //set the wake condition for real time clock and wake when external pin is pressed.

GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, 0x00);                                      //LED turned OFF

HibernateRequest();                                                                  // Request to remove power supply for CPU

while(1)
{
}
}
