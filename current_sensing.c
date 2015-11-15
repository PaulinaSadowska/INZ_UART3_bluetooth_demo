/*
 * adc_config.c
 *
 *  Created on: 8 lis 2015
 *      Author: Paulina Sadowska
 */


#include "current_sensing.h"

void CurrentSensing_Init(void)
{
	ADC0_Init();
	Timer0_Init();
	Interrupts_Enable();
}

void Interrupts_Enable(void)
{

	IntMasterEnable();				// Enable processor interrupts.
	ADCIntEnable(ADC0_BASE, 1);		//enable ADC0 interrupts
	IntEnable(INT_ADC0SS1);			//enable interrupt when ADC0 conversion is done
	TimerEnable(TIMER0_BASE, TIMER_A); //enable timerA interrupts
}

void ADC0_Init(void)
{
	//enable ADC0 peripheral
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

	//enable Hardware averaging
	//64 measurements being averaged together.
	//We will then average four of those samples together in our code for a total of 256.
	ADCHardwareOversampleConfigure(ADC0_BASE, 64);

	//configure the ADC sequencer.
	ADCSequenceConfigure(ADC0_BASE, 			//use ADC0
		 	 	 	 	 1, 					// sequencer 1
					     ADC_TRIGGER_TIMER, 	//timer trigger sequence
					     0); 					//highest priority
	 //configure all four steps in the ADC sequencer. CH4 (PD3)
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH4);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH4);
	 //configure all four steps in the ADC sequencer. CH5 (PD2)
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE, //use ADC0
							1,		 // sequencer 1
							3,		//step nr
							ADC_CTL_CH5 | 		//Chanel 5 : PD2
							ADC_CTL_IE| 	//configure the interrupt flag (ADC_CTL_IE) to be set when the sample is done
							ADC_CTL_END);	//last conversion on sequencer

	//enable ADC0 sequencer
	ADCSequenceEnable(ADC0_BASE, 1);

    // Clear the interrupt status flag.
    ADCIntClear(ADC0_BASE, 2);

}



void Timer0_Init(void)
{
	uint32_t ui32Period; //desired clock period

	// before calling any peripheral specific driverLib function we must enable the clock to that peripheral!!!
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	/*
	 * Timer 0 as a 32-bit timer in periodic mode. When Timer 0 is configured as a 32-bit timer,
	 * it combines the two 16-bit timers Timer 0A and Timer 0B.
	 * TIMER0_BASE is the start of the timer registers for Timer0 in the peripheral section of the memory map.
	 */
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

	/*
	 * desired frequency = 10Hz
	 * duty cycle = 50% (interrupt at 1/2 of the desired period)
	 */
	ui32Period = (SysCtlClockGet() / 10) / 2;

	/*
	 * load calculated period into the Timer’s Interval Load register using the TimerLoadSet
	 * you have to subtract one from the timer period since the interrupt fires at the zero count
	 */
	TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);

	// Enable triggering
	TimerControlTrigger(TIMER0_BASE, TIMER_A, true);
}

/*
 * interrupt routine called when conversion is done
 * calculates average value obtained by sensor,
 * and motor current.
 * ** NOTE! **
 * to get ADC0 interrupt to work ADC0IntHandler MUST be placed in interrupt vector
 * (tm4c123gh6pm_startup_ccs.c file) and declared in this file under "extern void _c_int00(void);"
 */
void ADC0IntHandler(void) {

    // Clear the interrupt status flag.
    ADCIntClear(ADC0_BASE, 1);

	 //read the ADC value from the ADC Sample Sequencer 1 FIFO
	 ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
	 //calculate average voltage
	 ui32ADC0ValueAvg_CH4 = (ui32ADC0Value[0] + ui32ADC0Value[1])/2;
	 // mV per ADC code = (VREFP - VREFN) * value / 4096
	 ui32VoltageMotorLeft = 3300 * ui32ADC0ValueAvg_CH4 / 4096; //[mV]*/
	 ui32CurrentMotorLeft = ui32VoltageMotorLeft * 10 / 22; //R = 2.2 Ohm

	 ui32ADC0ValueAvg_CH5 = (ui32ADC0Value[2] + ui32ADC0Value[3])/2;
	 // mV per ADC code = (VREFP - VREFN) * value / 4096
	 ui32VoltageMotorRight = 3300 * ui32ADC0ValueAvg_CH5 / 4096; //[mV]*/
	 ui32CurrentMotorRight = ui32VoltageMotorRight * 10 / 22; //R = 2.2 Ohm
}
