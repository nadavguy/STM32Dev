/*
 * LEDAgent.c
 *
 *  Created on: Apr 26, 2024
 *      Author: user
 */

#include "main.h"
#include "tim.h"

//tLEDSEQUENCE orientationErrorLEDSequence = {0};
//tLEDSEQUENCE storageErrorLEDSequence = {0};
//tLEDSEQUENCE idleAutoLEDSequence = {0};
//tLEDSEQUENCE armedAutoLEDSequence = {0};
//tLEDSEQUENCE triggeredLEDSequence = {0};
//tLEDSEQUENCE eepromErrorLEDSequence = {0};
tLEDSEQUENCE buttonPressedLEDSequence = {0};
tLEDSEQUENCE hardfaultErrorLEDSequence = {0};
//tLEDSEQUENCE autoPilotConnectionSequence = {0};
//tLEDSEQUENCE noAutoPilotConnectionErrorLEDSequence = {0};
//tLEDSEQUENCE generalErrorLEDSequence = {0};
//tLEDSEQUENCE pyroErrorLEDSequence = {0};
tLEDSEQUENCE dummyLEDSequence = {0};
//tLEDSEQUENCE capacitorsErrorLEDSequence = {0};
//tLEDSEQUENCE idleManualLEDSequence = {0};
//tLEDSEQUENCE armedManualLEDSequence = {0};
tLEDSEQUENCE sensorInitErrorLEDSequence = {0};
tLEDSEQUENCE sensorRunErrorLEDSequence = {0};
//tLEDSEQUENCE remoteControlErrorLEDSequence = {0};
tLEDSEQUENCE powerOffSequence = {0};

tLEDSEQUENCE *activeSequence;
tLEDSEQUENCE *previousSequence;

uint8_t activeSequenceCycles = 0;

float sinLED = 0;

void led_init(void)
{
  TIM1->CCR2 = 255;
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2); // GREEN
  TIM1->CCR1 = 255;
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1); // BLUE
  TIM1->CCR3 = 255;
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3); // RED
}

