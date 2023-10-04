/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: MCAL         *********************************************/
/******************************************  SWC: ADC            *********************************************/
/******************************************  Version: 1.00       *********************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERROR_STATE.h"
#include "../../LIB/BIT_MATH.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"

static u16* ADC_pu16Reading = NULL;
static void (*ADC_pvCallBackNotificationFunc)(void) = NULL;

u8 ADC_u8BusyState = IDLE;

ES_t ADC_enuInit(void)
{
	ES_t Local_enuErrorState = ES_OK;
	 
	//Set reference
	switch (ADC_REF_SELECTION)
	{
		case AVCC: SET_BIT(ADMUX, ADMUX_REFS0); CLR_BIT(ADMUX, ADMUX_REFS1); break;

		case INTERNAL_VREF: SET_BIT(ADMUX, ADMUX_REFS0);SET_BIT(ADMUX, ADMUX_REFS1); break;

		case AREF: CLR_BIT(ADMUX, ADMUX_REFS0);CLR_BIT(ADMUX, ADMUX_REFS1); break;
		
		default: Local_enuErrorState = ES_OUT_OF_RANGE; break;
	}

	//Left adjust result
	switch (ADC_LEFT_ADJUST)
	{
		case ENABLED: SET_BIT(ADMUX,ADMUX_ADLAR); break;
		
		case DISABLED: CLR_BIT(ADMUX,ADMUX_ADLAR); break;
		
		default: Local_enuErrorState = ES_OUT_OF_RANGE; break; 
	}

	//clear pre_scaler bits
	ADCSRA &= ACD_PRESCALER_MASK;
	//set pre_scaler selection
	ADCSRA |= ADC_PRESCALER_SELECTION;
	
	//enable ADC
	SET_BIT(ADCSRA,ADCSRA_ADEN);
	
	return Local_enuErrorState;
}

ES_t ADC_enuStartConversionSynch(u8 Copy_u8Channel, u16* Copy_u16Reading)
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(ADC_u8BusyState == IDLE)
	{
		ADC_u8BusyState = BUSY;
		u32 Local_u32Counter = 0;
		
		if(Copy_u16Reading != NULL)
		{
			//clear MUX bits
			ADMUX &= ACD_MULTIBLEXER_MASK;
			//set the required channel
			ADMUX |= Copy_u8Channel;
			
			//start conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			
			//polling (busy waiting) until flag is set
			while(((GET_BIT(ADCSRA,ADCSRA_ADIF)) == 0) && (Local_u32Counter != ADC_u32TIMEOUT))
			{
				Local_u32Counter++;
			}
			if(Local_u32Counter == ADC_u32TIMEOUT)
			{
				//loop is broken because time is out
				Local_enuErrorState = ES_NOK;
			}
			else
			{
				//loop is broken because flag is raised
				//clear flag
				SET_BIT(ADCSRA,ADCSRA_ADIF);
				//return the reading
				*Copy_u16Reading = ADCH;
				//make ADC state IDLE
				ADC_u8BusyState = IDLE;
			}
		}
		else
		{
			Local_enuErrorState = ES_NULL_POINTER;
		}
	}
	else
	{
		Local_enuErrorState = BUSY_FUNCTION;
	}
	
	return Local_enuErrorState;
}

ES_t ADC_enuStartConversionAsynch(u8 Copy_u8Channel, u16* Copy_u16Reading, void(*Copy_pvNotificationFunc)(void))
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(ADC_u8BusyState == IDLE)
	{
		if((Copy_u16Reading != NULL) && (Copy_pvNotificationFunc != NULL))
		{
			//make ADC busy
			ADC_u8BusyState = BUSY;
			
			//initialize the reading globally
			ADC_pu16Reading = Copy_u16Reading;
			//initialize the callback notification function globally
			ADC_pvCallBackNotificationFunc = Copy_pvNotificationFunc;
			
			//clear MUX bits
			ADMUX &= ACD_MULTIBLEXER_MASK;
			//set the required channel
			ADMUX |= Copy_u8Channel;
			
			//start conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			
			//enable ADC interrupt
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_enuErrorState = ES_NULL_POINTER;
		}
	}
	else
	{
		Local_enuErrorState = BUSY_FUNCTION;
	}
	
	return Local_enuErrorState;
}

s32 ADC_s32Mapping(s32 Copy_s32InputMin, s32 Copy_s32InputMax, s32 Copy_s32OutputMin, s32 Copy_s32OutputMax, s32 Copy_s32InputVal)
{
	s32 Local_s32Slope =  (Copy_s32OutputMax - Copy_s32OutputMin)/(Copy_s32InputMax - Copy_s32InputMin);
	s32 Local_s32OutputVal = (Local_s32Slope * (Copy_s32InputVal - Copy_s32InputMin)) + Copy_s32OutputMin;
	
	return Local_s32OutputVal;
}

void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	//Get ADC reading
	*ADC_pu16Reading = ADCH;
	
	//make ADC state IDLE
	ADC_u8BusyState = IDLE;
	
	//invoke the callback notification function
	ADC_pvCallBackNotificationFunc();
	 
	//disable ADC conversion complete interrupt
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
}