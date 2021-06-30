/*************************************************************
 * This is the code by Saurabh Lanje.
 *   YouTube Channel - www.youtube.com/saurabhlanje
 *   Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/

#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/gpio.h"
#include"driverlib/pin_map.h"
#include"driverlib/sysctl.h"
#include"driverlib/uart.h"
#include"utils/uartstdio.h"
#include"utils/uartstdio.c"

void uartint(void);

unsigned char data;

int main(void)
{

SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2);

SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);// ENABLE GPIO PORT A,FOR UART
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

GPIOPinConfigure(GPIO_PA0_U0RX); // PA0 IS CONFIGURED TO UART RX
GPIOPinConfigure(GPIO_PA1_U0TX); // PA1 IS CONFIGURED TO UART TX
GPIOPinConfigure(GPIO_PB0_U1RX); // PB0 IS CONFIGURED TO UART1 RX

GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0);

UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
UARTStdioConfig(0, 9600, 16000000);
UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

/*UARTIntRegister(UART1_BASE,uartint);
IntEnable(INT_UART1);
UARTIntEnable(UART1_BASE, UART_INT_RX|UART_INT_RT);*/

UARTprintf("Bluetooth demo\n");

while (1)
{
if(UARTCharsAvail(UART1_BASE))
{
data=UARTCharGet(UART1_BASE);
UARTCharPut(UART0_BASE,data);
if(data=='r')
       GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2, 0x02);
else if(data=='b')
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2, 0x04);

}
}

}

/*void uartint(void)
{
unsigned char data;
UARTIntClear(UART1_BASE, UART_INT_RX);
data= UARTCharGet(UART1_BASE);
UARTCharPut(UART0_BASE,data);
}*/
