/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: HAL          *********************************************/
/******************************************  SWC: KEYPAD         *********************************************/
/******************************************  Version: 1.00       *********************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERROR_STATE.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"

#include "util/delay.h"

u8 KEYPAD_enuGetPressedKey(void)
{
	u8 Local_u8Pressed_Key = NO_PRESSED_KEY;
	u8 Local_u8PinState;
	
	static u8 Local_Au8KeypadArrayVal[4][4] = KEYPAD_ARRAY_VAL;
	
	static u8 Local_Au8RowPort[]={R1_PORT, R2_PORT ,R3_PORT, R4_PORT};
	static u8 Local_Au8RowPin[]={R1_PIN, R2_PIN ,R3_PIN, R4_PIN};
	 
	static u8 Local_Au8ColPort[]={C1_PORT, C2_PORT ,C3_PORT, C4_PORT};
	static u8 Local_Au8ColPin[]={C1_PIN, C2_PIN ,C3_PIN, C4_PIN};
	
	for(u8 col=0; col<4; col++)
	{
		//activate current col
		DIO_enuSetPinValue(Local_Au8ColPort[col], Local_Au8ColPin[col], DIO_u8LOW);
		for(u8 row=0; row<4; row++)
		{
			//read current row
			DIO_enuGetPinValue(Local_Au8RowPort[row], Local_Au8RowPin[row], &Local_u8PinState);
			//check if pressed
			if(Local_u8PinState == DIO_u8LOW)
			{
				//_delay_ms(10);
				Local_u8Pressed_Key = Local_Au8KeypadArrayVal[row][col];
				//busy waiting
				while(Local_u8PinState == DIO_u8LOW)
				{
					DIO_enuGetPinValue(Local_Au8RowPort[row], Local_Au8RowPin[row], &Local_u8PinState);
				}
				return Local_u8Pressed_Key;
			}
		}
		//deactivate current col
		DIO_enuSetPinValue(Local_Au8ColPort[col], Local_Au8ColPin[col], DIO_u8HIGH);
	}
	
	return Local_u8Pressed_Key;
}