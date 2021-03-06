/*
 * UART3_messages_control.c
 *
 *  Created on: 11 lis 2015
 *      Author: palka
 */

#include "UART3_messages_control.h"

//helper variables used to write and decode message
unsigned char inBuffer[MESSAGE_LENGTH_IN]; //buffor to store readed message
unsigned char outBuffer[MESSAGE_LENGTH_OUT]; //buffor to store message to send
unsigned int i = 0; //variable to manage char position in inBuffer array
bool messageInProgress = false;

//data used on the outside
Direction direction = Stop;
uint32_t velocity = 0;
bool UARTDataChanged = false;


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

    }
	//UARTCharPutNonBlocking(UART3_BASE,'G');
}

void SendMessage()
{
	int j;
	for(j=0; j<MESSAGE_LENGTH_OUT; j++)
	{
		UARTCharPutNonBlocking(UART3_BASE,outBuffer[j]);
	}
}

void UARTDataChangedSubscribe(void(*uartDataChangedEventHandler)(void))
{
	UartDataChangedEventHandler = uartDataChangedEventHandler;
}

void OnUartDataChangedEvent()
{
		UartDataChangedEventHandler();
}

void DecodeMessage()
{
	switch(inBuffer[INDEX_DIRECTION])
	{
	case 'H':
		direction = Stop;
		break;
	case 'F':
		direction = Forward;
		break;
	case 'B':
		direction = Backward;
		break;
	case 'L':
		direction = Left;
		break;
	case 'R':
		direction = Right;
		break;
	}
	velocity = (inBuffer[INDEX_VELOCITY]-48)*100 + (inBuffer[INDEX_VELOCITY+1]-48)*10 + (inBuffer[INDEX_VELOCITY+2]-48);
	OnUartDataChangedEvent();
}

void CodeMessage(int current1, int current2)
{
	outBuffer[INDEX_START_BYTE] = START_BYTE;
	outBuffer[INDEX_STOP_BYTE] = STOP_BYTE;

	outBuffer[INDEX_CURRENT_1] = current1/1000+48;
	current1 = current1%1000;
	outBuffer[INDEX_CURRENT_1+1] =  current1/100+48;
	current1 = current1%100;
	outBuffer[INDEX_CURRENT_1+2] = current1/10+48;
	current1 = current1%10;
	outBuffer[INDEX_CURRENT_1+3] = current1+48;

	outBuffer[INDEX_CURRENT_2] = current2/1000+48;
	current2 = current2%1000;
	outBuffer[INDEX_CURRENT_2+1] =  current2/100+48;
	current2 = current2%100;
	outBuffer[INDEX_CURRENT_2+2] = current2/10+48;
	current2 = current2%10;
	outBuffer[INDEX_CURRENT_2+3] = current2+48;
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
    	DecodeMessage();
    	inBuffer[i] = character;
    }
    else if(messageInProgress)
    {
    	i++;
    	inBuffer[i] = character;
    }
}
