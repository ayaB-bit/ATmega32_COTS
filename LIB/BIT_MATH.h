#ifndef BIT_MATH_H_
#define BIT_MATH_H_



// SET BITNUM AT REG HIGH
#define SET_BIT(REG , BITNUM)     (REG |= (1<<BITNUM))


// CLER BITNUM AT REG TO LOW
#define CLR_BIT(REG , BITNUM)     (REG &= (~(1<<BITNUM)))

//XOR
// CHANGE VALUE OF BITNUM AT REG 
#define TOGGLE_BIT(REG , BITNUM)   (REG ^= (1<<BITNUM))


// GET BIT VALUE 
#define GET_BIT(REG,BITNUM)        (((REG) >> (BITNUM)) & (0x01))




#endif