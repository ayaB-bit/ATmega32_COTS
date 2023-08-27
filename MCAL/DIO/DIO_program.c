/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: MCAL         *********************************************/
/******************************************  SWC: DIO            *********************************************/
/******************************************  Version: 1.00       *********************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO_private.h"
#include "DIO_config.h"
#include "../../LIB/ERROR_STATE.h"
#include "DIO_interface.h"



/*ES_t DIO_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	
	DDRA = CONC(PA_PIN7_DIR,PA_PIN6_DIR,PA_PIN5_DIR,PA_PIN4_DIR,PA_PIN3_DIR,PA_PIN2_DIR,PA_PIN1_DIR,PA_PIN0_DIR);
	DDRB = CONC(PB_PIN7_DIR,PB_PIN6_DIR,PB_PIN5_DIR,PB_PIN4_DIR,PB_PIN3_DIR,PB_PIN2_DIR,PB_PIN1_DIR,PB_PIN0_DIR);
	DDRC = CONC(PC_PIN7_DIR,PC_PIN6_DIR,PC_PIN5_DIR,PC_PIN4_DIR,PC_PIN3_DIR,PC_PIN2_DIR,PC_PIN1_DIR,PC_PIN0_DIR);
	DDRD = CONC(PD_PIN7_DIR,PD_PIN6_DIR,PD_PIN5_DIR,PD_PIN4_DIR,PD_PIN3_DIR,PD_PIN2_DIR,PD_PIN1_DIR,PD_PIN0_DIR);
	
	PORTA = CONC(PA_PIN7_VAL,PA_PIN6_VAL,PA_PIN5_VAL,PA_PIN4_VAL,PA_PIN3_VAL,PA_PIN2_VAL,PA_PIN1_VAL,PA_PIN0_VAL);
	PORTB = CONC(PB_PIN7_VAL,PB_PIN6_VAL,PB_PIN5_VAL,PB_PIN5_VAL,PB_PIN3_VAL,PB_PIN2_VAL,PB_PIN1_VAL,PB_PIN0_VAL);
	PORTC = CONC(PC_PIN7_VAL,PC_PIN6_VAL,PC_PIN5_VAL,PC_PIN4_VAL,PC_PIN3_VAL,PC_PIN2_VAL,PC_PIN1_VAL,PC_PIN0_VAL);
	PORTD = CONC(PD_PIN7_VAL,PD_PIN6_VAL,PD_PIN5_VAL,PD_PIN4_VAL,PD_PIN3_VAL,PD_PIN2_VAL,PD_PIN1_VAL,PD_PIN0_VAL);
	
	Local_enuErrorState = ES_OK;
	
	return Local_enuErrorState;
}*/
/////////////////
/*ES_t DIO_enuSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction)
{
	ES_t Local_enuErrorState = ES_OK;
	
	switch(Copy_u8Port)
	{
		case DIO_u8PORTA: DDRA=Copy_u8Direction; break;
		case DIO_u8PORTB: DDRB=Copy_u8Direction; break;
		case DIO_u8PORTC: DDRC=Copy_u8Direction; break;
		case DIO_u8PORTD: DDRD=Copy_u8Direction; break;
		default: Local_enuErrorState = ES_OUT_OF_RANGE; break;
	}

	return Local_enuErrorState;
}*/
///////////////////////////
/*ES_t DIO_enuSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	ES_t Local_enuErrorState = ES_OK;

	switch(Copy_u8Port)
	{
		case DIO_u8PORTA: PORTA=Copy_u8Value; break;
		case DIO_u8PORTB: PORTB=Copy_u8Value; break;
		case DIO_u8PORTC: PORTC=Copy_u8Value; break;
		case DIO_u8PORTD: PORTD=Copy_u8Value; break;
		default: Local_enuErrorState = ES_OUT_OF_RANGE; break;
	}
	
	return Local_enuErrorState;
}*/
/////////////////////////////////
ES_t DIO_enuGetPortValue(u8 Copy_u8Port, u8* Copy_pu8Value)
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_pu8Value != NULL)
	{
		switch(Copy_u8Port)
		{
			case DIO_u8PORTA: *Copy_pu8Value = PINA; break;
			case DIO_u8PORTB: *Copy_pu8Value = PINB; break;
			case DIO_u8PORTC: *Copy_pu8Value = PINC; break;
			case DIO_u8PORTD: *Copy_pu8Value = PIND; break;
			default: Local_enuErrorState = ES_OUT_OF_RANGE; break;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	
	return Local_enuErrorState;
}
////////////////////////////////////
ES_t DIO_enuTogPort(u8 Copy_u8Port)
{
	ES_t Local_enuErrorState = ES_OK;
	
	switch(Copy_u8Port)
	{
		case DIO_u8PORTA: PORTA=~PORTA; break;
		case DIO_u8PORTB: PORTB=~PORTB; break;
		case DIO_u8PORTC: PORTC=~PORTC; break;
		case DIO_u8PORTD: PORTD=~PORTD; break;
		default: Local_enuErrorState=ES_OUT_OF_RANGE; break;
	}
	
	return Local_enuErrorState;
}
/////////////////////////////
/*ES_t DIO_enuSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		if(Copy_u8Direction == INPUT)
		{
			switch(Copy_u8Port)
			{
				case DIO_u8PORTA: CLR_BIT(DDRA,Copy_u8Pin); break;
				case DIO_u8PORTB: CLR_BIT(DDRB,Copy_u8Pin); break;
				case DIO_u8PORTC: CLR_BIT(DDRC,Copy_u8Pin); break;
				case DIO_u8PORTD: CLR_BIT(DDRD,Copy_u8Pin); break;
				default: Local_enuErrorState = ES_OUT_OF_RANGE; break;
			}
		}
		else if(Copy_u8Direction ==  OUTPUT)
		{
			switch(Copy_u8Port)
			{
				case DIO_u8PORTA: SET_BIT(DDRA,Copy_u8Pin); break;
				case DIO_u8PORTB: SET_BIT(DDRB,Copy_u8Pin); break;
				case DIO_u8PORTC: SET_BIT(DDRC,Copy_u8Pin); break;
				case DIO_u8PORTD: SET_BIT(DDRD,Copy_u8Pin); break;
				default: Local_enuErrorState = ES_OUT_OF_RANGE; break;
			}
		}
		else
		{
			Local_enuErrorState = ES_NOK;
		}
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}
*/
////////////////////////

ES_t DIO_enuSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{

	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		if(Copy_u8Value == LOW)
		{
			switch(Copy_u8Port)
			{
				case DIO_u8PORTA: CLR_BIT(PORTA,Copy_u8Pin); break;
				case DIO_u8PORTB: CLR_BIT(PORTB,Copy_u8Pin); break;
				case DIO_u8PORTC: CLR_BIT(PORTC,Copy_u8Pin); break;
				case DIO_u8PORTD: CLR_BIT(PORTD,Copy_u8Pin); break;
				default: Local_enuErrorState = ES_OUT_OF_RANGE; break;
			}
		}
		else if(Copy_u8Value == HIGH)
		{
			switch(Copy_u8Port)
			{
				case DIO_u8PORTA: SET_BIT(PORTA,Copy_u8Pin); break;
				case DIO_u8PORTB: SET_BIT(PORTB,Copy_u8Pin); break;
				case DIO_u8PORTC: SET_BIT(PORTC,Copy_u8Pin); break;
				case DIO_u8PORTD: SET_BIT(PORTD,Copy_u8Pin); break;
				default: Local_enuErrorState = ES_OUT_OF_RANGE; break;
			}
		}
		else
		{
			Local_enuErrorState = ES_NOK;
		}
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}
//////////////////////
ES_t DIO_enuGetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* Copy_pu8Value)
{
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_pu8Value != NULL)
	{
		if(Copy_u8Pin <= DIO_u8PIN7)
		{
			switch(Copy_u8Port)
			{
				case DIO_u8PORTA: *Copy_pu8Value=GET_BIT(PINA , Copy_u8Pin); break;
				case DIO_u8PORTB: *Copy_pu8Value=GET_BIT(PINB , Copy_u8Pin); break;
				case DIO_u8PORTC: *Copy_pu8Value=GET_BIT(PINC , Copy_u8Pin); break;
				case DIO_u8PORTD: *Copy_pu8Value=GET_BIT(PIND , Copy_u8Pin); break;
				default: Local_enuErrorState = ES_OUT_OF_RANGE; break;
			}
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}
////////////////////////////
ES_t DIO_enuTogPin(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		switch(Copy_u8Port)
		{
			case DIO_u8PORTA: TOGGLE_BIT(PORTA,Copy_u8Pin); break;
			case DIO_u8PORTB: TOGGLE_BIT(PORTB,Copy_u8Pin); break;
			case DIO_u8PORTC: TOGGLE_BIT(PORTC,Copy_u8Pin); break;
			case DIO_u8PORTD: TOGGLE_BIT(PORTD,Copy_u8Pin); break;
			default: Local_enuErrorState = ES_OUT_OF_RANGE; break;
		}
	}

	return Local_enuErrorState;
}