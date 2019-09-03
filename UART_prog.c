/*
 * UART_prog.c
 *
 *  Created on: Sep 3, 2019
 *      Author: hp
 */

#include "STDTYPES.h"
#include "Macro.h"
#include "UART_interfacing.h"
#include "USART_MEMORY_MAPING.h"

Status_t UART_Init(UART_conf_s* a_Init_Var_ptr)
{
	Status_t ReturnValue=NOT_OK;
	if(a_Init_Var_ptr->Init_DoubleSpeed)
	{
		Set_Bit(USART_Status_Register_A_UCSRA,Double_Speed_Bit_U2X);
		USART_Baud_Rate_Select_Low_Register=(uint8)416;
		Clear_Bit(USART_Baud_Rate_Select_High_Register,Select_UBRRH_Register_URSEL);
		USART_Baud_Rate_Select_High_Register=(416>>8);
		ReturnValue=OK;
	}

	else
	{
		Clear_Bit(USART_Status_Register_A_UCSRA,Double_Speed_Bit_U2X);
		USART_Baud_Rate_Select_Low_Register=a_Init_Var_ptr->BuadRate;
		ReturnValue=OK;
	}
	switch(a_Init_Var_ptr->Init_Parity)
	{
	case NoParity:
		USART_Status_Register_C_UCSRC=(USART_Status_Register_C_UCSRC|0x80)&(~(1<<Parity_Mode_Select_Bit0_UPM0))&(~(1<<Parity_Mode_Select_Bit1_UPM1));
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case EvenParity:
		USART_Status_Register_C_UCSRC=(USART_Status_Register_C_UCSRC|0xA0)&(~(1<<Parity_Mode_Select_Bit0_UPM0));
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case OddParity:
		USART_Status_Register_C_UCSRC=(USART_Status_Register_C_UCSRC|0xB0);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	}

	if(a_Init_Var_ptr->Init_Stop==OneStopBit)
	{
		USART_Status_Register_C_UCSRC=(USART_Status_Register_C_UCSRC|0x80)&(~(1<<Select_Number_of_Stop_Bits_USBS));
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else if(a_Init_Var_ptr->Init_Stop==TwoStopBit)
	{
		USART_Status_Register_C_UCSRC=(USART_Status_Register_C_UCSRC|0x88);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	switch(a_Init_Var_ptr->Init_DataSize)
	{
	case _5_bit:
		USART_Status_Register_C_UCSRC=(USART_Status_Register_C_UCSRC|0x80)&(~(1<<Data_Size_Select_Bit0_UCSZ0))&(~(1<<Data_Size_Select_Bit1_UCSZ1));
		Clear_Bit(USART_Status_Register_B_UCSRB,Data_Size_Select_Bit2_UCSZ2);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case _6_bit:
		USART_Status_Register_C_UCSRC=(USART_Status_Register_C_UCSRC|0x82)&(~(1<<Data_Size_Select_Bit1_UCSZ1));
		Clear_Bit(USART_Status_Register_B_UCSRB,Data_Size_Select_Bit2_UCSZ2);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case _7_bit:
		USART_Status_Register_C_UCSRC=(USART_Status_Register_C_UCSRC|0x84)&(~(1<<Data_Size_Select_Bit0_UCSZ0));
		Clear_Bit(USART_Status_Register_B_UCSRB,Data_Size_Select_Bit2_UCSZ2);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case _8_bit:
		USART_Status_Register_C_UCSRC=(USART_Status_Register_C_UCSRC|0x86);
		Clear_Bit(USART_Status_Register_B_UCSRB,Data_Size_Select_Bit2_UCSZ2);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	case _9_bit:
		USART_Status_Register_C_UCSRC=(USART_Status_Register_C_UCSRC|0x86);
		Set_Bit(USART_Status_Register_B_UCSRB,Data_Size_Select_Bit2_UCSZ2);
		if(ReturnValue==OK)
			ReturnValue=OK;
		break;
	}
	if(a_Init_Var_ptr->Init_Em)
	{
		Clear_Bit(USART_Status_Register_B_UCSRB,USART_Data_Register_Empty_Interrupt_Enable_UDRIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else
	{
		Set_Bit(USART_Status_Register_B_UCSRB,USART_Data_Register_Empty_Interrupt_Enable_UDRIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	if(a_Init_Var_ptr->Init_TX)
	{
		Clear_Bit(USART_Status_Register_B_UCSRB,USART_Transmit_Complete_Interrupt_Enable_TXCIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else
	{
		Set_Bit(USART_Status_Register_B_UCSRB,USART_Transmit_Complete_Interrupt_Enable_TXCIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	if(a_Init_Var_ptr->Init_RX)
	{
		Clear_Bit(USART_Status_Register_B_UCSRB,USART_Receive_Complete_Interrupt_Enable_RXCIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	else
	{
		Set_Bit(USART_Status_Register_B_UCSRB,USART_Receive_Complete_Interrupt_Enable_RXCIE);
		if(ReturnValue==OK)
			ReturnValue=OK;
	}
	return ReturnValue;
}

Status_t UART_ReceiveChar(uint8* a_data_ptr)
{
	uint16 dummy;
	Status_t ReturnValue;
	if(USART_Status_Register_A_UCSRA&((1<<Parity_Error_Flag_PE)|(1<<Data_OverRun_Flag_DOR)|(1<<Frame_Error_Flag_FE)))
	{
		dummy=USART_Data_Register;
		ReturnValue=NOT_OK;
	}
	else
	{
		*a_data_ptr=USART_Data_Register;
		ReturnValue=OK;
	}
	return ReturnValue;
}

Status_t UART_SendChar(uint8 a_data)
{
	Status_t ReturnValue;
	if(Get_Bit(USART_Status_Register_B_UCSRB,Transmitter_Enable_TXEN))
	{
		USART_Data_Register=a_data;
		ReturnValue=OK;
	}
	else
		ReturnValue=NOT_OK;
	return ReturnValue;
}

Status_t UART_Receive(const uint8* a_data_ptr)
{
	Status_t ReturnValue;
	for(uint8 Count=0;a_data_ptr[Count-1]!='\n';Count++)
	{
		ReturnValue=UART_ReceiveChar(&(a_data_ptr[Count]));
		if(!(ReturnValue))
			return ReturnValue;
	}
	return ReturnValue;
}

Status_t UART_Send(uint8* a_data_ptr)
{
	Status_t ReturnValue;
	for(uint8 Count=0;a_data_ptr[Count]!='\n';Count++)
	{
		ReturnValue=UART_SendChar((a_data_ptr[Count]));
		if(!(ReturnValue))
			return ReturnValue;
	}
	return ReturnValue;
}

Status_t UART_StartComm(void)
{
	Status_t ReturnValue;
	Set_Bit(USART_Status_Register_B_UCSRB,Transmitter_Enable_TXEN);
	Set_Bit(USART_Status_Register_B_UCSRB,Receiver_Enable_RXEN);
	if((Get_Bit(USART_Status_Register_B_UCSRB,Transmitter_Enable_TXEN)))
	{
		if((Get_Bit(USART_Status_Register_B_UCSRB,Receiver_Enable_RXEN)))
			ReturnValue=OK;
		else
			ReturnValue=NOT_OK;
	}
	else
		ReturnValue=NOT_OK;
	return ReturnValue;

}

Status_t UART_StopComm(void)
{
	Status_t ReturnValue;
	while((Get_Bit(USART_Status_Register_A_UCSRA,USART_Data_Register_Empty_Flag_UDRE))==0);
	Clear_Bit(USART_Status_Register_B_UCSRB,Transmitter_Enable_TXEN);
	Clear_Bit(USART_Status_Register_B_UCSRB,Receiver_Enable_RXEN);
	if(!(Get_Bit(USART_Status_Register_B_UCSRB,Transmitter_Enable_TXEN)))
	{
		if(!(Get_Bit(USART_Status_Register_B_UCSRB,Receiver_Enable_RXEN)))
			ReturnValue=OK;
		else
			ReturnValue=NOT_OK;
	}
	else
		ReturnValue=NOT_OK;
	return ReturnValue;

}
