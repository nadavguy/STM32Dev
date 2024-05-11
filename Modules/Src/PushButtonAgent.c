/*
 * PushButtonAgent.c
 *
 *  Created on: Apr 26, 2024
 *      Author: user
 */

#include "main.h"

bool isPushButtonPressed = false;

uint8_t pushButtonCycle = 0;

uint16_t pushButtonPreviousValue = 0;

uint32_t pushButtonPressStart = 0;
uint32_t pushButtonPressCycleStart = 0;
uint32_t pushButtonPressDurationmSec[5] = {0};

GPIO_PinState pushPinState;

void checkButtonPress(void)
{
	pushPinState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

	if ( (pushPinState == GPIO_PIN_RESET) && (!isPushButtonPressed) )
	{
		//				setLEDSequence(&buttonPressedLEDSequence);
		isPushButtonPressed = true;
		pushButtonPressStart = HAL_GetTick();
		if (pushButtonCycle == 0)
		{
			pushButtonPressCycleStart = HAL_GetTick();
		}
	}
	else if ( (pushPinState == GPIO_PIN_RESET) && (isPushButtonPressed) )
	{

	}
	else if ( (pushPinState == GPIO_PIN_SET) && (isPushButtonPressed))
	{
		pushButtonPressDurationmSec[pushButtonCycle] = HAL_GetTick() - pushButtonPressStart;

		if (checkForButtonPattern())
		{
			//Do some shit
		}
		else
		{
			isPushButtonPressed = false;
		}
		pushButtonCycle++;
	}
	else if ((pushPinState == GPIO_PIN_SET) && (!isPushButtonPressed) )
	{
		//TODO: Consider how to handle pushBUttonCycle == 5
		if (HAL_GetTick() - pushButtonPressCycleStart > 5000)
		{
			pushButtonCycle = 0;
			pushButtonPressDurationmSec[0] = 0;
			pushButtonPressDurationmSec[1] = 0;
			pushButtonPressDurationmSec[2] = 0;
			pushButtonPressDurationmSec[3] = 0;
			pushButtonPressDurationmSec[4] = 0;
			pushButtonPressCycleStart = HAL_GetTick();
		}
	}
	else
	{

	}/*End Of Push Button Region */
}

bool checkForButtonPattern(void)
{
	if ( (pushButtonPressDurationmSec[0] >= 750) && (pushButtonPressDurationmSec[0] <= 1750) && (pushButtonPressDurationmSec[1] <= 10) )
	{
//	    isSetToPowerOff = true;
//	    setPowerOffCycleStart = HAL_GetTick();
		//Do this
		return (true);
	}
	else if ((pushButtonPressDurationmSec[0] >= 2000) && (pushButtonPressDurationmSec[0] <= 3750) && (pushButtonPressDurationmSec[1] <= 10))
	{
		//Do that

		return (true);
	}
	else if ( (pushButtonPressDurationmSec[0] >= 200) && (pushButtonPressDurationmSec[0] <= 400) &&
			(pushButtonPressDurationmSec[1] >= 200) && (pushButtonPressDurationmSec[1] <= 400))
	{
		//Do this or that
		return (true);
	}
	else if ((pushButtonPressDurationmSec[0] >= 500) && (pushButtonPressDurationmSec[0] <= 750) &&
			(pushButtonPressDurationmSec[1] >= 200) && (pushButtonPressDurationmSec[1] <= 400))
	{
		//Do that or this
		return (true);
	}
	else if ((pushButtonPressDurationmSec[0] >= 500) && (pushButtonPressDurationmSec[0] <= 750) &&
			(pushButtonPressDurationmSec[1] >= 500) && (pushButtonPressDurationmSec[1] <= 750))
	{
		//This is the good stuff
		return (true);
	}

	return (false);
}
