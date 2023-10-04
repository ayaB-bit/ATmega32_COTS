/*
 * COTS.c
 *
 * Created: 24/08/2023 08:19:12 ص
 * Author : Aya Bedair
 */ 
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"

#include "MCAL/PORT/PORT_interface.h"
#include "MCAL/PORT/PORT_config.h"
#include "MCAL/PORT/PORT_private.h"

#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/DIO/DIO_config.h"
#include "MCAL/DIO/DIO_private.h"

#include "MCAL/ADC/ADC_interface.h"
#include "MCAL/ADC/ADC_config.h"
#include "MCAL/ADC/ADC_private.h"

#include "HAL/LCD/CLCD_interface.h"
#include "HAL/LCD/CLCD_config.h"
#include "HAL/LCD/CLCD_private.h"

#include "MCAL/EXTI/EXTI_interface.h"
#include "MCAL/EXTI/EXTI_config.h"
#include "MCAL/EXTI/EXTI_private.h"

#include <util/delay.h>

//void INT0_ISR(void);
//void INT1_ISR(void);
void ADC_ISR(void);
u8 APP_u8ADCReading;
int main(void)
{
	PORT_enuInit();
	ADC_enuInit();
	GIE_voidEnable();
	//LCD_enuInit();
    while (1) 
    {
		 ADC_enuStartConversionAsynch(0, &APP_u8ADCReading, &ADC_ISR);
    }
}
void ADC_ISR(void)
{
	DIO_enuSetPortValue(DIO_u8PORTC,APP_u8ADCReading);
}
void INT0_ISR(void)
{
	DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8HIGH);
	_delay_ms(1000);
	DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8LOW);
}

void INT1_ISR(void)
{
	DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8HIGH);
}

