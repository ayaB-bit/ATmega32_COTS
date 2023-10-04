/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: MCAL         *********************************************/
/******************************************  SWC: EXTI           *********************************************/
/******************************************  Version: 1.00       *********************************************/

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/*Options:
          1- FALLING_EDGE
          2- RISING_EDGE
		  3- ON_CHANGE
          4- LOW_LEVEL 
*/
#define INT0_SENSE             FALLING_EDGE
#define INT1_SENSE			   FALLING_EDGE
#define INT2_SENSE			   RISING_EDGE

#define INT0_INITIAL_STATE     ENABLE 
#define INT1_INITIAL_STATE     ENABLE
#define INT2_INITIAL_STATE     ENABLE

#endif