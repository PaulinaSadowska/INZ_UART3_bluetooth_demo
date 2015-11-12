/*
 * TIMER_sending_data.h
 *
 *  Created on: 12 lis 2015
 *      Author: palka
 */

#ifndef TIMER_SENDING_DATA_H_
#define TIMER_SENDING_DATA_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h" //includes valid INT_ values for IntEnable function parameter
#include "driverlib/timer.h" //macros for Timer API

#include "UART3_messages_control.h"
#include "current_sensing.h"

void Timer1_Init(unsigned int frequency);

#endif /* TIMER_SENDING_DATA_H_ */
