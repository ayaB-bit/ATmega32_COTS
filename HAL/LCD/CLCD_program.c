/*************************************************************************************************************/
/*************************************************************************************************************/
/******************************************  Author: Aya Bedair  *********************************************/
/******************************************  Layer: HAL          *********************************************/
/******************************************  SWC: LCD            *********************************************/
/******************************************  Version: 1.00       *********************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERROR_STATE.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"

#include "util/delay.h"

u8 cursor=0;

ES_t LCD_enuInit(void)
{
	ES_t Local_enuErrorState = ES_OK;
	
	_delay_ms(40);
	
	//func set 0011NFXX
	#if LCD_MODE == EIGHT_BIT
	//EIGHT_BIT
	LCD_invidSendCommand(0x38);  //001110xx
	#elif LCD_MODE == FOUR_BIT
	//FOUR_BIT
	LCD_invidSendCommand(0x28);  //001010xx
	#endif
	
	_delay_ms(1);
	//display on/off 00001DCB
	LCD_invidSendCommand(0x0f);  //00001111
	_delay_ms(1);
	//display clear 00000001
	LCD_invidSendCommand(0x01);
	_delay_ms(2);
	//entry mode 000001 ID SH
	#if DIRECTION == LEFT_TO_RIGHT
	LCD_invidSendCommand(0X06);  //00000110
	#elif DIRECTION == RIGHT_TO_LEFT
	LCD_invidSendCommand(0x04);  //00000101
	LCD_invidSendCommand(0x8f);
	#endif
	
	return Local_enuErrorState;
}

ES_t LCD_enuSendChar(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_OK;
	//set rs
	DIO_enuSetPinValue(RS_PORT, RS_PIN, DIO_u8HIGH);
	
	LCD_vidLatch(Copy_u8Data);
	
	cursor++;
	if(cursor==16)
	{
		if(DIRECTION == LEFT_TO_RIGHT)
		LCD_invidSendCommand(0xc0);
		else
		LCD_invidSendCommand(0xcf);
	}
	
	return Local_enuErrorState;
}

ES_t LCD_enuSendCommand(u8 Copy_u8Command)
{
	ES_t Local_enuErrorState = ES_OK;
	//set rs
	DIO_enuSetPinValue(RS_PORT, RS_PIN, DIO_u8LOW);
	
	LCD_vidLatch(Copy_u8Command);
	
	return Local_enuErrorState;
}

ES_t LCD_enuGoTo(u8 Copy_u8Row, u8 Copy_u8Col)
{
	ES_t Local_enuErrorState = ES_OK;

	if (Copy_u8Row == 0)
	{
		LCD_invidSendCommand(0x80 + Copy_u8Col);
	}
	else if(Copy_u8Row == 1)
	{
		LCD_invidSendCommand(0xc0 +Copy_u8Col);
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t LCD_enuDisplayEXtraChar(u8 Copy_u8CharArray[], u8 Copy_u8CharNum, u8 Copy_u8Row, u8 Copy_u8Col, u8 Copy_u8Direction)
{
	ES_t Local_enuErrorState = ES_OK;
	
	//go to CGRAM
	LCD_invidSendCommand(PAT0);
	//send to CGRAM
	for(u8 i=0;i<(8*Copy_u8CharNum);i++)
	LCD_vidLatch(Copy_u8CharArray[i]);
	//go to DDRAM
	LCD_enuGoTo( Copy_u8Row, Copy_u8Col);
	LCD_invidSendCommand(Copy_u8Direction);
	//
	for(u8 i=0;i<Copy_u8CharNum;i++)
	LCD_vidLatch(i);
	
	return Local_enuErrorState;
}

ES_t LCD_enuSendString(u8* Copy_pu8String)
{
	ES_t Local_enuErrorState = ES_OK;
	
	while (*Copy_pu8String) 
	{
		LCD_vidLatch(*Copy_pu8String);
		Copy_pu8String++;
	}
	
	return Local_enuErrorState;
}

ES_t LCD_enuWriteNumber(f32 Copy_u8Num)
{
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_u8Num == 0.0)
	{
		LCD_vidLatch('0');
		return Local_enuErrorState;
	}

	static u8 Local_Au8Digits[16] = {'0'};
	s8 Local_u8Iterator = -1;
	s32 Local_s32Number = Copy_u8Num;
	if(Copy_u8Num < 0 )
	{
		LCD_vidLatch('-');
		Local_s32Number *= -1;
	}

	if((Copy_u8Num < 1.0 && Copy_u8Num > 0.0) || (Copy_u8Num > -1.0 && Copy_u8Num < 0.0)) LCD_enuSendChar('0');

	while (Local_s32Number > 0)
	{
		Local_u8Iterator++;
		Local_Au8Digits[Local_u8Iterator] = Local_s32Number % 10;
		Local_s32Number /= 10;
	}

	while( Local_u8Iterator >= 0)
	{
		LCD_vidLatch( Local_Au8Digits[Local_u8Iterator] + '0');
		Local_u8Iterator--;
	}

	Copy_u8Num = (Copy_u8Num - (s32)Copy_u8Num);
	if(Copy_u8Num != 0.0)
	{
		LCD_vidLatch('.');
		if(Copy_u8Num < 0) Copy_u8Num *= -1;
		u16 base = 10;
		while (base <= 10000)
		{
			Local_u8Iterator++;
			Local_Au8Digits[3 - Local_u8Iterator] = ((s32)(Copy_u8Num*base))%10;
			base *= 10;
		}

		while( Local_u8Iterator >= 0 )
		{
			LCD_vidLatch( Local_Au8Digits[Local_u8Iterator] + '0');
			Local_u8Iterator--;
		}

	}

	return Local_enuErrorState;
}


ES_t LCD_enuClear(void)
{
	ES_t Local_enuErrorState = ES_OK;
	
	LCD_invidSendCommand(0x01);
	
	return Local_enuErrorState;
}

static inline void LCD_vidLatch(u8 Copy_u8Data)
{
	DIO_enuSetPinValue(RS_PORT, RS_PIN, DIO_u8HIGH );
	//set rw, EN low
	DIO_enuSetPinValue(RW_PORT, RW_PIN, DIO_u8LOW);
	DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8LOW);
	//write data
	DIO_enuSetPinValue(D7_PORT, D7_PIN, ((Copy_u8Data)>>7)&1);
	DIO_enuSetPinValue(D6_PORT, D6_PIN, ((Copy_u8Data)>>6)&1);
	DIO_enuSetPinValue(D5_PORT, D5_PIN, ((Copy_u8Data)>>5)&1);
	DIO_enuSetPinValue(D4_PORT, D4_PIN, ((Copy_u8Data)>>4)&1);
#if LCD_MODE == EIGHT_BIT
	DIO_enuSetPinValue(D3_PORT, D3_PIN, ((Copy_u8Data)>>3)&1);
	DIO_enuSetPinValue(D2_PORT, D2_PIN, ((Copy_u8Data)>>2)&1);
	DIO_enuSetPinValue(D1_PORT, D1_PIN, ((Copy_u8Data)>>1)&1);
	DIO_enuSetPinValue(D0_PORT, D0_PIN, ((Copy_u8Data)>>0)&1);
#elif LCD_MODE == FOUR_BIT
	
#endif
	//EN latch
	DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8HIGH);
	_delay_ms(10);
	DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8LOW);
}

static inline void LCD_invidSendCommand(u8 Copy_u8Command)
{
	
	//set rs
	DIO_enuSetPinValue(RS_PORT, RS_PIN, DIO_u8LOW);
	//set rw, EN low
	DIO_enuSetPinValue(RW_PORT, RW_PIN, DIO_u8LOW);
	DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8LOW);
	//write data
	DIO_enuSetPinValue(D7_PORT, D7_PIN, ((Copy_u8Command)>>7)&1);
	DIO_enuSetPinValue(D6_PORT, D6_PIN, ((Copy_u8Command)>>6)&1);
	DIO_enuSetPinValue(D5_PORT, D5_PIN, ((Copy_u8Command)>>5)&1);
	DIO_enuSetPinValue(D4_PORT, D4_PIN, ((Copy_u8Command)>>4)&1);
	DIO_enuSetPinValue(D3_PORT, D3_PIN, ((Copy_u8Command)>>3)&1);
	DIO_enuSetPinValue(D2_PORT, D2_PIN, ((Copy_u8Command)>>2)&1);
	DIO_enuSetPinValue(D1_PORT, D1_PIN, ((Copy_u8Command)>>1)&1);
	DIO_enuSetPinValue(D0_PORT, D0_PIN, ((Copy_u8Command)>>0)&1);
	//EN latch
	DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8HIGH);
	_delay_ms(10);
	DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8LOW);
}
