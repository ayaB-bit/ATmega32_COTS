/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: MCAL         *********************************************/
/******************************************  SWC: DIO            *********************************************/
/******************************************  Version: 1.00       *********************************************/

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/*
//pin direction
#define DIO_u8PIN_OUTPUT   1
#define DIO_u8PIN_INPUT    0
//pin value
#define DIO_u8PIN_HIGH     1
#define DIO_u8PIN_LOW      0
//port direction
#define DIO_u8PORT_OUTPUT  0xFF
#define DIO_u8PORT_INPUT   0x00
//port value
#define DIO_u8PORT_HIGH    0xFF
#define DIO_u8PORT_LOW     0x00
*/
//ports
#define DIO_PORTA        0
#define DIO_PORTB        1
#define DIO_PORTC        2
#define DIO_PORTD        3
//pins
#define DIO_PIN0         0
#define DIO_PIN1         1
#define DIO_PIN2         2
#define DIO_PIN3         3
#define DIO_PIN4         4
#define DIO_PIN5         5
#define DIO_PIN6         6
#define DIO_PIN7         7

//#define INPUT     0
//#define OUTPUT    1

#define LOW       0
#define HIGH      1

#define FLOAT     0
#define PULL_UP   1

#define PORTA     *((volatile u8*)0x3B)
#define PINA      *((volatile u8*)0x39)

#define PORTB     *((volatile u8*)0x38)
#define PINB      *((volatile u8*)0x36)

#define PORTC     *((volatile u8*)0x35)
#define PINC      *((volatile u8*)0x33)

#define PORTD     *((volatile u8*)0x32)
#define PIND      *((volatile u8*)0x30)


#endif