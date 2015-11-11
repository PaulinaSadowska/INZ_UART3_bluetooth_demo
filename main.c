#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

#include "UART3_conf.h"

//macros of data recieved from uart
#define START_BYTE '{'
#define STOP_BYTE '}'
#define MOVE_LEFT 'L'
#define MOVE_RIGHT 'R'
#define MOVE_FORWARD 'F'
#define MOVE_BACK 'B'
#define MESSAGE_LENGTH 3 //length of the message

void LEDBlink(void);

unsigned char inBuffer[MESSAGE_LENGTH]; //buffor to store readed message
unsigned int i=0; //variable to manage char position in inBuffer array

void UARTIntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART3_BASE, true); 	//get interrupt status
    UARTIntClear(UART3_BASE, ui32Status); 			//clear the asserted interrupts
    while(UARTCharsAvail(UART3_BASE))				//loop while there are chars
    {
        UARTCharPutNonBlocking(UART3_BASE, UARTCharGetNonBlocking(UART3_BASE)); //echo character
        LEDBlink();
    }
}

int main(void) {
	
	 //clock runs on 40Mhz
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    //LED init
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    //UART3 init (Bluetooth)
    UART3_Init();

    while (1)
    { }

}

void LEDBlink(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); //blink LED
    SysCtlDelay(SysCtlClockGet() / (1000 * 3)); //delay ~1 msec
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); //turn off LED
}
