/*
 * main.c
 *
 *  Created on: Sep 4, 2019
 *      Author: Ahmed Eldakhly
 *      App use two MC communicate with each other by UART to send number_
 *      by one of them and other one display this number on 7_segement.
 */
#include "STDTYPES.h"
#include "Macro.h"
#include "UART_interfacing.h"
#include "DIO_MemoryMaping.h"
#include "DIO_interface.h"
#include "avr/delay.h"
Status_t checkData=OK;
uint8 DataReceive,DataSend=0;
UART_conf_s Uart={51,NoParity,OneStopBit,_8_bit,DisableEM,DisableTX,DisableRX,NormalSpeed};

int main(void)
{
	sint8 s8Letter=-2;
	DIO_SetPinDirection(PIN20,Input);
	DIO_SetPinDirection(PIN8,Output);
	DIO_SetPinDirection(PIN9,Output);
	DIO_SetPinDirection(PIN10,Output);
	DIO_SetPinDirection(PIN11,Output);
	DIO_SetPinDirection(PIN28,Output);
	DIO_SetPinDirection(PIN27,Output);
	DIO_SetPinDirection(PIN26,Output);
	DIO_WritePin(PIN26,High);
	DIO_WritePin(PIN27,High);
	DIO_WritePin(PIN28,High);
	DIO_SetPinDirection(PIN24,Input);
	DIO_SetPinDirection(PIN25,Output);
	DIO_SetPinDirection(PIN20,Input);
	DIO_WritePin(PIN20,High);
	DIO_WritePin(PIN24,High);
	Status_t check=UART_Init(Uart);

	if(check==OK)
		check=UART_StartComm();
	if(check==OK)
	{

		while(1)
		{

			if(checkData==OK)
			{

				for(uint8 i=0;i<100;i++)
				{
					DIO_WritePin(PIN28,High);
					if(DIO_ReadPin(PIN20)==High)
					{
						while(DIO_ReadPin(PIN20)==High);
						if(s8Letter<9)
							s8Letter++;
						else
							s8Letter=0;
						i=0;
					}
					_delay_ms(2);
				}
				if(s8Letter>=0)
				{
					DataSend=s8Letter;
					s8Letter=0;
				}
			}
			UART_SendChar(DataSend);
			DataSend=0;
			checkData=UART_ReceiveChar(&DataReceive);
			if(checkData==OK)
				PORTB=(PORTB & 0xf0)|(DataReceive & 0x0f);
		}
	}
	return 0;
}

