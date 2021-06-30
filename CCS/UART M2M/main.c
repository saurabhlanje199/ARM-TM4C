/*************************************************************
 * This is the code by Saurabh Lanje.
 *   YouTube Channel - www.youtube.com/saurabhlanje
 *   Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/

#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"driverlib/gpio.h"
#include"driverlib/pin_map.h"
#include"driverlib/sysctl.h"
#include"driverlib/uart.h"
#include "inc/tm4c123gh6pm.h"
#include "utils/uartstdio.h"
#include"utils/uartstdio.c"
#include "driverlib/debug.h"
#include "driverlib/eeprom.h"

//#define GPIO_PA0_U0RX 0x00000001 // UART PIN ADDRESS FOR UART RX
//#define GPIO_PA1_U0TX 0x00000401 // UART PIN ADDRESS FOR UART TX

uint32_t a=0, zero=0, b=0;
int main(void){

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ| SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);// ENABLE GPIO PORT A,FOR UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);// ENABLE GPIO PORT B, FOR UART

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    GPIOPinConfigure(GPIO_PA0_U0RX); // PA0 IS CONFIGURED TO UART RX0
    GPIOPinConfigure(GPIO_PA1_U0TX); // PA1 IS CONFIGURED TO UART TX0
    GPIOPinConfigure(GPIO_PB0_U1RX); // PB0 IS CONFIGURED TO UART RX1
    GPIOPinConfigure(GPIO_PB1_U1TX); // PB1 IS CONFIGURED TO UART TX1
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    UARTStdioConfig(0, 115200, 16000000);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(),115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    while (1)
    {
        if (UARTCharsAvail(UART0_BASE))    //Checks if any character is present in FIFO
        {
            a=UARTCharGet(UART0_BASE);     //Get the character from the serial port
            UARTCharPut(UART1_BASE,a);
             SysCtlDelay(13333333);                               //print the character to the serial terminal
        }
        if(UARTCharsAvail(UART1_BASE))
        {
            b= UARTCharGet(UART1_BASE);
            UARTCharPut(UART0_BASE,b);
           SysCtlDelay(13333333);
        }

    }
}

