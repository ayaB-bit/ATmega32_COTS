/*
 * COTS.c
 *
 * Created: 24/08/2023 08:19:12 ص
 * Author : Bedir
 */ 
#include "LIB/STD_TYPES.h"
#include "LIB/ERROR_STATE.h"

#include "MCAL/PORT/PORT_interface.h"

#include "hal/LCD/CLCD_interface.h"

#include "hal/KEYPAD/KEYPAD_interface.h"
#include "hal/KEYPAD/KEYPAD_config.h"

#include <util/delay.h>


int main(void)
{
	PORT_enuInit();
	LCD_enuInit();
	u8 val;
	
	
    while (1) 
    {
		do 
		{
			val=KEYPAD_enuGetPressedKey();
		} while (val==0xff);
		
		LCD_enuSendChar(val);
			
    }
}

