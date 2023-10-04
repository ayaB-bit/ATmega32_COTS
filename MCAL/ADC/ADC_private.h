/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: MCAL         *********************************************/
/******************************************  SWC: ADC            *********************************************/
/******************************************  Version: 1.00       *********************************************/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

//ADC multiplexer selection register
#define ADMUX                  *((volatile u8*)0x27)
#define ADMUX_REFS1            7
#define ADMUX_REFS0            6
#define ADMUX_ADLAR            5
#define ADMUX_MUX4             4
#define ADMUX_MUX3             3
#define ADMUX_MUX2             2
#define ADMUX_MUX1             1
#define ADMUX_MUX0             0

//ADC control & status register
#define ADCSRA                 *((volatile u8*)0x26)
#define ADCSRA_ADEN            7
#define ADCSRA_ADSC            6
#define ADCSRA_ADATE           5
#define ADCSRA_ADIF	           4
#define ADCSRA_ADIE	           3
#define ADCSRA_ADPS2           2
#define ADCSRA_ADPS1           1
#define ADCSRA_ADPS0           0
						     
#define ADCH                   *((volatile u8*)0x25)
#define ADCL                   *((volatile u8*)0x24)

#define ACD_PRESCALER_MASK     0xf8

#define AREF                   0
#define AVCC                   1
#define INTERNAL_VREF          2

#define ENABLED                0
#define DISABLED               1
						    
#define DIV_BY_2               1
#define DIV_BY_4			   2
#define DIV_BY_8			   3
#define DIV_BY_16			   4
#define DIV_BY_32			   5
#define DIV_BY_64			   6
#define DIV_BY_128             7

#define ACD_MULTIBLEXER_MASK   0xE0

#define IDLE                   0
#define BUSY                   1

#endif