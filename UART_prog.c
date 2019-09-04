/*
 * UART_prog.c
 *
 *this file consist of function for UART Driver
 *
 *  Created on: Sep 3, 2019
 *  Modified on: Sep 4, 2019
 *      Author: Ahmed Eldakhly
 */

/*this file contain typedefs of Standard Data Types*/
#include "STDTYPES.h"
/*this file contain Macros Like function to set,clear and get specific bit in selected register */
#include "Macro.h"
/*this file contain enums,struct and function Prototypes for UART Driver*/
#include "UART_interfacing.h"
/*this file contain Register that belong to UART Peripheral*/
#include "USART_MEMORY_MAPING.h"
#include"DIO_interface.h"
#include"DIO_MemoryMaping.h"
/********************************************************************************************/
/****************************************************************************
* 1-func_Name: UART_Init.													*
*                                                             			    *
* 2-arguments:																*
* 		Input:																*
* 			Data type: typedef of user struct called  UART_conf_s			*
* 			this struct that contain the required parameters that needed to_*
* 			configure the UART peripheral by user 							*
* 		output: void                                 						*
*																			*
*3-Return:																	*
*	  DataType: enum status   												*
*	  description: the return value will be OK if function done 			*
*	  			  correctly or NOT_OK if happen something wrong.			*
*	                                                       				    *
*4-this function's role is initialize UART communicationby determine Baud_	*
*  rate,Baud rate mood,Data size,Number of stop bits,Parity Mood and_		*
*  interrupts mood.															*
*																			*
*****************************************************************************/
Status_t UART_Init(UART_conf_s const a_Init_Var)
{
	Status_t ReturnValue=NOT_OK;
	/*select Baud rate mood*/
	if((a_Init_Var.Init_DoubleSpeed)==Dou_Speed)
	{
		SetBit(USART_UCSRA,Bit_U2X);
		USART_BaudRateLow=a_Init_Var.BuadRate;
		ClearBit(USART_BaudRateHigh,SelectRegister_URSEL);
		USART_BaudRateHigh=((a_Init_Var.BuadRate)>>8);
		ReturnValue=OK;
	}
	else if((a_Init_Var.Init_DoubleSpeed)==NormalSpeed)
	{
		ClearBit(USART_UCSRA,Bit_U2X);
		USART_BaudRateLow=a_Init_Var.BuadRate;
		ReturnValue=OK;
	}
	else
		ReturnValue=NOT_OK;
	/*select parity mood*/
	switch(a_Init_Var.Init_Parity)
	{
	case NoParity:
		USART_UCSRC=(USART_UCSRC|0x80)&(~(1<<Bit0_UPM0))&(~(1<<Bit1_UPM1));
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case EvenParity:
		USART_UCSRC=(USART_UCSRC|0xA0)&(~(1<<Bit0_UPM0));
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case OddParity:
		USART_UCSRC=(USART_UCSRC|0xB0);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	default:
		ReturnValue=NOT_OK;
	}
	/*select number of stop bits*/
	if(a_Init_Var.Init_Stop==OneStopBit)
	{
		USART_UCSRC=(USART_UCSRC|0x80)&(~(1<<StopBits_USBS));
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else if(a_Init_Var.Init_Stop==TwoStopBit)
	{
		USART_UCSRC=(USART_UCSRC|0x88);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else
		ReturnValue=NOT_OK;
	/*select data size*/
	switch(a_Init_Var.Init_DataSize)
	{
	case _5_bit:
		USART_UCSRC=(USART_UCSRC|0x80)&(~(1<<Bit0_UCSZ0))&(~(1<<Bit1_UCSZ1));
		ClearBit(USART_UCSRB,Bit2_UCSZ2);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case _6_bit:
		USART_UCSRC=(USART_UCSRC|0x82)&(~(1<<Bit1_UCSZ1));
		ClearBit(USART_UCSRB,Bit2_UCSZ2);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case _7_bit:
		USART_UCSRC=(USART_UCSRC|0x84)&(~(1<<Bit0_UCSZ0));
		ClearBit(USART_UCSRB,Bit2_UCSZ2);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case _8_bit:
		USART_UCSRC=(USART_UCSRC|0x86);
		ClearBit(USART_UCSRB,Bit2_UCSZ2);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case _9_bit:
		USART_UCSRC=(USART_UCSRC|0x86);
		SetBit(USART_UCSRB,Bit2_UCSZ2);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	default:
		ReturnValue=NOT_OK;
	}
	/*enable or disable empty data register interrupt*/
	if(a_Init_Var.Init_Em)
	{
		ClearBit(USART_UCSRB,InterruptEnable_UDRIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else if((a_Init_Var.Init_Em)==EnableEM)
	{
		SetBit(USART_UCSRB,InterruptEnable_UDRIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else
		ReturnValue=NOT_OK;
	/*enable or disable transmitter interrupt*/
	if(a_Init_Var.Init_TX)
	{
		ClearBit(USART_UCSRB,InterruptEnable_TXCIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else if((a_Init_Var.Init_TX)==EnableTX)
	{
		SetBit(USART_UCSRB,InterruptEnable_TXCIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else
		ReturnValue=NOT_OK;
	/*enable or disable receiver interrupt*/
	if(a_Init_Var.Init_RX)
	{
		ClearBit(USART_UCSRB,InterruptEnable_RXCIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else if((a_Init_Var.Init_RX)==EnableRX)
	{
		SetBit(USART_UCSRB,InterruptEnable_RXCIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else
		ReturnValue=NOT_OK;

	return ReturnValue;
}
/********************************************************************************************/
/****************************************************************************
* 1-func_Name: UART_ReceiveChar.											*
*                                                             			    *
* 2-arguments:																*
* 		Input: void                                 						*
* 		Output:																*
* 			Data type: pointer to uint8										*
* 			this pointer points to data that receive by UART				*
*																			*
*3-Return:																	*
*	  DataType: enum status   												*
*	  description: the return value will be OK if function done 			*
*	  			  correctly or NOT_OK if happen something wrong.			*
*	                                                       				    *
*4-this function's role is return data that is received by UART				*
*																			*
*****************************************************************************/
Status_t UART_ReceiveChar(uint8* a_data_ptr)
{
	uint16 dummy;
	Status_t ReturnValue;
	/*check if pulling is selected*/
	if(!(GetBit(USART_UCSRB,InterruptEnable_RXCIE)))
		/*pull on receive flag*/
		while(!(GetBit(USART_UCSRA,Flag_RXC)));
	/*get Data from data register of UART*/
	if(USART_UCSRA&((1<<Flag_PE)|(1<<Flag_DOR)|(1<<Flag_FE)))
	{
		dummy=USART_DataRegister;
		ReturnValue=NOT_OK;
	}
	else
	{
		*a_data_ptr=USART_DataRegister;
		ReturnValue=OK;
	}
	return ReturnValue;
}
/********************************************************************************************/
/****************************************************************************
* 1-func_Name: UART_SendChar.												*
*                                                             			    *
* 2-arguments:																*
* 		Input:																*
* 			Data type:uint8													*
* 			this data that send from user by UART Protocol					*
* 		Output: void                                 						*
*																			*
*3-Return:																	*
*	  DataType: enum status   												*
*	  description: the return value will be OK if function done 			*
*	  			  correctly or NOT_OK if happen something wrong.			*
*	                                                       				    *
*4-this function's role is send data from user by UART						*
*																			*
*****************************************************************************/
Status_t UART_SendChar(uint8 a_data)
{
	Status_t ReturnValue;
	/*check if pulling is selected*/
	if(!(GetBit(USART_UCSRB,InterruptEnable_UDRIE)))
		/*pull on empty Data register flag*/
		while(!(GetBit(USART_UCSRA,Flag_UDRE)));
	/*put Data on data register of UART*/
	if(GetBit(USART_UCSRB,Enable_TXEN))
	{
		USART_DataRegister=a_data;
		ReturnValue=OK;
	}
	else
		ReturnValue=NOT_OK;
	return ReturnValue;
}
/********************************************************************************************/
/****************************************************************************
* 1-func_Name: UART_Receive.												*
*                                                             			    *
* 2-arguments:																*
* 		Input: void                                 						*
* 		Output:																*
* 			Data type: pointer to uint8										*
* 			this pointer points to string that receive by UART				*
*																			*
*3-Return:																	*
*	  DataType: enum status   												*
*	  description: the return value will be OK if function done 			*
*	  			  correctly or NOT_OK if happen something wrong.			*
*	                                                       				    *
*4-this function's role is return string that is received by UART			*
*																			*
*****************************************************************************/
Status_t UART_Receive(const uint8* a_data_ptr)
{
	Status_t ReturnValue;
	/*Loop to Receive string by UART*/
	for(uint8 Count=0;a_data_ptr[Count-1]!='\n';Count++)
	{
		ReturnValue=UART_ReceiveChar(&(a_data_ptr[Count]));
		if(!(ReturnValue))
			return ReturnValue;
	}
	return ReturnValue;
}
/********************************************************************************************/
/****************************************************************************
* 1-func_Name: UART_Send.													*
*                                                             			    *
* 2-arguments:																*
* 		Input:																*
* 			Data type:Pointer to uint8										*
* 			this string that send from user by UART Protocol				*
* 		Output: void                                 						*
*																			*
*3-Return:																	*
*	  DataType: enum status   												*
*	  description: the return value will be OK if function done 			*
*	  			  correctly or NOT_OK if happen something wrong.			*
*	                                                       				    *
*4-this function's role is send string from user by UART					*
*																			*
*****************************************************************************/
Status_t UART_Send(uint8* a_data_ptr)
{
	Status_t ReturnValue;
	/*Loop on string to send by UART*/
	for(uint8 Count=0;a_data_ptr[Count]!='\n';Count++)
	{
		ReturnValue=UART_SendChar((a_data_ptr[Count]));
		if(!(ReturnValue))
			return ReturnValue;
	}
	return ReturnValue;
}
/********************************************************************************************/
/****************************************************************
 * 1-func_Name:UART_StartComm.									*
 *                                                              *
 * 2-arguments:													*
 * 		Input: void												*
 * 		output: void                                 			*
 *																*
 *3-Return:														*
 *	  DataType: enum status   									*
 *	  description: the return value will be OK if function done *
 *	  			  correctly or NOT_OK if happen something wrong.*
 *	                                                            *
 *4-this function's role is starting UART communication_		*
 *  by Set Enable Bits for receive and transmit.				*
 *																*
 * **************************************************************/
Status_t UART_StartComm(void)
{
	Status_t ReturnValue;
	SetBit(USART_UCSRB,Enable_TXEN);
	SetBit(USART_UCSRB,Enable_RXEN);
	if((GetBit(USART_UCSRB,Enable_TXEN)))
	{
		if((GetBit(USART_UCSRB,Enable_RXEN)))
			ReturnValue=OK;
		else
			ReturnValue=NOT_OK;
	}
	else
		ReturnValue=NOT_OK;
	return ReturnValue;

}
/********************************************************************************************/
/****************************************************************
 * 1-func_Name:UART_StopComm.									*
 *                                                              *
 * 2-arguments:													*
 * 		Input: void												*
 * 		output: void                                 			*
 *																*
 *3-Return:														*
 *	  DataType: enum status   									*
 *	  description: the return value will be OK if function done *
 *	  			  correctly or NOT_OK if happen something wrong.*
 *	                                                            *
 *4-this function's role is stopping UART communication_		*
 *  by Clear Enable Bits for receive and transmit.				*
 *																*
 * **************************************************************/
Status_t UART_StopComm(void)
{
	Status_t ReturnValue;
	while((GetBit(USART_UCSRA,Flag_UDRE))==0);
	ClearBit(USART_UCSRB,Enable_TXEN);
	ClearBit(USART_UCSRB,Enable_RXEN);
	if(!(GetBit(USART_UCSRB,Enable_TXEN)))
	{
		if(!(GetBit(USART_UCSRB,Enable_RXEN)))
			ReturnValue=OK;
		else
			ReturnValue=NOT_OK;
	}
	else
		ReturnValue=NOT_OK;
	return ReturnValue;
}

