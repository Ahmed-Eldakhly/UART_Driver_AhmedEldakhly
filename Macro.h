/*
 * Macro.h
 *
 *  Created on: Aug 17, 2019
 *      Author: hp
 */

#ifndef MACRO_H_
#define MACRO_H_

#define SetBit(Register,Bit) (Register|=(1<<Bit))
#define ClearBit(Register,Bit) (Register&=(~(1<<Bit)))
#define GetBit(Register,Bit) ((Register>>Bit)&1)
#define ToggleBit(Register,Bit) (Register^=(1<<Bit))

#endif /* MACRO_H_ */
