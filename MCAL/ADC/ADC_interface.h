/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: MCAL         *********************************************/
/******************************************  SWC: ADC            *********************************************/
/******************************************  Version: 1.00       *********************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

ES_t ADC_enuInit(void);

ES_t ADC_enuStartConversionSynch(u8 Copy_u8Channel, u16* Copy_u16Reading);

//Enable global interrupt before using this function
ES_t ADC_enuStartConversionAsynch(u8 Copy_u8Channel, u16* Copy_u16Reading, void(*Copy_pvNotificationFunc)(void));

s32 ADC_s32Mapping(s32 Copy_s32InputMin, s32 Copy_s32InputMax, s32 Copy_s32OutputMin, s32 Copy_s32OutputMax, s32 Copy_s32InputVal);



#endif