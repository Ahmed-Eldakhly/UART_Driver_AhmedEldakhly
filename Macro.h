/*
 * Macro.h
 *
 *  Created on: Aug 17, 2019
 *      Author: hp
 */

#ifndef MACRO_H_
#define MACRO_H_

#define Set_Bit(Register,Bit) (Register|=(1<<Bit))
#define Clear_Bit(Register,Bit) (Register&=(~(1<<Bit)))
#define Get_Bit(Register,Bit) ((Register>>Bit)&1)
#define Toggle_Bit(Register,Bit) (Register^=(1<<Bit))

#endif /* MACRO_H_ */
