/*
 * ItemHelper.h
 *
 *  Created on: Apr 28, 2021
 *      Author: gilad
 */

#ifndef INC_ITEMHELPER_H_
#define INC_ITEMHELPER_H_

#include "main.h"
extern uint8_t multiplierIndex;

extern void updateUint8Item(MENUDRAWType howToDraw);
extern void updateUint16Item(MENUDRAWType howToDraw);
extern void updateUint32Item(MENUDRAWType howToDraw);
extern void updateStringItem(MENUDRAWType howToDraw);



#endif /* INC_ITEMHELPER_H_ */
