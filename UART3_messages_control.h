/*
 * UART3_messages_control.h
 *
 *  Created on: 11 lis 2015
 *      Author:  Paulina Sadowska
 */

#ifndef UART3_MESSAGES_CONTROL_H_
#define UART3_MESSAGES_CONTROL_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/uart.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

//macros of data recieved from uart
#define START_BYTE '{'
#define STOP_BYTE '}'
#define MOVE_LEFT 'L'
#define MOVE_RIGHT 'R'
#define MOVE_FORWARD 'F'
#define MOVE_BACK 'B'
#define MESSAGE_LENGTH 3 //length of the message

void WriteCharToBuffer(unsigned char character);

extern unsigned char inBuffer[MESSAGE_LENGTH]; //buffor to store readed message
extern unsigned int i; //variable to manage char position in inBuffer array
extern bool messageInProgress;

#endif /* UART3_MESSAGES_CONTROL_H_ */
