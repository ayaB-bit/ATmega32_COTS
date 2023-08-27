/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: MCAL         *********************************************/
/******************************************  SWC: PORT           *********************************************/
/******************************************  Version: 1.00       *********************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "PORT_private.h"
#include "PORT_config.h"
#include "../../LIB/ERROR_STATE.h"
#include "PORT_interface.h"

ES_t PORT_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	
	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;
	
	PORTA = PORTA_VAL;
	PORTB = PORTB_VAL;
	PORTC = PORTC_VAL;
	PORTD = PORTD_VAL;
	
	Local_enuErrorState = ES_OK;
	
	return Local_enuErrorState;
}