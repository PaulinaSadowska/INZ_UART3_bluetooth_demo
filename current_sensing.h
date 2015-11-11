/*
 * adc_config.h
 *
 *  Created on: 8 lis 2015
 *      Author: palka
 */

#ifndef ADC_ADC_TIMER_INTERRUPT_DEMO_ADC_CONFIG_H_
#define ADC_ADC_TIMER_INTERRUPT_DEMO_ADC_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h" //includes valid INT_ values for IntEnable function parameter
#include "driverlib/adc.h" //definitions for using the ADC driverS
#include "driverlib/timer.h" //macros for Timer API


	//Sequencer 1 generates 4 samples	/* array that will be used for storing the data read from the ADC FIFO.
	/* Array must be as large as the FIFO for the sequencer in use.
	 *
	 * Sequencer 0 : 8 samples
	 * Sequencer 1 : 4 samples
	 * Sequencer 2 : 4 samples
	 * Sequencer 3 : 1 samples
	 *
	 * We will be using sequencer 1
	 */
	uint32_t ui32ADC0Value[4]; //data buffer

	volatile uint32_t ui32ADC0ValueAvg_CH0; //average value readed from PE3
	volatile uint32_t ui32ADC0ValueAvg_CH1;	//average value readed from PE2

	volatile uint32_t ui32VoltageMotorLeft; //voltage on channel 0 (PE3)
	volatile uint32_t ui32VoltageMotorRight; //voltage on channel 1 (PE2)

	volatile uint32_t ui32CurrentMotorLeft; //current on channel 0 (PE3)
	volatile uint32_t ui32CurrentMotorRight; //current on channel 1 (PE2)


    /*
	* Calls ADC0_Init, Timer0_Init and Interrupts_Enable function
	* most general function to be called from the outside
    */
	void CurrentSensing_Init(void);

    /*
	* Initialize ADC0 sequencer 1
	* sequencer 1 gets 4 samples (averaged)
	* samples 0 and 1 from PE3, samples 2, 3 from PE2
	* it calculates average voltage and store it in ui32VoltageMotorRight/Left
	* it also calculate it to get ui32CurrentMotorRight/Left
	* (results are stored in this variables)
    */
	void ADC0_Init(void);

    /*
	* Initialize TIMER0 as ADC trigger
	* 32 bit periodic timer
	* frequency = 10Hz
    */
	void Timer0_Init(void);

    /*
	* Initialize processor, TIM0 and ADC0 interrupts
	* ** NOTE! **
	* to get ADC0 interrupt to work ADC0IntHandler MUST be placed in interrupt vector
	* (tm4c123gh6pm_startup_ccs.c file) and declared in this file under "extern void _c_int00(void);"
    */
	void Interrupts_Enable(void);

#endif /* ADC_ADC_TIMER_INTERRUPT_DEMO_ADC_CONFIG_H_ */
