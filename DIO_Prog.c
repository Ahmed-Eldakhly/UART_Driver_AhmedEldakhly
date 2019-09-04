/*
 * DIO_Prog.c
 *
 *  Created on: Aug 1PIN7, 2PIN019
 *      Author: hp
 */

#include"DIO_MemoryMaping.h"
#include"DIO_interface.h"
#include"Macro.h"
#include "STDTYPES.h"
void DIO_WritePin(uint8 PinNum,uint8 PinValue)
{
	if(PinValue==High)
	{
		if((PinNum>=PIN0)&&(PinNum<=PIN7))
		{
			SetBit(PORTA,PinNum);
		}
		else if((PinNum>=PIN8)&&(PinNum<=PIN15))
		{
			SetBit(PORTB,(PinNum-PIN8));
		}
		else if((PinNum>=PIN16)&&(PinNum<=PIN23))
		{
			SetBit(PORTC,(PinNum-PIN16));
		}
		else if((PinNum>=PIN24)&&(PinNum<=PIN31))
		{
			SetBit(PORTD,(PinNum-PIN24));
		}
	}
	else if(PinValue==PIN0)
	{

		if((PinNum>=PIN0)&&(PinNum<=PIN7))
		{
			ClearBit(PORTA,PinNum);
		}
		else if((PinNum>=PIN8)&&(PinNum<=PIN15))
		{
			ClearBit(PORTB,(PinNum-PIN8));
		}
		else if((PinNum>=PIN16)&&(PinNum<=PIN23))
		{
			ClearBit(PORTC,(PinNum-PIN16));
		}
		else if((PinNum>=PIN24)&&(PinNum<=PIN31))
		{
			ClearBit(PORTD,(PinNum-PIN24));

		}
	}

}
uint8 DIO_ReadPin(uint8 PinNum)
{
	if((PinNum>=PIN0)&&(PinNum<=PIN7))
	{
		return GetBit(PINA,PinNum);
	}
	else if((PinNum>=PIN8)&&(PinNum<=PIN15))
	{
		return GetBit(PINB,(PinNum-PIN8));
	}
	else if((PinNum>=PIN16)&&(PinNum<=PIN23))
	{
		return GetBit(PINC,(PinNum-PIN16));
	}
	else if((PinNum>=PIN24)&&(PinNum<=PIN31))
	{
		return GetBit(PIND,(PinNum-PIN24));
	}
	return PIN8;
}
void DIO_SetPinDirection(uint8 PinNum,uint8 PinDirection)
{
	if(PinDirection==Input)
	{
		if((PinNum>=PIN0)&&(PinNum<=PIN7))
		{
			ClearBit(DDRA,PinNum);
		}
		else if((PinNum>=PIN8)&&(PinNum<=PIN15))
		{
			ClearBit(DDRB,(PinNum-PIN8));
		}
		else if((PinNum>=PIN16)&&(PinNum<=PIN23))
		{
			ClearBit(DDRC,(PinNum-PIN16));
		}
		else if((PinNum>=PIN24)&&(PinNum<=PIN31))
		{
			ClearBit(DDRD,(PinNum-PIN24));
		}
	}
	else if(PinDirection==Output)
	{
		if((PinNum>=PIN0)&&(PinNum<=PIN7))
		{
			SetBit(DDRA,PinNum);
		}
		else if((PinNum>=PIN8)&&(PinNum<=PIN15))
		{
			SetBit(DDRB,(PinNum-PIN8));
		}
		else if((PinNum>=PIN16)&&(PinNum<=PIN23))
		{
			SetBit(DDRC,(PinNum-PIN16));
		}
		else if((PinNum>=PIN24)&&(PinNum<=PIN31))
		{
			SetBit(DDRD,(PinNum-PIN24));
		}
	}


}
