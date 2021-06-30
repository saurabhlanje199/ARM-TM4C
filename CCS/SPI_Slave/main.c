/*************************************************************
 * This is the code by Saurabh Lanje.
 *   YouTube Channel - www.youtube.com/saurabhlanje
 *   Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"


#define NUM_SSI_DATA            3

uint32_t pui32DataTx[NUM_SSI_DATA];
uint32_t pui32DataRx[NUM_SSI_DATA];
uint32_t ui32Index;
volatile unsigned long g_ulSSI2RXTO = 0;

void SSI0_SLAVE_Interrupt(void)
{
    uint32_t ui32Status;

    ui32Status=SSIIntStatus(SSI0_BASE,1);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0X00);
    if(ui32Status & SSI_RXFF|SSI_RXTO)
    {
        for(ui32Index=0;ui32Index < NUM_SSI_DATA; ui32Index++)
        {
            SSIDataGet(SSI0_BASE, &pui32DataRx[ui32Index]);
             UARTprintf("%c", pui32DataRx[ui32Index]);
        }
          UARTprintf("\n");
    }
    SSIIntClear(SSI0_BASE, ui32Status);
}

void InitConsole(void)
{
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); // enable UART0 GPIO peripheral
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);
        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
        UARTStdioConfig(0, 9600, SysCtlClockGet()); // 115200 baud
}


int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    uint32_t ui32clock= SysCtlClockGet();
    InitConsole();

    UARTprintf("SSI Slave->\n");
    UARTprintf("  Mode: SPI\n");
    UARTprintf("  Data: 8-bit\n\n");

    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0x00);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 |GPIO_PIN_2);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);

    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3,SSI_MODE_SLAVE,4000000, 8);
    SSIEnable(SSI0_BASE);
    SSIIntRegister(SSI0_BASE,SSI0_SLAVE_Interrupt);
    SSIIntEnable(SSI0_BASE,SSI_RXFF|SSI_RXTO);
    while(SSIDataGetNonBlocking(SSI0_BASE, &pui32DataRx[0]))
    {
    }
    SSIIntClear(SSI0_BASE,SSI_RXFF|SSI_RXTO);

    pui32DataTx[0] = 'S';
    pui32DataTx[1] = 'P';
    pui32DataTx[2] = 'I';

    while(SSIBusy(SSI0_BASE))
    {
    }

    IntEnable(INT_SSI0);
    while(1)
    {
           while(SSIBusy(SSI0_BASE))
            {
            }
        if(!GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4))
                {
              UARTprintf("Data Sent to master\n");
               for(ui32Index = 0; ui32Index < NUM_SSI_DATA; ui32Index++)
                {
                   SSIDataPut(SSI0_BASE, pui32DataTx[ui32Index]);
                   GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0X02);
                }
               SysCtlDelay(13333333/2);
                }
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0X00);
    }
}


