/*
 * GeneralHelper.c
 *
 *  Created on: Apr 26, 2024
 *      Author: user
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "stm32f7xx_hal.h"


char CTime[20] = {0};

double CurrentTime(void)
{
	return ((float)HAL_GetTick() / 1000.0);
}

char *CT(void)
{
	//sprintf(CTime, "%02d/%02d/%04d %02d:%02d:%02d.%03d,", L_day, L_month, L_year, L_hour, L_min, L_sec, L_ms);
	sprintf(CTime, "%7.3f,", (float)HAL_GetTick() / 1000.0);
	return (CTime);
}

void UpdateDynamicArray(float new_val, float *pSrc, int Array_Length)
{
	for (int i = 1; i < Array_Length; i++)
	{
		pSrc[i - 1] = pSrc[i];
	}
	pSrc[Array_Length - 1] = new_val;
}

void ArrayAverage(float *ReturnedAverage, float *pSrc, int Array_Length)
{
	float sum = 0;
	for (int i = 0; i < Array_Length; i++)
	{
		sum += pSrc[i];
	}
	*ReturnedAverage = sum / (float)Array_Length;
}

float normalizeAngle(float angleToNormalize )
{
	float localRet = 0;
	if (angleToNormalize < -180)
	{
		localRet = angleToNormalize + 360;
	}
	else if (angleToNormalize > 180)
	{
		localRet = 360 - angleToNormalize;
	}
	else
	{
		localRet = angleToNormalize;
	}
	return (localRet);

}

bool ASSERT(bool exp, const char *functionName, uint32_t line)
{
	bool localRet = false;
	if (exp)
	{
//		sprintf(resolvePointerToLogsBuffer(), "%s Test passed, %s\r\n", CT(), functionName);
//		logData(true, true, INTERNAL, BLUE, false);
		localRet = true;
	}
	else
	{
//		sprintf(resolvePointerToLogsBuffer(), "%s Test failed, %s at line %lu\r\n", CT(), functionName, line);
//		logData(true, true, INTERNAL, MAGENTA, false);
		localRet = false;
	}
	return (localRet);
}

void limitArrayToTimeInterval(float *dataArray, float *timeArray, int *currentArrayIndex, int *slidingWindowDuration)
{
	int Local_Delta_Time = (int)(timeArray[*currentArrayIndex - 1] - timeArray[0]);
	if (*currentArrayIndex > 1)
	{
		if (Local_Delta_Time > *slidingWindowDuration)
		{
			int LocalCounter = 1;
			while ((int)(timeArray[*currentArrayIndex - 1] - timeArray[0 + LocalCounter]) > *slidingWindowDuration)
			{
				LocalCounter++;
			}

			//      for (int i = 0; i < *currentArrayIndex; i++)
			//      {
			//        dataArray[i] = dataArray[i + LocalCounter];
			//        timeArray[i] = timeArray[i + LocalCounter];
			//      }
			memcpy(&dataArray[0], &dataArray[LocalCounter], (*currentArrayIndex - LocalCounter) * sizeof(int));
			memcpy(&timeArray[0], &timeArray[LocalCounter], (*currentArrayIndex - LocalCounter) * sizeof(int));

			*currentArrayIndex = *currentArrayIndex - LocalCounter;
		}
	}
}

float floatArrayMinValue(float *pSrc, int Array_Length)
{
	float LocalMinValue = pSrc[0];
	for (int i = 0; i < Array_Length; i++)
	{
		if (pSrc[i] < LocalMinValue)
		{
			LocalMinValue = pSrc[i];
		}
	}
	return (LocalMinValue);
}

void MinAccelerationDurationForFreefall(float *pSrc, float *timeSrc, int Array_Length, float *Duration, float *MinAccelration, float freefallThreshold, uint32_t freefallDuration)
{
	// float MaxDuration = 0;
	// float MinAccelerationInDuration = 10;
	float StartInterval = 0;
	float LocalIntervalDuration = 0;
	float BigestDurationInArraySoFar = 0;
	float MinAccelerationInCurrentInterval = 9.8065;
	float LocalMinValue = pSrc[0];
	bool LowAccelerationDetectedBefore = false;

	for (int i = 0; i < Array_Length; i++)
	{
		if (pSrc[i] < freefallThreshold)
		{
			if (!LowAccelerationDetectedBefore) //if start of interval save start time
			{
				StartInterval = timeSrc[i];
				LowAccelerationDetectedBefore = true;
			}
			else //save interval duration
			{
				LocalIntervalDuration = timeSrc[i] - StartInterval;
				if (pSrc[i] < LocalMinValue) // Save minimum value in interval
				{
					LocalMinValue = pSrc[i];
				}
			}

			if ((LocalIntervalDuration > (freefallDuration)) && (LocalIntervalDuration > BigestDurationInArraySoFar))
			{
				BigestDurationInArraySoFar = LocalIntervalDuration;
				MinAccelerationInCurrentInterval = LocalMinValue;
			}
		}
		else // Acceleration is not under threshold value, check if values need to be updated and clear variables for next test
		{
			LocalMinValue = 10;
			LocalIntervalDuration = 0;
			LowAccelerationDetectedBefore = false;
		}
	}
	*Duration = BigestDurationInArraySoFar;
	*MinAccelration = MinAccelerationInCurrentInterval;
}

bool isFloatEquals(float a, float b,float epsilon)
{
	bool localRet = false;

	if (fabs(a - b) <= epsilon)
	{
		// Numbers are considered equal within the given tolerance
		localRet = true;
	}
	else
	{
		// Numbers are not equal
		localRet = false;
	}
	return (localRet);
}

void rotationOf2DVector(float xToRotate, float yToRotate, float rotationAngleInRadians, float *rotatedX, float *rotatedY)
{
	*rotatedX = xToRotate * cos(rotationAngleInRadians) - yToRotate * sin(rotationAngleInRadians);
	*rotatedY = xToRotate * sin(rotationAngleInRadians) + yToRotate * cos(rotationAngleInRadians);
}
