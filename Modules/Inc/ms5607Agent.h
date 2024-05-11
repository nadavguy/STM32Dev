/*
 * ms5607Agent.h
 *
 *  Created on: Apr 26, 2024
 *      Author: user
 */

#ifndef INC_MS5607AGENT_H_
#define INC_MS5607AGENT_H_

#define P_0 1013.25

typedef struct sBAROMEMSDATA
{
		float air_pressure_out;
		float temperature_out;
		float altitude_out;
		float verticalVelocity;
} tBAROMEMSDATA;

typedef struct sBARODATA
{
		//Log written time
		//    uint32_t LastBaroMeassurementSystick;
		//    uint32_t LastPressureMeassurementSystick;
		//    uint32_t LastTemperatureMeassurementSystick;

		//Update / Data received
		tBAROMEMSDATA rawData;
		tBAROMEMSDATA filteredData;

		float LastMeassuredBaro;
		float LastMeassuredPressure;
		float LastMeassuredTemperature;

		//    float Filtered_Velocity;
		float Delta_Height_Average;
		float Start_Height_Average;
		float start_height;

		bool isNewBaroDataAvailable;
		bool needToWriteLog;
		bool isFaultySensor;

} tBARODATA;

extern int32_t TEMP;
extern int32_t P;

extern void initMS56XXOutputStruct(tBARODATA *dataToFilter);
extern void MS56XXReset(void);
extern uint16_t MS56XXReadProm(uint8_t address);
extern void MS56XXInit(void);
extern void MS56XXSendCmd(uint8_t Cmd);
extern uint32_t MS56XXRead3Bytes(uint8_t address);
extern void MS56XXCyclicRead(void);
bool GetAltitudeAndTemp(void);
extern void altitudeFromMeasurements(tBARODATA *dataToUse);
extern void ms5607ChipUnSelected(void);


#endif /* INC_MS5607AGENT_H_ */
