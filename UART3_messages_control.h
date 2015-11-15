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

/** macros of data recieved from uart **/

//special characters
#define START_BYTE '{'
#define STOP_BYTE '}'

//possible move directions
#define MOVE_LEFT 'L'
#define MOVE_RIGHT 'R'
#define MOVE_FORWARD 'F'
#define MOVE_BACK 'B'
#define DONT_MOVE 'H'

//indexes on in message for informations
//in message
#define INDEX_DIRECTION 1
#define INDEX_VELOCITY  2
//out message
#define INDEX_START_BYTE 0
#define INDEX_CURRENT_1  1
#define INDEX_CURRENT_2  5
#define INDEX_STOP_BYTE  9


 //length of the message
#define MESSAGE_LENGTH_IN 6 //input message length
#define MESSAGE_LENGTH_OUT 10 //output message length

extern unsigned char inBuffer[MESSAGE_LENGTH_IN]; //buffor to store readed message
extern unsigned char outBuffer[MESSAGE_LENGTH_OUT]; //buffor to store readed message
extern unsigned int i; //variable to manage char position in inBuffer array
extern bool messageInProgress;

/* New data types */
typedef enum DirectionType
{
	Forward,
	Backward,
	Left,
	Right,
	Stop,
} Direction;

//data used on the outside
// TODO: Change direction for enum typedef DIR{} Direction;
extern Direction direction;

extern uint32_t velocity;
extern bool UARTDataChanged;

//EventHandler
void(*UartDataChangedEventHandler)(void);

//gets character and create incoming void WriteCharToBuffer(unsigned char character);message in inBuffer
void WriteCharToBuffer(unsigned char character);
void DecodeMessage();
void CodeMessage();
void SendMessage();
void OnUartDataChangedEvent();
void UARTDataChangedSubscribe(void(*uartDataChangedEventHandler)(void));

#endif /* UART3_MESSAGES_CONTROL_H_ */
