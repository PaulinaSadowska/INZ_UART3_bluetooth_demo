/*
 * UART3_conf.c
 *
 *  Created on: 9 lis 2015
 *      Author: palka
 */

#include "UART3_conf.h"

void UART3_Init()
{
	//Enable the UART0 and GPIOC peripherals (the UART2 pins are on GPIO Port C)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    GPIOPinConfigure(GPIO_PC6_U3RX);
    GPIOPinConfigure(GPIO_PC7_U3TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    //Initialize the parameters for the UART: baud_rate, 8-1-N
    UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), BAUD_RATE,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    //The receiver timeout interrupt is
    IntMasterEnable(); 		//enable processor interrupts
    IntEnable(INT_UART3); 	//enable the UART3 interrupt
   /*
    * receiver interrupts (RX) - generated when a single character has been received (when FIFO is disabled)
    *			or when the specified FIFO level has been reached (when FIFO is enabled)
    * receiver timeout interrupts (RT) - generated when a character has been received,
    * 			and a second character has not been received within a 32-bit period.
    */
    UARTIntEnable(UART3_BASE, UART_INT_RX | UART_INT_RT);


}
