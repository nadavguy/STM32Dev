/*
 * ms5607Agent.c
 *
 *  Created on: Apr 26, 2024
 *      Author: user
 */

#include "main.h"
#include "spi.h"

uint8_t SPITX[1] = {0};
uint8_t SPIRX2Byte[2] = {0};
uint8_t SPIRX3Byte[3] = {0};
uint16_t Coeff1 = 0;
uint16_t Coeff2 = 0;
uint16_t Coeff3 = 0;
uint16_t Coeff4 = 0;
uint16_t Coeff5 = 0;
uint16_t Coeff6 = 0;
uint16_t MSCRC = 0;
bool isCmdSet = false;
bool isPressureLastCmd = false;
uint32_t LastTempMeasurement = 0;
uint32_t LastPressureMeasurement = 0;
uint32_t LastCommandSent = 0;
uint32_t RawTemp = 0;
uint32_t RawPressure = 0;

int32_t dT = 0;
int32_t TEMP = 0;
int64_t OFF = 0;
int64_t SNES = 0;
int32_t P = 0;

tBARODATA *pointerToDataToFilter = {0};

void initMS56XXOutputStruct(tBARODATA *dataToFilter)
{
	pointerToDataToFilter = dataToFilter;
}

void ms5607ChipSelected(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
}

void ms5607ChipUnSelected(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
}

void MS56XXReset(void)
{
	ms5607ChipSelected();
	SPITX[0] = 0x1E;
	HAL_SPI_Transmit(&hspi1, &SPITX[0], 1, HAL_MAX_DELAY);
	while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY);
	ms5607ChipUnSelected();
}

uint16_t MS56XXReadProm(uint8_t address)
{
	SPITX[0] = address;
	ms5607ChipSelected();
	HAL_SPI_Transmit(&hspi1, &SPITX[0], 1, HAL_MAX_DELAY);
	while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY);
	HAL_SPI_Receive(&hspi1, &SPIRX2Byte[0], 1, HAL_MAX_DELAY);
	HAL_SPI_Receive(&hspi1, &SPIRX2Byte[1], 1, HAL_MAX_DELAY);
	ms5607ChipUnSelected();
	return ((SPIRX2Byte[0]<<8) + SPIRX2Byte[1]);
}

void MS56XXInit(void)
{
	MS56XXReset();
	HAL_Delay(50);
	MS56XXReadProm(0xA0);
	Coeff1 = MS56XXReadProm(0xA2);
	Coeff2 = MS56XXReadProm(0xA4);
	Coeff3 = MS56XXReadProm(0xA6);
	Coeff4 = MS56XXReadProm(0xA8);
	Coeff5 = MS56XXReadProm(0xAA);
	Coeff6 = MS56XXReadProm(0xAC);
	MSCRC = MS56XXReadProm(0xAE);

	MS56XXSendCmd(0x58);
	HAL_Delay(9);
	RawTemp = MS56XXRead3Bytes(0);

	MS56XXSendCmd(0x48);
	HAL_Delay(9);
	RawPressure = MS56XXRead3Bytes(0);
	GetAltitudeAndTemp();
}

void MS56XXSendCmd(uint8_t Cmd)
{
	ms5607ChipSelected();
	SPITX[0] = Cmd;
	HAL_SPI_Transmit(&hspi1, &SPITX[0], 1, HAL_MAX_DELAY);
	while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY);
	ms5607ChipUnSelected();
	isCmdSet = true;
}

uint32_t MS56XXRead3Bytes(uint8_t address)
{
	SPITX[0] = 0x00;
	ms5607ChipSelected();
	HAL_SPI_Transmit(&hspi1, &SPITX[0], 1, HAL_MAX_DELAY);
	while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY);
	HAL_SPI_Receive(&hspi1, &SPIRX3Byte[0], 1, HAL_MAX_DELAY);
	HAL_SPI_Receive(&hspi1, &SPIRX3Byte[1], 1, HAL_MAX_DELAY);
	HAL_SPI_Receive(&hspi1, &SPIRX3Byte[2], 1, HAL_MAX_DELAY);
	ms5607ChipUnSelected();
	isCmdSet = false;
	return ((SPIRX3Byte[0] << 16) + (SPIRX3Byte[1] << 8 ) + (SPIRX3Byte[0]));
}

bool GetAltitudeAndTemp(void)
{
	dT = (double)RawTemp - (double)Coeff5 * 256.0;
	TEMP = 2000.0 + dT * (double)Coeff6 / 8388608.0;
	OFF = (double)Coeff2 * 131072.0 + (double)Coeff4 * (double)dT / 64.0;
	SNES = (double)Coeff1 * 65536.0 + ((double)Coeff3 * (double)dT) / 128.0;
	P = (((double)RawPressure * (double)SNES) / 2097152.0 - (double)OFF) / 32768.0;

	if ( (!isFloatEquals(pointerToDataToFilter->rawData.temperature_out, TEMP, 0.01) )
			|| (!isFloatEquals(pointerToDataToFilter->rawData.air_pressure_out, P * 100 / 100.0, 0.01)) )
	{
		pointerToDataToFilter->rawData.temperature_out = TEMP;
		pointerToDataToFilter->rawData.air_pressure_out = P / 100.0;
		return (true);
	}
	return (false);
}

void MS56XXCyclicRead(void)
{
	if ( (HAL_GetTick() - LastTempMeasurement) > 1000 )
	{
		if (!isCmdSet)
		{
			MS56XXSendCmd(0x58);
			isCmdSet = true;
			pointerToDataToFilter->isNewBaroDataAvailable = false;
			isPressureLastCmd = false;
			LastCommandSent = HAL_GetTick();
		}
	}

	if ((HAL_GetTick() - LastPressureMeasurement) > 20)
	{
		if (!isCmdSet)
		{
			MS56XXSendCmd(0x48);
			isCmdSet = true;
			pointerToDataToFilter->isNewBaroDataAvailable = false;
			isPressureLastCmd = true;
			LastCommandSent = HAL_GetTick();
		}
	}

	if ( (HAL_GetTick() - LastCommandSent) > 9 )
	{
		if (isCmdSet)
		{
			if (!isPressureLastCmd)
			{
				RawTemp = MS56XXRead3Bytes(0);
				LastTempMeasurement = HAL_GetTick();
			}
			else
			{
				RawPressure = MS56XXRead3Bytes(0);
				LastPressureMeasurement = HAL_GetTick();
			}
			isCmdSet = false;
			pointerToDataToFilter->isNewBaroDataAvailable = GetAltitudeAndTemp();
		}
	}
}

void altitudeFromMeasurements(tBARODATA *dataToUse)
{

	dataToUse->filteredData.altitude_out = (((float)pow(((float)P_0 / (float)dataToUse->filteredData.air_pressure_out), (float)1.0f / 5.257f) - 1.0f) * ((float)(dataToUse->filteredData.temperature_out / 100.0f) + 273.15f)) / 0.0065f;

}
