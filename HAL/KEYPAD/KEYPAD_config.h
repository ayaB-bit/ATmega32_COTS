/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: HAL          *********************************************/
/******************************************  SWC: KEYPAD         *********************************************/
/******************************************  Version: 1.00       *********************************************/

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define KEYPAD_ARRAY_VAL  {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'c','0','=','+'}}

//ROW PORTS
#define R1_PORT		DIO_u8PORTC
#define R2_PORT		DIO_u8PORTC
#define R3_PORT		DIO_u8PORTC
#define R4_PORT		DIO_u8PORTC
//ROWS PINS
#define R1_PIN      DIO_u8PIN0
#define R2_PIN      DIO_u8PIN1
#define R3_PIN      DIO_u8PIN2
#define R4_PIN      DIO_u8PIN3

//COL PORTS
#define C1_PORT		DIO_u8PORTC
#define C2_PORT		DIO_u8PORTC
#define C3_PORT		DIO_u8PORTC
#define C4_PORT		DIO_u8PORTC
//COL PINS
#define C1_PIN      DIO_u8PIN4
#define C2_PIN      DIO_u8PIN5
#define C3_PIN      DIO_u8PIN6
#define C4_PIN      DIO_u8PIN7

#define NO_PRESSED_KEY    0xff

#endif