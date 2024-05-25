/*
 * QCAgent.c
 *
 *  Created on: May 23, 2024
 *      Author: user
 */


#include <stdint.h>
#include "main.h"
#include "gpio.h"

void QCInit(void)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_Output_QC_DP_Signal2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_Output_QC_DP_Signal1_Pin, GPIO_PIN_SET);
	HAL_Delay(3000);
//	  digitalWrite(Dp_2k2, LOW);
//	  digitalWrite(Dp_10k, HIGH);
//
//	  delay(3000);
}

void setQCVoltage(uint8_t voltageToSet)
{
	switch (voltageToSet)
	{
		case 5:
		{

			break;
		}
		case 9:
		{

			break;
		}
		case 12:
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_Output_QC_DN_Signal2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, GPIO_Output_QC_DN_Signal1_Pin, GPIO_PIN_SET);

			HAL_GPIO_WritePin(GPIOD, GPIO_Output_QC_DP_Signal1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_Output_QC_DP_Signal2_Pin, GPIO_PIN_RESET);
//			digitalWrite(Dn_2k2, LOW);
//			digitalWrite(Dn_10k, HIGH);
//			digitalWrite(Dp_10k, HIGH);
//			digitalWrite(Dp_2k2, LOW);
			break;
		}
		default:
		{

			break;
		}
	}
}
