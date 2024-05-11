/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "MenuHelper.h"
#include "FrameHelper.h"
#include "ItemHelper.h"
#include "PopupHelper.h"
#include "fonts.h"
#include "ScreenAgent.h"

#include "LEDAgent.h"
#include "PushButtonAgent.h"
#include "ms5607Agent.h"
#include "GeneralHelper.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SYS_WKUP4_Tamper_Pin GPIO_PIN_13
#define SYS_WKUP4_Tamper_GPIO_Port GPIOC
#define ADC1_IN1_Battery_Pin GPIO_PIN_1
#define ADC1_IN1_Battery_GPIO_Port GPIOA
#define GPIO_Output_SPI1_CS_Pin GPIO_PIN_5
#define GPIO_Output_SPI1_CS_GPIO_Port GPIOC
#define GPIO_Output_ms5607_CS_Pin GPIO_PIN_0
#define GPIO_Output_ms5607_CS_GPIO_Port GPIOB
#define GPIO_Output1_Pin GPIO_PIN_1
#define GPIO_Output1_GPIO_Port GPIOB
#define GPIO_Output2_Pin GPIO_PIN_7
#define GPIO_Output2_GPIO_Port GPIOE
#define TIM1_CH1_LED_Blue_Pin GPIO_PIN_9
#define TIM1_CH1_LED_Blue_GPIO_Port GPIOE
#define TIM1_CH2_LED_GREEN_Pin GPIO_PIN_11
#define TIM1_CH2_LED_GREEN_GPIO_Port GPIOE
#define TIM1_CH3_LED_Red_Pin GPIO_PIN_13
#define TIM1_CH3_LED_Red_GPIO_Port GPIOE
#define TIM2_Ch2_Mosfet3_Pin GPIO_PIN_10
#define TIM2_Ch2_Mosfet3_GPIO_Port GPIOB
#define GPIO_Input__3_Pin GPIO_PIN_13
#define GPIO_Input__3_GPIO_Port GPIOD
#define GPIO_Inout__2_Pin GPIO_PIN_15
#define GPIO_Inout__2_GPIO_Port GPIOD
#define GPIO_Output__3_Pin GPIO_PIN_7
#define GPIO_Output__3_GPIO_Port GPIOC
#define TIM2_CH1_Mosfet1_Pin GPIO_PIN_15
#define TIM2_CH1_Mosfet1_GPIO_Port GPIOA
#define GPIO_Output_ChargeEN__Pin GPIO_PIN_0
#define GPIO_Output_ChargeEN__GPIO_Port GPIOD
#define GPIO_Input_ChargeDetect_Pin GPIO_PIN_2
#define GPIO_Input_ChargeDetect_GPIO_Port GPIOD
#define TIM2_CH2_Mosfet2_Pin GPIO_PIN_3
#define TIM2_CH2_Mosfet2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern tCURSOR_DATA currentCursorPosition;
extern tBARODATA ms5607Baro;

extern uint8_t baroReadingArray[100];

extern float versionID;
extern float buildID;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
