/*
 * TIMER_sending_data.c
 *
 *  Created on: 12 lis 2015
 *      Author: palka
 */
#include "TIMER_sending_data.h"

void Timer1IntHandler(void)
{
	// Clear the timer interrupt
	TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    CodeMessage(ui32CurrentMotorRight, ui32CurrentMotorLeft); //create some mock data
    SendMessage(); //sends outBuffer
}


void Timer1_Init(unsigned int frequency)
{
	uint32_t ui32Period; //desired clock period

	// before calling any peripheral specific driverLib function we must enable the clock to that peripheral!!!
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

	/*
	 * Timer 1 as a 32-bit timer in periodic mode.
	 * TIMER1_BASE is the start of the timer registers for Timer0 in the peripheral section of the memory map.
	 */
	TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);

	/*
	 * desired frequency = x Hz
	 * duty cycle = 50% (interrupt at 1/2 of the desired period)
	 */
	ui32Period = (SysCtlClockGet() / frequency) / 2;

	/*
	 * load calculated period into the Timer’s Interval Load register using the TimerLoadSet
	 * you have to subtract one from the timer period since the interrupt fires at the zero count
	 */
	TimerLoadSet(TIMER1_BASE, TIMER_A, ui32Period -1);

	// Enable triggering
	TimerControlTrigger(TIMER1_BASE, TIMER_A, true);


	/*** INTERRUPT ENABLE ***/

	IntEnable(INT_TIMER1A); // enables the specific vector associated with Timer0A
	TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT); //enables a specific event within the timer to generate an interrupt.(timeout of Timer 0A)
//	IntMasterEnable(); //master interrupt enable API for all interrupts.

	/* TIMER ENABLE */
	TimerEnable(TIMER1_BASE, TIMER_A);

}
