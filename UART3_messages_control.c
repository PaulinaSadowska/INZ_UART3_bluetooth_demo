/*
 * UART3_messages_control.c
 *
 *  Created on: 11 lis 2015
 *      Author: palka
 */

#include "UART3_messages_control.h"

unsigned char inBuffer[MESSAGE_LENGTH]; //buffor to store readed message
unsigned int i = 0; //variable to manage char position in inBuffer array
bool messageInProgress = false;

//UART3 interrupt handler
void UARTIntHandler(void)
{
    uint32_t ui32Status;
    unsigned char temp;
    ui32Status = UARTIntStatus(UART3_BASE, true); 	//get interrupt status
    UARTIntClear(UART3_BASE, ui32Status); 			//clear the asserted interrupts
    while(UARTCharsAvail(UART3_BASE))				//loop while there are chars
    {
        temp = UARTCharGetNonBlocking(UART3_BASE); //gets character
        WriteCharToBuffer(temp);  //check if character is part of frame and write it to buffer
       // LEDBlink();
    }
	UARTCharPutNonBlocking(UART3_BASE,'G');
}

void WriteCharToBuffer(unsigned char character)
{
    if(character == START_BYTE)
    {
    	i=0;
    	messageInProgress = true;
    	inBuffer[i] = character;
    }
    else if(messageInProgress && character == STOP_BYTE)
    {
    	i++;
    	messageInProgress = false;
    	inBuffer[i] = character;
    }
    else if(messageInProgress)
    {
    	i++;
    	inBuffer[i] = character;
    }
}
