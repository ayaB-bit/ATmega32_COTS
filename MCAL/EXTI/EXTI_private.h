/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: MCAL         *********************************************/
/******************************************  SWC: EXTI           *********************************************/
/******************************************  Version: 1.00       *********************************************/

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define INT0           1
#define INT1           2
#define INT2           3
//General Interrupt Control Reg
#define GICR           *((volatile u8*)0x5B)
#define GICR_INT0      6
#define GICR_INT1      7
#define GICR_INT2      5 

//General Interrupt Flag Reg		  
#define GIFR           *((volatile u8*)0X5A)

//MCU Control Reg		  
#define MCUCR          *((volatile u8*)0X55)
#define MCUSR_ISC11    3   //INT1
#define MCUSR_ISC10    2
#define MCUSR_ISC01    1   //INT0
#define MCUSR_ISC00    0

//MCU Control & Status Reg			  
#define MCUCSR         *((volatile u8*)0X54)
#define MCUCSR_INT2    6   //INT2

#define ENABLE         1
#define DISABLE        2

#endif