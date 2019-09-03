/*
 * USART_MEMORY_MAPING.h
 *
 *  Created on: 21 Jul 2019
 *      Author: mohamed
 */

#ifndef USART_MEMORY_MAPING_H_
#define USART_MEMORY_MAPING_H_

#include"STDTYPES.h"

#define USART_Status_Register_A_UCSRA (*(volatile uint8*)0x2B)
#define MultiProcessors_Comm_Mode_Bit_MPCM 0
#define Double_Speed_Bit_U2X 1
#define Parity_Error_Flag_PE 2
#define Data_OverRun_Flag_DOR 3
#define Frame_Error_Flag_FE 4
#define USART_Data_Register_Empty_Flag_UDRE 5
#define USART_Transmit_Complete_Flag_TXC 6
#define USART_Receive_Complete_Flag_RXC 7


#define USART_Status_Register_B_UCSRB (*(volatile uint8*)0x2A)
#define Bit_8_in_Transmited_Data_TXB8 0
#define Bit_8_in_Received_Data_RXB8 1
#define Data_Size_Select_Bit2_UCSZ2 2
#define Transmitter_Enable_TXEN 3
#define Receiver_Enable_RXEN 4
#define USART_Data_Register_Empty_Interrupt_Enable_UDRIE 5
#define USART_Transmit_Complete_Interrupt_Enable_TXCIE 6
#define USART_Receive_Complete_Interrupt_Enable_RXCIE 7


#define USART_Status_Register_C_UCSRC (*(volatile uint8*)0x40)
#define USART_Clock_Polarity_Bit_UCPOL 0
#define Data_Size_Select_Bit0_UCSZ0 1
#define Data_Size_Select_Bit1_UCSZ1 2
#define Select_Number_of_Stop_Bits_USBS 3
#define Parity_Mode_Select_Bit0_UPM0 4
#define Parity_Mode_Select_Bit1_UPM1 5
#define USART_Mode_Select_Bit_UMSEL 6
#define Select_UCSRC_Register_URSEL 7



#define USART_Data_Register (*(volatile uint8*)0x2C)


#define USART_Baud_Rate_Select_Low_Register (*(volatile uint8*)0x29)
#define USART_Baud_Rate_Select_High_Register (*(volatile uint8*)0x40)
#define Select_UBRRH_Register_URSEL 7




#endif /* USART_MEMORY_MAPING_H_ */
