/*************************************************************
 * This is the code by Saurabh Lanje.
 *   YouTube Channel - www.youtube.com/saurabhlanje
 *   Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/

#include <stdint.h>             // Integer declaration
#include <stdbool.h>            // Boolean values
#include "inc/hw_memmap.h"      // Each and every peripheral is assigned with memeory address i.e. it is memory mapped
#include "driverlib/debug.h"    //for debug purpose
#include "driverlib/gpio.h"     //gpio pin values and address with API's
#include "driverlib/sysctl.h"   //Sysctl API's
//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
int main(void)
{
    //volatile uint32_t ui32Loop; //used for loop variable
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Enable the GPIO port that is used for the on-board LED.


    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);// Enable the GPIO pin for the LED (PF3).  Set the direction as output
                                                       //and enable the GPIO pin for digital function.

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    while(1) // Loop forever.
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);        // Turn on the LED.

        SysCtlDelay(6666666);

        //for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);    // Delay for a bit.

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00); // Turn off the LED.

        SysCtlDelay(6666666);

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);        // Turn on the LED.

        SysCtlDelay(6666666);

        //for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);    // Delay for a bit.

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00); // Turn off the LED.

        SysCtlDelay(6666666);

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);        // Turn on the LED.

        SysCtlDelay(6666666);

        //for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);    // Delay for a bit.

       GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00); // Turn off the LED.

        SysCtlDelay(6666666);
        //for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++); // Delay for a bit.
    }
}

