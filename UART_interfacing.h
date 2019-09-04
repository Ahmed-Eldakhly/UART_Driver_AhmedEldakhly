/*
 * UART_interfacing.h
 *
 *this file consist of enums,struct and function Prototypes for UART Driver
 *
 *  Created on: Sep 3, 2019
 *  Modified on: Sep 4, 2019
 *      Author: Ahmed Eldakhly
 */

#ifndef UART_INTERFACING_H_
#define UART_INTERFACING_H_

	/*this file contain typedefs of Standard Data Types*/
	#include"STDTYPES.h"


	/*status flag for any function to make sure this function is done*/
	typedef enum
	{
		NOT_OK,
		OK
	}Status_t;
	/*flag to determine baud rate speed mood*/
	enum DoubleSpeed
	{
		NormalSpeed,
		Dou_Speed
	};
	/*flag to enable or disable receive interrupt*/
	enum RXIntEN
	{
		EnableRX,
		DisableRX
	};
	/*flag to enable or disable transmit interrupt*/
	enum TXIntEN
	{
		EnableTX,
		DisableTX
	};
	/*flag to enable or disable Empty Data register interrupt*/
	enum EmptyIntEN
	{
		EnableEM,
		DisableEM
	};
	/*flag to determine Data Size (5,6,7,8 or 9 bits)*/
	enum DataSize
	{
		_5_bit,
		_6_bit,
		_7_bit,
		_8_bit,
		_9_bit
	};
	/*flag to determine Parity Mood (No parity - even parity - odd parity)*/
	enum Parity
	{
		NoParity,
		OddParity,
		EvenParity
	};
	/*flag to determine Number of stop bits (one bit - two bits)*/
	enum StopBit
	{
		OneStopBit,
		TwoStopBit
	};
	/*struct that let user set configuration of UART Peripheral */
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
	Status_t UART_Init(UART_conf_s const a_Init_Var_ptr);

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
	Status_t UART_ReceiveChar(uint8* a_data_ptr);

	/********************************************************************************************/
	/****************************************************************************
	* 1-func_Name: UART_SendChar.												*
	*                                                             			    *
	* 2-arguments:																*
	* 		Input:																*
	* 			Data type:uint8													*
	* 			this data that send from user by UART	Protocol				*
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
	Status_t UART_SendChar(uint8 a_data);

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
	Status_t UART_Receive(const uint8* a_data_ptr);

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
	Status_t UART_Send(uint8* a_data_ptr);

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
	Status_t UART_StartComm(void);

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
	Status_t UART_StopComm(void);


#endif /* UART_INTERFACING_H_ */
