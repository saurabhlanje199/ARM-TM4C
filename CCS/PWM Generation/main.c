/*************************************************************
 * This is the code by Saurabh Lanje.
 *   YouTube Channel - www.youtube.com/saurabhlanje
 *   Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/

#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"
#include"driverlib/debug.h"
#include"driverlib/pwm.h"
#include"driverlib/pin_map.h"
#include"inc/hw_gpio.h"
//#include"driverlib/rom.h"
//MAIN FUNCTION
static int count;
int main(void)
{
int i=0;
volatile uint8_t ui8Adjust;//VARIABLE FOR PWM_WIDTH SET AS % FROM 0 TO 100
//CLOCK SETTINGS - SET SYSTEM CLOCK TO 40MHz
SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
//SET PWM CLOCK AS SYSTEM CLOCK DIVIDED BY 64
SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
//PERIPHERAL CONFIGURATION
SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); //PWM PERIPHERAL ENABLE
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //GPIO FOR PWM1
GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);
GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
GPIOPinTypePWM(GPIO_PORTF_BASE, 0x0E/*GPIO_PIN_2*/); //GPIO PF1 FOR PWM1
GPIOPinConfigure(GPIO_PF2_M1PWM6);//PD0 AS M1PWM5
GPIOPinConfigure(GPIO_PF1_M1PWM5);
GPIOPinConfigure(GPIO_PF3_M1PWM7);
PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN);
PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN);
//PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN);
//SET PWM GENERATOR WITH MODEOF OPERATION AS COUNTING
PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3,100); //SET PERIOD OF PWM GENERATOR
PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2,100);
PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true); //ENABLE BIT5 OUTPUT
PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
PWMGenEnable(PWM1_BASE, PWM_GEN_3); //ENABLE PWM_GEN_2 GENERATOR
PWMGenEnable(PWM1_BASE, PWM_GEN_2);
while(1)
{

  // if(!GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4))
    {
// PWM_WIDTH CHANGE FROM 0%- 100% IN STEPS OF 10%
            for(i=1;i<11;i++)
            {
                ui8Adjust = i*10; //Step size of 10%
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, ui8Adjust); //SET THE PULSE WIDTH
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, ui8Adjust); //SET THE PULSE WIDTH
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, ui8Adjust); //SET THE PULSE WIDTH
                SysCtlDelay(13333333); //DELAY OF 300MILLISECONDS
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 0x00);
            }
    }
}
}
