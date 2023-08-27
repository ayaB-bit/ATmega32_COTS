/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: HAL          *********************************************/
/******************************************  SWC: LCD            *********************************************/
/******************************************  Version: 1.00       *********************************************/
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

ES_t LCD_enuInit(void);

ES_t LCD_enuSendChar(u8 Copy_u8Data);

ES_t LCD_enuSendCommand(u8 Copy_u8Command);

ES_t LCD_enuGoto(u8 Copy_u8Row, u8 Copy_u8Col);

ES_t LCD_enuDisplayEXtraChar(u8 Copy_u8CharArray[], u8 Copy_u8CharNum, u8 Copy_u8Row, u8 Copy_u8Col, u8 Copy_u8Direction);

ES_t LCD_enuSendString(u8* Copy_pu8String);

ES_t LCD_enuWriteNumber(f32 Copy_u8Num);

ES_t LCD_enuClear(void);


#endif