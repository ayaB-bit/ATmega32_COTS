/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: HAL          *********************************************/
/******************************************  SWC: LCD            *********************************************/
/******************************************  Version: 1.00       *********************************************/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/*  Patterns addresses  */
#define PAT0    0x40
#define PAT1    0x48
#define PAT2    0x50
#define PAT3    0x58
#define PAT4    0x60
#define PAT5    0x68
#define PAT6    0x70
#define PAT7    0x78

/*  LCD MODE   */
#define LCD_MODE    EIGHT_BIT

#define DIRECTION   LEFT_TO_RIGHT

/*  ctrl pins  */
#define RS_PORT   DIO_u8PORTD
#define RS_PIN    DIO_u8PIN0

#define RW_PORT   DIO_u8PORTD
#define RW_PIN	  DIO_u8PIN1

#define EN_PORT   DIO_u8PORTD
#define EN_PIN	  DIO_u8PIN2

/*  data pins */
#define D0_PORT   DIO_u8PORTC
#define D0_PIN	  DIO_u8PIN0

#define D1_PORT	  DIO_u8PORTC
#define D1_PIN	  DIO_u8PIN1

#define D2_PORT	  DIO_u8PORTC
#define D2_PIN	  DIO_u8PIN2

#define D3_PORT   DIO_u8PORTC
#define D3_PIN	  DIO_u8PIN3

#define D4_PORT	  DIO_u8PORTC
#define D4_PIN	  DIO_u8PIN4

#define D5_PORT	  DIO_u8PORTC
#define D5_PIN	  DIO_u8PIN5

#define D6_PORT   DIO_u8PORTC
#define D6_PIN	  DIO_u8PIN6

#define D7_PORT	  DIO_u8PORTC
#define D7_PIN	  DIO_u8PIN7

#endif			