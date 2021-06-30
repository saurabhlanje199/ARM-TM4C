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

/*#define GPIO_PA0_U0RX 0x00000001 // UART PIN ADDRESS FOR UART RX
#define GPIO_PA1_U0TX 0x00000401 // UART PIN ADDRESS FOR UART TX
#define GPIO_PB0_U1RX 0x00010001*/
    unsigned char comp[11];
    unsigned int m=0;
int i=0,j;
char b[6];

void uartint()
{
    UARTIntClear(UART1_BASE, UART_INT_RX);
    comp[i]= UARTCharGet(UART1_BASE);
    UARTCharPut(UART0_BASE,comp[i]);
    i++;
}


int main()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    // ENABLE PERIPHERAL UART 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

   // GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    GPIOPinConfigure(GPIO_PA0_U0RX); // PA0 IS CONFIGURED TO UART RX
    GPIOPinConfigure(GPIO_PA1_U0TX); // PA1 IS CONFIGURED TO UART TX
    GPIOPinConfigure(GPIO_PB0_U1RX); // PB0 IS CONFIGURED TO UART RX

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 115200, 16000000);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


    UARTprintf("--------------Welcome to RFID demo---------------\n");
    //UARTIntRegister(UART1_BASE,uartint);
    IntEnable(INT_UART1);
    UARTIntEnable(UART1_BASE, UART_INT_RX|UART_INT_RT);

    while(1);
}

