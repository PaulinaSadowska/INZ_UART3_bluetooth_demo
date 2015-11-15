#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

#include "UART3_conf.h"
#include "UART3_messages_control.h"
#include "current_sensing.h"
#include "TIMER_sending_data.h"
#include "MotorControl.h"


void ChangeMovementParameters(void)
{
	// Directions are not set up properly
	switch(direction)
	{
	case Forward:
		MCPwmDutyCycleSet(MotorA,velocity);
		MCPwmDutyCycleSet(MotorB,velocity);
		MCChangeMotorState(MotorA, ROT_CCW );
		MCChangeMotorState(MotorB, ROT_CCW );
		break;
	case Backward:
		MCPwmDutyCycleSet(MotorA,velocity);
		MCPwmDutyCycleSet(MotorB,velocity);
		MCChangeMotorState(MotorA, ROT_CW );
		MCChangeMotorState(MotorB, ROT_CW );
		break;
	case Right:
		MCPwmDutyCycleSet(MotorA,velocity);
		MCPwmDutyCycleSet(MotorB,velocity);
		MCChangeMotorState(MotorA, ROT_CCW );
		MCChangeMotorState(MotorB, ROT_CW );
		break;
	case Left:
		MCPwmDutyCycleSet(MotorA,velocity);
		MCPwmDutyCycleSet(MotorB,velocity);
		MCChangeMotorState(MotorA, ROT_CW );
		MCChangeMotorState(MotorB, ROT_CCW );
		break;
	case Stop:
		MCPwmDutyCycleSet(MotorA,velocity);
		MCPwmDutyCycleSet(MotorB,velocity);
		MCChangeMotorState(MotorA, SOFT_BREAK );
		MCChangeMotorState(MotorB, SOFT_BREAK);
		break;
	}
}

int main(void) {
	
	 //clock runs on 40Mhz
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    //UART3 init (Bluetooth)
    UART3_Init();
    MCInitControlHardware(1);
    UARTDataChangedSubscribe(ChangeMovementParameters);

    //ADC channels init
    CurrentSensing_Init();
    //Initialize Timer to periodically send data do Android
    Timer1_Init(1); //frequency 1Hz

    while (1)
    { }

}