void initLEDSequences(void)
{
//	orientationErrorLEDSequence.ID = 1;
//	orientationErrorLEDSequence.phase = 0;
//	orientationErrorLEDSequence.sequenceRepeats = 0;
//	orientationErrorLEDSequence.sequenceStart = 0;
//	orientationErrorLEDSequence.sequenceTimings[0] = 200;
//	orientationErrorLEDSequence.sequenceTimings[1] = 200;
//	orientationErrorLEDSequence.sequenceTimings[2] = 200;
//	orientationErrorLEDSequence.sequenceTimings[3] = 200;
//	orientationErrorLEDSequence.sequenceTimings[4] = 1200;
//	orientationErrorLEDSequence.sequenceColors[0] = 0; //Black
//	orientationErrorLEDSequence.sequenceColors[1] = 3; //Yellow
//	orientationErrorLEDSequence.sequenceColors[2] = 0;
//	orientationErrorLEDSequence.sequenceColors[3] = 3;
//	orientationErrorLEDSequence.sequenceColors[4] = 0;
//	orientationErrorLEDSequence.sequenceLength = 5;

//	idleAutoLEDSequence.ID = 2;
//	idleAutoLEDSequence.phase = 0;
//	idleAutoLEDSequence.sequenceRepeats = 0;
//	idleAutoLEDSequence.sequenceStart = 0;
//	idleAutoLEDSequence.sequenceTimings[0] = 0;
//	idleAutoLEDSequence.sequenceTimings[1] = 1000;
//	idleAutoLEDSequence.sequenceColors[0] = 0; //Black
//	idleAutoLEDSequence.sequenceColors[1] = 4; //Blue
//	idleAutoLEDSequence.sequenceLength = 2;

//	storageErrorLEDSequence.ID = 3;
//	storageErrorLEDSequence.phase = 0;
//	storageErrorLEDSequence.sequenceRepeats = 0;
//	storageErrorLEDSequence.sequenceStart = 0;
//	storageErrorLEDSequence.sequenceTimings[0] = 200;
//	storageErrorLEDSequence.sequenceTimings[1] = 200;
//	storageErrorLEDSequence.sequenceTimings[2] = 200;
//	storageErrorLEDSequence.sequenceTimings[3] = 200;
//	storageErrorLEDSequence.sequenceTimings[4] = 200;
//	storageErrorLEDSequence.sequenceTimings[5] = 200;
//	storageErrorLEDSequence.sequenceTimings[6] = 800;
//	storageErrorLEDSequence.sequenceColors[0] = 0; //Black
//	storageErrorLEDSequence.sequenceColors[1] = 3; //Yellow
//	storageErrorLEDSequence.sequenceColors[2] = 0;
//	storageErrorLEDSequence.sequenceColors[3] = 3;
//	storageErrorLEDSequence.sequenceColors[4] = 0;
//	storageErrorLEDSequence.sequenceColors[5] = 3;
//	storageErrorLEDSequence.sequenceColors[6] = 0;
//	storageErrorLEDSequence.sequenceLength = 7;

//	armedAutoLEDSequence.ID = 4;
//	armedAutoLEDSequence.phase = 0;
//	armedAutoLEDSequence.sequenceRepeats = 0;
//	armedAutoLEDSequence.sequenceStart = 0;
//	armedAutoLEDSequence.sequenceTimings[0] = 200;
//	armedAutoLEDSequence.sequenceTimings[1] = 1000;
//	armedAutoLEDSequence.sequenceColors[0] = 0;
//	armedAutoLEDSequence.sequenceColors[1] = 8; //Green
//	armedAutoLEDSequence.sequenceLength = 2;

//	triggeredLEDSequence.ID = 5;
//	triggeredLEDSequence.phase = 0;
//	triggeredLEDSequence.sequenceRepeats = 0;
//	triggeredLEDSequence.sequenceStart = 0;
//	triggeredLEDSequence.sequenceTimings[0] = 200;
//	triggeredLEDSequence.sequenceTimings[1] = 1000;
//	triggeredLEDSequence.sequenceColors[0] = 0;
//	triggeredLEDSequence.sequenceColors[1] = 5; //Red
//	triggeredLEDSequence.sequenceLength = 2;

//	eepromErrorLEDSequence.ID = 6;
//	eepromErrorLEDSequence.phase = 0;
//	eepromErrorLEDSequence.sequenceRepeats = 0;
//	eepromErrorLEDSequence.sequenceStart = 0;
//	eepromErrorLEDSequence.sequenceTimings[0] = 200;
//	eepromErrorLEDSequence.sequenceTimings[1] = 1000;
//	eepromErrorLEDSequence.sequenceColors[0] = 0;
//	eepromErrorLEDSequence.sequenceColors[1] = 2; //Magenta
//	eepromErrorLEDSequence.sequenceLength = 2;

	buttonPressedLEDSequence.ID = 7;
	buttonPressedLEDSequence.phase = 0;
	buttonPressedLEDSequence.sequenceRepeats = 0;
	buttonPressedLEDSequence.sequenceStart = 0;
	buttonPressedLEDSequence.sequenceTimings[0] = 200;
	buttonPressedLEDSequence.sequenceTimings[1] = 1000;
	buttonPressedLEDSequence.sequenceColors[0] = 200;
	buttonPressedLEDSequence.sequenceColors[1] = 2; //Magenta
	buttonPressedLEDSequence.sequenceLength = 2;

	hardfaultErrorLEDSequence.ID = 8;
	hardfaultErrorLEDSequence.phase = 0;
	hardfaultErrorLEDSequence.sequenceRepeats = 0;
	hardfaultErrorLEDSequence.sequenceStart = 0;
	hardfaultErrorLEDSequence.sequenceTimings[0] = 200;
	hardfaultErrorLEDSequence.sequenceTimings[1] = 1000;
	hardfaultErrorLEDSequence.sequenceColors[0] = 0;
	hardfaultErrorLEDSequence.sequenceColors[1] = 1; //Orange
	hardfaultErrorLEDSequence.sequenceLength = 2;

//	autoPilotConnectionSequence.ID = 9;
//	autoPilotConnectionSequence.phase = 0;
//	autoPilotConnectionSequence.sequenceRepeats = 0;
//	autoPilotConnectionSequence.sequenceStart = 0;
//	autoPilotConnectionSequence.sequenceTimings[0] = 0;
//	autoPilotConnectionSequence.sequenceTimings[1] = 1000;
//	autoPilotConnectionSequence.sequenceTimings[2] = 1000;
//	autoPilotConnectionSequence.sequenceTimings[3] = 0;
//	autoPilotConnectionSequence.sequenceTimings[4] = 0;
//	autoPilotConnectionSequence.sequenceColors[0] = 13; //Black
//	autoPilotConnectionSequence.sequenceColors[1] = 13; //Magenta
//	autoPilotConnectionSequence.sequenceColors[2] = 0;
//	autoPilotConnectionSequence.sequenceColors[3] = 0;
//	autoPilotConnectionSequence.sequenceColors[4] = 0;
//	autoPilotConnectionSequence.sequenceLength = 2;

//	noAutoPilotConnectionErrorLEDSequence.ID = 10;
//	noAutoPilotConnectionErrorLEDSequence.phase = 0;
//	noAutoPilotConnectionErrorLEDSequence.sequenceRepeats = 0;
//	noAutoPilotConnectionErrorLEDSequence.sequenceStart = 0;
//	noAutoPilotConnectionErrorLEDSequence.sequenceTimings[0] = 200;
//	noAutoPilotConnectionErrorLEDSequence.sequenceTimings[1] = 200;
//	noAutoPilotConnectionErrorLEDSequence.sequenceTimings[2] = 200;
//	noAutoPilotConnectionErrorLEDSequence.sequenceTimings[3] = 200;
//	noAutoPilotConnectionErrorLEDSequence.sequenceTimings[4] = 1200;
//	noAutoPilotConnectionErrorLEDSequence.sequenceColors[0] = 0; //Black
//	noAutoPilotConnectionErrorLEDSequence.sequenceColors[1] = 11; //Teal
//	noAutoPilotConnectionErrorLEDSequence.sequenceColors[2] = 0;
//	noAutoPilotConnectionErrorLEDSequence.sequenceColors[3] = 2; //Magenta
//	noAutoPilotConnectionErrorLEDSequence.sequenceColors[4] = 0;
//	noAutoPilotConnectionErrorLEDSequence.sequenceLength = 5;

//	generalErrorLEDSequence.ID = 11;
//	generalErrorLEDSequence.phase = 0;
//	generalErrorLEDSequence.sequenceRepeats = 0;
//	generalErrorLEDSequence.sequenceStart = 0;
//	generalErrorLEDSequence.sequenceTimings[0] = 200;
//	generalErrorLEDSequence.sequenceTimings[1] = 200;
//	generalErrorLEDSequence.sequenceTimings[2] = 200;
//	generalErrorLEDSequence.sequenceTimings[3] = 200;
//	generalErrorLEDSequence.sequenceTimings[4] = 200;
//	generalErrorLEDSequence.sequenceTimings[5] = 200;
//	generalErrorLEDSequence.sequenceTimings[6] = 1200;
//	generalErrorLEDSequence.sequenceColors[0] = 0; //Black
//	generalErrorLEDSequence.sequenceColors[1] = 5; //Red
//	generalErrorLEDSequence.sequenceColors[2] = 0;
//	generalErrorLEDSequence.sequenceColors[3] = 3; //Yellow
//	generalErrorLEDSequence.sequenceColors[4] = 0;
//	generalErrorLEDSequence.sequenceColors[5] = 2; //Magenta
//	generalErrorLEDSequence.sequenceColors[6] = 0;
//	generalErrorLEDSequence.sequenceLength = 7;

//	pyroErrorLEDSequence.ID = 12;
//	pyroErrorLEDSequence.phase = 0;
//	pyroErrorLEDSequence.sequenceRepeats = 0;
//	pyroErrorLEDSequence.sequenceStart = 0;
//	pyroErrorLEDSequence.sequenceTimings[0] = 200;
//	pyroErrorLEDSequence.sequenceTimings[1] = 200;
//	pyroErrorLEDSequence.sequenceTimings[2] = 1600;
//	pyroErrorLEDSequence.sequenceColors[0] = 0; //Black
//	pyroErrorLEDSequence.sequenceColors[1] = 5; //Red
//	pyroErrorLEDSequence.sequenceColors[2] = 0;
//	pyroErrorLEDSequence.sequenceLength = 3;

	dummyLEDSequence.ID = 13;
	dummyLEDSequence.phase = 0;
	dummyLEDSequence.sequenceRepeats = 0;
	dummyLEDSequence.sequenceStart = 0;
	dummyLEDSequence.sequenceTimings[0] = 200;
	dummyLEDSequence.sequenceTimings[1] = 1800;
	dummyLEDSequence.sequenceColors[0] = 0; //Black
	dummyLEDSequence.sequenceColors[1] = 0;
	dummyLEDSequence.sequenceLength = 2;

//	capacitorsErrorLEDSequence.ID = 14;
//	capacitorsErrorLEDSequence.phase = 0;
//	capacitorsErrorLEDSequence.sequenceRepeats = 0;
//	capacitorsErrorLEDSequence.sequenceStart = 0;
//	capacitorsErrorLEDSequence.sequenceTimings[0] = 200;
//	capacitorsErrorLEDSequence.sequenceTimings[1] = 200;
//	capacitorsErrorLEDSequence.sequenceTimings[2] = 200;
//	capacitorsErrorLEDSequence.sequenceTimings[3] = 200;
//	capacitorsErrorLEDSequence.sequenceTimings[4] = 200;
//	capacitorsErrorLEDSequence.sequenceTimings[5] = 200;
//	capacitorsErrorLEDSequence.sequenceTimings[6] = 800;
//	capacitorsErrorLEDSequence.sequenceColors[0] = 0; //Black
//	capacitorsErrorLEDSequence.sequenceColors[1] = 5; //Red
//	capacitorsErrorLEDSequence.sequenceColors[2] = 0;
//	capacitorsErrorLEDSequence.sequenceColors[3] = 5;
//	capacitorsErrorLEDSequence.sequenceColors[4] = 0;
//	capacitorsErrorLEDSequence.sequenceColors[5] = 3; //Yellow
//	capacitorsErrorLEDSequence.sequenceColors[6] = 0;
//	capacitorsErrorLEDSequence.sequenceLength = 7;

//	idleManualLEDSequence.ID = 15;
//	idleManualLEDSequence.phase = 0;
//	idleManualLEDSequence.sequenceRepeats = 0;
//	idleManualLEDSequence.sequenceStart = 0;
//	idleManualLEDSequence.sequenceTimings[0] = 200;
//	idleManualLEDSequence.sequenceTimings[1] = 200;
//	idleManualLEDSequence.sequenceTimings[2] = 200;
//	idleManualLEDSequence.sequenceTimings[3] = 200;
//	idleManualLEDSequence.sequenceTimings[4] = 1200;
//	idleManualLEDSequence.sequenceColors[0] = 0; //Black
//	idleManualLEDSequence.sequenceColors[1] = 4; //Blue
//	idleManualLEDSequence.sequenceColors[2] = 0;
//	idleManualLEDSequence.sequenceColors[3] = 4;
//	idleManualLEDSequence.sequenceColors[4] = 0;
//	idleManualLEDSequence.sequenceLength = 5;

//	armedManualLEDSequence.ID = 16;
//	armedManualLEDSequence.phase = 0;
//	armedManualLEDSequence.sequenceRepeats = 0;
//	armedManualLEDSequence.sequenceStart = 0;
//	armedManualLEDSequence.sequenceTimings[0] = 200;
//	armedManualLEDSequence.sequenceTimings[1] = 200;
//	armedManualLEDSequence.sequenceTimings[2] = 200;
//	armedManualLEDSequence.sequenceTimings[3] = 200;
//	armedManualLEDSequence.sequenceTimings[4] = 1200;
//	armedManualLEDSequence.sequenceColors[0] = 0; //Black
//	armedManualLEDSequence.sequenceColors[1] = 8; //Green
//	armedManualLEDSequence.sequenceColors[2] = 0;
//	armedManualLEDSequence.sequenceColors[3] = 8;
//	armedManualLEDSequence.sequenceColors[4] = 0;
//	armedManualLEDSequence.sequenceLength = 5;

	sensorInitErrorLEDSequence.ID = 17;
	sensorInitErrorLEDSequence.phase = 0;
	sensorInitErrorLEDSequence.sequenceRepeats = 0;
	sensorInitErrorLEDSequence.sequenceStart = 0;
	sensorInitErrorLEDSequence.sequenceTimings[0] = 200;
	sensorInitErrorLEDSequence.sequenceTimings[1] = 200;
	sensorInitErrorLEDSequence.sequenceTimings[2] = 200;
	sensorInitErrorLEDSequence.sequenceTimings[3] = 200;
	sensorInitErrorLEDSequence.sequenceTimings[4] = 1200;
	sensorInitErrorLEDSequence.sequenceColors[0] = 0; //Black
	sensorInitErrorLEDSequence.sequenceColors[1] = 2; //Magenta
	sensorInitErrorLEDSequence.sequenceColors[2] = 0;
	sensorInitErrorLEDSequence.sequenceColors[3] = 3; //Yellow
	sensorInitErrorLEDSequence.sequenceColors[4] = 0;
	sensorInitErrorLEDSequence.sequenceLength = 5;

	sensorRunErrorLEDSequence.ID = 18;
	sensorRunErrorLEDSequence.phase = 0;
	sensorRunErrorLEDSequence.sequenceRepeats = 0;
	sensorRunErrorLEDSequence.sequenceStart = 0;
	sensorRunErrorLEDSequence.sequenceTimings[0] = 200;
	sensorRunErrorLEDSequence.sequenceTimings[1] = 200;
	sensorRunErrorLEDSequence.sequenceTimings[2] = 200;
	sensorRunErrorLEDSequence.sequenceTimings[3] = 200;
	sensorRunErrorLEDSequence.sequenceTimings[4] = 200;
	sensorRunErrorLEDSequence.sequenceTimings[5] = 200;
	sensorRunErrorLEDSequence.sequenceTimings[6] = 800;
	sensorRunErrorLEDSequence.sequenceColors[0] = 0; //Black
	sensorRunErrorLEDSequence.sequenceColors[1] = 2; //Magenta
	sensorRunErrorLEDSequence.sequenceColors[2] = 0;
	sensorRunErrorLEDSequence.sequenceColors[3] = 3; //Yellow
	sensorRunErrorLEDSequence.sequenceColors[4] = 0;
	sensorRunErrorLEDSequence.sequenceColors[5] = 3; //Yellow
	sensorRunErrorLEDSequence.sequenceColors[6] = 0;
	sensorRunErrorLEDSequence.sequenceLength = 7;

//	remoteControlErrorLEDSequence.ID = 19;
//	remoteControlErrorLEDSequence.phase = 0;
//	remoteControlErrorLEDSequence.sequenceRepeats = 0;
//	remoteControlErrorLEDSequence.sequenceStart = 0;
//	remoteControlErrorLEDSequence.sequenceTimings[0] = 200;
//	remoteControlErrorLEDSequence.sequenceTimings[1] = 200;
//	remoteControlErrorLEDSequence.sequenceTimings[2] = 1600;
//	remoteControlErrorLEDSequence.sequenceColors[0] = 0; //Black
//	remoteControlErrorLEDSequence.sequenceColors[1] = 3; //Yellow
//	remoteControlErrorLEDSequence.sequenceColors[2] = 0;
//	remoteControlErrorLEDSequence.sequenceLength = 3;

	powerOffSequence.ID = 20;
	powerOffSequence.phase = 0;
	powerOffSequence.sequenceRepeats = 0;
	powerOffSequence.sequenceStart = 0;
	powerOffSequence.sequenceTimings[0] = 0;
	powerOffSequence.sequenceTimings[1] = 1000;
	powerOffSequence.sequenceTimings[2] = 1000;
	powerOffSequence.sequenceTimings[3] = 0;
	powerOffSequence.sequenceTimings[4] = 0;
	powerOffSequence.sequenceColors[0] = 14; //Orange
	powerOffSequence.sequenceColors[1] = 14; //Orange
	powerOffSequence.sequenceColors[2] = 0;
	powerOffSequence.sequenceColors[3] = 0;
	powerOffSequence.sequenceColors[4] = 0;
	powerOffSequence.sequenceLength = 2;

}

