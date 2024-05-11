/*
 * LEDAgent.h
 *
 *  Created on: Apr 4, 2022
 *      Author: gilad
 */

#ifndef INC_LEDAGENT_H_
#define INC_LEDAGENT_H_

typedef struct sLEDSEQUENCE
{
	uint8_t ID;
	uint8_t phase;
	uint32_t sequenceStart;
	uint8_t sequenceColors[16];
	uint16_t sequenceTimings[16];
	uint8_t sequenceLength;
	uint8_t sequenceRepeats;
	bool didSequenceEnd;
}tLEDSEQUENCE;

//extern tLEDSEQUENCE orientationErrorLEDSequence;
//extern tLEDSEQUENCE storageErrorLEDSequence;
//extern tLEDSEQUENCE idleAutoLEDSequence;
//extern tLEDSEQUENCE armedAutoLEDSequence;
//extern tLEDSEQUENCE triggeredLEDSequence;
//extern tLEDSEQUENCE eepromErrorLEDSequence;
extern tLEDSEQUENCE buttonPressedLEDSequence;
extern tLEDSEQUENCE hardfaultErrorLEDSequence;
//extern tLEDSEQUENCE autoPilotConnectionSequence;
//extern tLEDSEQUENCE noAutoPilotConnectionErrorLEDSequence;
//extern tLEDSEQUENCE generalErrorLEDSequence;
//extern tLEDSEQUENCE pyroErrorLEDSequence;
extern tLEDSEQUENCE dummyLEDSequence;
//extern tLEDSEQUENCE capacitorsErrorLEDSequence;
//extern tLEDSEQUENCE idleManualLEDSequence;
//extern tLEDSEQUENCE armedManualLEDSequence;
extern tLEDSEQUENCE sensorInitErrorLEDSequence;
extern tLEDSEQUENCE sensorRunErrorLEDSequence;
//extern tLEDSEQUENCE remoteControlErrorLEDSequence;
extern tLEDSEQUENCE powerOffSequence;

extern void led_init(void);
extern void initLEDSequences(void);
void led_to_buffer(uint8_t red, uint8_t green, uint8_t blue);
void setLEDSequence(tLEDSEQUENCE *sequenceToSet);
extern void updateLEDSequence(void);


#endif /* INC_LEDAGENT_H_ */
