/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: MCAL         *********************************************/
/******************************************  SWC: EXTI           *********************************************/
/******************************************  Version: 1.00       *********************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define FALLING_EDGE   1
#define RISING_EDGE    2
#define ON_CHANGE      3
#define LOW_LEVEL      4

void EXTI_voidInt0Init(void);

void EXTI_voidInt1Init(void);

void EXTI_voidInt2Init(void);

ES_t EXTI_enuIntSetSenseControl(u8 Copy_u8Int, u8 Copy_u8Sense);

ES_t EXTI_enuIntEnable(u8 Copy_u8Int);

ES_t EXTI_enuIntDisable(u8 Copy_u8Int);

ES_t EXTI_enuSetInt0CallBack(void (*Copy_pvInt0Func)(void));

ES_t EXTI_enuSetInt1CallBack(void (*Copy_pvInt1Func)(void));

ES_t EXTI_enuSetInt2CallBack(void (*Copy_pvInt2Func)(void));

#endif