void led_state(uint8_t _led_mode)
{
	switch (_led_mode)
	{
		case 0:
		{
			led_to_buffer(0, 0, 0); // clear
			break;
		}
		case 1:
		{
			led_to_buffer(255, 80, 0); // Orange
			break;
		}
		case 2:
		{
			led_to_buffer(255, 60, 255);  // Magenta
			break;
		}
		case 3:
		{
			led_to_buffer(255, 200, 0); // Yellow
			break;
		}
		case 4:
		{
			led_to_buffer(0, 0, 255);   // Blue
			break;
		}
		case 5:
			led_to_buffer(255, 0, 0);   // Red
			break;
		case 8:
		{
			led_to_buffer(0, 255, 0);   // Green
			break;
		}
		case 9:
		{
			led_to_buffer(24, 105, 100);   // turquoise
			break;
		}
		case 10:
		{
			led_to_buffer(0, 0, 0);   // black
			break;
		}
		case 11:
		{
			led_to_buffer(0, 255, 255);   // teal
			break;
		}
		case 12:
		{
			led_to_buffer(0, 128 + 127 * sin(2 * 3.1415 * sinLED), 128 + 127 * sin(2 * 3.1415 * sinLED));   // teal Blinking
			break;
		}
		case 13:
		{
			led_to_buffer(128 + 127 * sin(2 * 3.1415 * sinLED), 30 + 30 * sin(2 * 3.1415 * sinLED), 128 + 127 * sin(2 * 3.1415 * sinLED));   // Magenta Blinking
			break;
		}
		case 14:
		{
		    led_to_buffer(128 + 127 * sin(2 * 3.1415 * sinLED), 40 + 40 * sin(2 * 3.1415 * sinLED), 0);   // Magenta Blinking
		    break;
		}
		default : // white
		{
			led_to_buffer(255, 255, 255);
			break;
		}
	}
}

