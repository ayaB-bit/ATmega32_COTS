/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: MCAL         *********************************************/
/******************************************  SWC: EXTI           *********************************************/
/******************************************  Version: 1.00       *********************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERROR_STATE.h"
#include "../../LIB/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

//Global pointer to function to hold INT0 ISR address
void(*EXTI_pvInt0Isr)(void) = NULL;

//Global pointer to function to hold INT1 ISR address
void(*EXTI_pvInt1Isr)(void) = NULL;

//Global pointer to function to hold INT2 ISR address
void(*EXTI_pvInt2Isr)(void) = NULL;

void EXTI_voidInt0Init(void)
{
	//Check INT0_SENSE option
	#if INT0_SENSE == FALLING_EDGE  //1 0
		SET_BIT(MCUCR,MCUSR_ISC01);
		CLR_BIT(MCUCR,MCUSR_ISC00);	
		
	#elif INT0_SENSE == RISING_EDGE //1 1
		SET_BIT(MCUCR,MCUSR_ISC01);
		SET_BIT(MCUCR,MCUSR_ISC00);
		
	#elif INT0_SENSE == ON_CHANGE   //0 1
		CLR_BIT(MCUCR,MCUSR_ISC01);
		SET_BIT(MCUCR,MCUSR_ISC00);
		
	#elif INT0_SENSE == LOW_LEVEL   //0 0
		CLR_BIT(MCUCR,MCUSR_ISC01);
		CLR_BIT(MCUCR,MCUSR_ISC00);
	#else
		#error "Wrong INT0_SENSE configuration option"
	#endif
	
	//Check INT0_INITIAL_STATE option
	#if INT0_INITIAL_STATE == ENABLE
		SET_BIT(GICR,GICR_INT0);
	#elif INT0_INITIAL_STATE == DISABLE
		CLR_BIT(GICR,GICR_INT0);
	#else 
		#error "Wrong INT0_INITIAL_STATE configuration option"
	#endif
}

void EXTI_voidInt1Init(void)
{
	//Check INT1_SENSE option
	#if INT1_SENSE == FALLING_EDGE  //1 0
	SET_BIT(MCUCR,MCUSR_ISC11);
	CLR_BIT(MCUCR,MCUSR_ISC10);
	
	#elif INT1_SENSE == RISING_EDGE //1 1
	SET_BIT(MCUCR,MCUSR_ISC11);
	SET_BIT(MCUCR,MCUSR_ISC10);
	
	#elif INT1_SENSE == ON_CHANGE   //0 1
	CLR_BIT(MCUCR,MCUSR_ISC11);
	SET_BIT(MCUCR,MCUSR_ISC10);
	
	#elif INT1_SENSE == LOW_LEVEL   //0 0
	CLR_BIT(MCUCR,MCUSR_ISC11);
	CLR_BIT(MCUCR,MCUSR_ISC10);
	#else
	#error "Wrong INT1_SENSE configuration option"
	#endif
	
	//Check INT1_INITIAL_STATE option
	#if INT1_INITIAL_STATE == ENABLE
	SET_BIT(GICR,GICR_INT1);
	#elif INT1_INITIAL_STATE == DISABLE
	CLR_BIT(GICR,GICR_INT1);
	#else
	#error "Wrong INT1_INITIAL_STATE configuration option"
	#endif
}

void EXTI_voidInt2Init(void)
{
	//Check INT1_SENSE option
	#if INT2_SENSE == FALLING_EDGE  //0
	CLR_BIT(MCUCSR,MCUCSR_INT2);
	
	#elif INT2_SENSE == RISING_EDGE //1
	SET_BIT(MCUCSR,MCUCSR_INT2);
	#else
	#error "Wrong INT2_SENSE configuration option"
	#endif
	
	//Check INT1_INITIAL_STATE option
	#if INT2_INITIAL_STATE == ENABLE
	SET_BIT(GICR,GICR_INT2);
	#elif INT2_INITIAL_STATE == DISABLE
	CLR_BIT(GICR,GICR_INT2);
	#else
	#error "Wrong INT2_INITIAL_STATE configuration option"
	#endif
}

ES_t EXTI_enuIntSetSenseControl(u8 Copy_u8Int, u8 Copy_u8Sense)
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_u8Sense == FALLING_EDGE)
	{
		switch(Copy_u8Int)
		{
			case INT0 : SET_BIT(MCUCR,MCUSR_ISC01); CLR_BIT(MCUCR,MCUSR_ISC00); break;
			case INT1 : SET_BIT(MCUCR,MCUSR_ISC11); CLR_BIT(MCUCR,MCUSR_ISC10); break;
			case INT2 : CLR_BIT(MCUCSR,MCUCSR_INT2); break;
			default : Local_enuErrorState = ES_NOK; break;
		}
	}
	else if(Copy_u8Sense == RISING_EDGE)
	{
		switch(Copy_u8Int)
		{
		case INT0 : SET_BIT(MCUCR,MCUSR_ISC01); SET_BIT(MCUCR,MCUSR_ISC00); break;
		case INT1 : SET_BIT(MCUCR,MCUSR_ISC11); SET_BIT(MCUCR,MCUSR_ISC10); break;
		case INT2 : SET_BIT(MCUCSR,MCUCSR_INT2); break;
		default : Local_enuErrorState = ES_NOK; break;			
		}
	}
	else if(Copy_u8Sense == ON_CHANGE)
	{
		switch(Copy_u8Int)
		{
		case INT0 : CLR_BIT(MCUCR,MCUSR_ISC01); SET_BIT(MCUCR,MCUSR_ISC00); break;
		case INT1 : CLR_BIT(MCUCR,MCUSR_ISC11); SET_BIT(MCUCR,MCUSR_ISC10); break;
		default : Local_enuErrorState = ES_NOK; break;			
		}
	}
	else if(Copy_u8Sense == LOW_LEVEL)
	{
		switch(Copy_u8Int)
		{
		case INT0 : CLR_BIT(MCUCR,MCUSR_ISC01); CLR_BIT(MCUCR,MCUSR_ISC00); break;
		case INT1 : CLR_BIT(MCUCR,MCUSR_ISC11); CLR_BIT(MCUCR,MCUSR_ISC10); break;
		default : Local_enuErrorState = ES_NOK; break;			
		}
	}
	else
	{
		Local_enuErrorState = ES_NOK;
	}
	
	return Local_enuErrorState;
}

ES_t EXTI_enuIntEnable(u8 Copy_u8Int)
{
	ES_t Local_enuErrorState = ES_OK;
	
	switch(Copy_u8Int)
	{
	case INT0: SET_BIT(GICR,GICR_INT0); break;
	case INT1: SET_BIT(GICR,GICR_INT1); break;
	case INT2: SET_BIT(GICR,GICR_INT2); break;
	default: Local_enuErrorState = ES_NOK; break;		
	}
	
	return Local_enuErrorState;
}

ES_t EXTI_enuIntDisable(u8 Copy_u8Int)
{
	ES_t Local_enuErrorState = ES_OK;
	
	switch(Copy_u8Int)
	{
	case INT0: CLR_BIT(GICR,GICR_INT0); break;
	case INT1: CLR_BIT(GICR,GICR_INT1); break;
	case INT2: CLR_BIT(GICR,GICR_INT2); break;
	default: Local_enuErrorState = ES_NOK; break;		
	}

	
	return Local_enuErrorState;
}

ES_t EXTI_enuSetInt0CallBack(void (*Copy_pvInt0Func)(void))
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_pvInt0Func != NULL)
	{
		EXTI_pvInt0Isr = Copy_pvInt0Func;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	
	return Local_enuErrorState;
}

void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if(EXTI_pvInt0Isr != NULL)
	{
		EXTI_pvInt0Isr();
	}
	else
	{
		//Do nothing
	}
}

ES_t EXTI_enuSetInt1CallBack(void (*Copy_pvInt1Func)(void))
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_pvInt1Func != NULL)
	{
		EXTI_pvInt1Isr = Copy_pvInt1Func;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	
	return Local_enuErrorState;
}

void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	if(EXTI_pvInt1Isr != NULL)
	{
		EXTI_pvInt1Isr();
	}
	else
	{
		//Do nothing
	}
}

ES_t EXTI_enuSetInt2CallBack(void (*Copy_pvInt2Func)(void))
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_pvInt2Func != NULL)
	{
		EXTI_pvInt2Isr = Copy_pvInt2Func;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	
	return Local_enuErrorState;
}

void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	if(EXTI_pvInt2Isr != NULL)
	{
		EXTI_pvInt2Isr();
	}
	else
	{
		//Do nothing
	}
}