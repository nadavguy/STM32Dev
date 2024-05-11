/*
 * GeneralHelper.h
 *
 *  Created on: Apr 26, 2024
 *      Author: user
 */

#ifndef INC_GENERALHELPER_H_
#define INC_GENERALHELPER_H_


#include "stdbool.h"

extern double CurrentTime(void);
extern char *CT(void);
extern void UpdateDynamicArray(float new_val, float *pSrc, int Array_Length);
extern void ArrayAverage(float *ReturnedAverage, float *pSrc, int Array_Length);
extern float normalizeAngle(float angleToNormalize );
extern bool ASSERT(bool exp, const char *functionName, uint32_t line);
extern void limitArrayToTimeInterval(float *dataArray, float *timeArray, int *currentArrayIndex, int *slidingWindowDuration);
extern float floatArrayMinValue(float *pSrc, int Array_Length);
extern void MinAccelerationDurationForFreefall(float *pSrc, float *timeSrc, int Array_Length, float *Duration, float *MinAccelration, float freefallThreshold, uint32_t freefallDuration);
extern bool isFloatEquals(float a, float b,float epsilon);
extern void rotationOf2DVector(float xToRotate, float yToRotate, float rotationAngleInRadians, float *rotatedX, float *rotatedY);


#endif /* INC_GENERALHELPER_H_ */
