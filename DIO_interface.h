/*
 * DIO_interface.h
 *
 *  Created on: Aug 17, 2019
 *      Author: hp
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
#include "DIO_MemoryMaping.h"
#include "STDTYPES.h"

void DIO_WritePin(uint8 PinNum,uint8 PinValue);
uint8 DIO_ReadPin(uint8 PinNum);
void DIO_SetPinDirection(uint8 PinNum,uint8 PinDirection);



#endif /* DIO_INTERFACE_H_ */

