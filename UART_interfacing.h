/*
 * UART_interfacing.h
 *
 *  Created on: Sep 3, 2019
 *      Author: hp
 */

#ifndef UART_INTERFACING_H_
#define UART_INTERFACING_H_
#include"STDTYPES.h"

	typedef enum
	{
		NOT_OK,
		OK
	}Status_t;

	enum DoubleSpeed
	{
		NormalSpeed,
		Dou_Speed
	};

	enum RXIntEN
	{
		EnableRX,
		DisableRX
	};

	enum TXIntEN
	{
		EnableTX,
		DisableTX
	};

	enum EmptyIntEN
	{
		EnableEM,
		DisableEM
	};

	enum DataSize
	{
		_5_bit,
		_6_bit,
		_7_bit,
		_8_bit,
		_9_bit
	};

	enum Parity
	{
		NoParity,
		OddParity,
		EvenParity
	};

	enum StopBit
	{
		OneStopBit,
		TwoStopBit
	};

	typedef struct
	{
		uint16 BuadRate;
		enum Parity Init_Parity;
		enum StopBit Init_Stop;
		enum DataSize Init_DataSize;
		enum EmptyIntEN Init_Em;
		enum TXIntEN Init_TX;
		enum RXIntEN Init_RX;
		enum DoubleSpeed Init_DoubleSpeed;
	}UART_conf_s;

	Status_t UART_Init(UART_conf_s*);
	Status_t UART_ReceiveChar(uint8* a_data_ptr);
	Status_t UART_SendChar(uint8 a_data);
	Status_t UART_Receive(const uint8* a_data_ptr);
	Status_t UART_Send(uint8* a_data_ptr);
	Status_t UART_StartComm(void);
	Status_t UART_StopComm(void);


#endif /* UART_INTERFACING_H_ */