//-----------------------------------------------------------------------------

void led_to_buffer(uint8_t red, uint8_t green, uint8_t blue)
{
	TIM1->CCR2 = green * 31;
	TIM1->CCR3 = red * 31;
	TIM1->CCR1 = blue * 31;

}

void setLEDSequence(tLEDSEQUENCE *sequenceToSet)
{
	//TODO: Errors should also be decided here in addition to setting them manually
	// 		Other states are set manually and only over-rided by errors
	if (activeSequence->ID == sequenceToSet->ID)
	{
		return;
	}
	else
	{
	    if (pushPinState == GPIO_PIN_RESET)
	    {
	        activeSequence = &buttonPressedLEDSequence;
	    }
//	    else if (isSetToPowerOff)
//	    {
//	        activeSequence = &powerOffSequence;
//	    }
		else
		{
			activeSequence = sequenceToSet;
		}
		previousSequence = activeSequence;
		activeSequence->phase = 0;
		activeSequenceCycles = 0;
	}

}

void updateLEDSequence(void)
{
    if (activeSequence->phase >= activeSequence->sequenceLength)
    {
    	activeSequence->phase = 0;
    	activeSequence->didSequenceEnd = true;
    	activeSequenceCycles++;
    	if (activeSequenceCycles >= 200)
    	{
    		activeSequenceCycles = 0;
    	}
    	if ( (activeSequenceCycles >= activeSequence->sequenceRepeats)
    			&& (activeSequence->sequenceRepeats != 0) )
    	{
    		setLEDSequence(previousSequence);
    	}

    }
    if (activeSequence->phase == 0)
    {
        activeSequence->sequenceStart = HAL_GetTick();
        activeSequence->phase = activeSequence->phase + 1;
        activeSequence->didSequenceEnd = false;

    }
    else if (HAL_GetTick() - activeSequence->sequenceStart >= activeSequence->sequenceTimings[activeSequence->phase])
    {
    	activeSequence->sequenceStart = HAL_GetTick();
        activeSequence->phase = activeSequence->phase + 1;
    }
    else
    {
		sinLED += 1 / 100.0;
		if (sinLED >= 1)
		{
			sinLED = 0;
		}
    	led_state(activeSequence->sequenceColors[activeSequence->phase]);
    }
}

