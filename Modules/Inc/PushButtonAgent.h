/*
 * PushButtonAgent.h
 *
 *  Created on: Apr 26, 2024
 *      Author: user
 */

#ifndef INC_PUSHBUTTONAGENT_H_
#define INC_PUSHBUTTONAGENT_H_

extern bool isPushButtonPressed;

extern uint8_t pushButtonCycle;

extern uint16_t pushButtonPreviousValue;

extern uint32_t pushButtonPressStart;
extern uint32_t pushButtonPressCycleStart;
extern uint32_t pushButtonPressDurationmSec[5];

extern GPIO_PinState pushPinState;

extern void checkButtonPress(void);
extern bool checkForButtonPattern(void);


#endif /* INC_PUSHBUTTONAGENT_H_ */
