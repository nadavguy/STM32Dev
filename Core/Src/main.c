/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "GUI_Paint.h"
#include "lvgl.h"
#include "ui.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t baroArrayCounter = 0;

uint8_t baroReadingArray[100] = {0};

uint32_t baroInitSampleTime = 0;

static uint8_t buf_1[40960];

float versionID = 1.000;
float buildID = 1.020;

tBARODATA ms5607Baro = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void my_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * color_p);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_DAC_Init();
  MX_USB_DEVICE_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

//  initLEDSequences();
//  led_init();
//  initMS56XXOutputStruct(&ms5607Baro);
//  MS56XXInit();
//  ms5607Baro.filteredData.air_pressure_out = ms5607Baro.rawData.air_pressure_out;

  memset(baroReadingArray, 120, sizeof(baroReadingArray));
  screenInit();
  screenClear();
  renderCompleteFrame = true;

  lv_init();

  lv_display_t * disp = lv_display_create(128, 160); /*Basic initialization with horizontal and vertical resolution in pixels*/
  lv_display_set_flush_cb(disp, my_flush_cb); /*Set a flush callback to draw to the display*/
  lv_display_set_buffers(disp, buf_1, NULL, sizeof(buf_1), LV_DISPLAY_RENDER_MODE_FULL); /*Set an initialized buffer*/
  ui_init();

//  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);
//  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
//
//  /*Create a spinner*/
//  lv_obj_t * spinner = lv_spinner_create(lv_screen_active());
//  lv_obj_set_size(spinner, 64, 64);
//  lv_obj_align(spinner, LV_ALIGN_CENTER, 0, 0);

  baroInitSampleTime = HAL_GetTick();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  checkButtonPress();
	  checkForButtonPattern();
//
//	  MS56XXCyclicRead();
//	  if ( (HAL_GetTick() - baroInitSampleTime <= 2000) && (ms5607Baro.isNewBaroDataAvailable) )
//	  {
//		  ms5607Baro.filteredData.air_pressure_out = (ms5607Baro.rawData.air_pressure_out + ms5607Baro.filteredData.air_pressure_out)/2;
//		  ms5607Baro.isNewBaroDataAvailable = false;
//		  altitudeFromMeasurements(&ms5607Baro);
//		  ms5607Baro.start_height = ms5607Baro.filteredData.altitude_out;
//	  }
//	  else if ( (HAL_GetTick() - baroInitSampleTime > 2000) && (ms5607Baro.isNewBaroDataAvailable) )
//	  {
//		  ms5607Baro.filteredData.air_pressure_out = ms5607Baro.rawData.air_pressure_out;
//		  altitudeFromMeasurements(&ms5607Baro);
//		  ms5607Baro.filteredData.altitude_out = ms5607Baro.filteredData.altitude_out - ms5607Baro.start_height;
//
//		  memcpy(&baroReadingArray[0], &baroReadingArray[1], sizeof(baroReadingArray) - 1);
//		  //		  float localAmpMeasuremnt = (3.3 * (ampReading ) / 4096.0) / 0.4;
//		  //
//		  //
//		  //		  milliAmpsForDisplay = (uint16_t)(localAmpMeasuremnt * 1000.0);
//		  baroReadingArray[99] = (uint8_t)(120 - 20 * (ms5607Baro.filteredData.altitude_out) / 5.0);
//
//		  ms5607Baro.isNewBaroDataAvailable = false;
//	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  ms5607ChipUnSelected();
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
	  HAL_Delay(1);
//	  screenUpdate(false);
//	  displayNextFrame();

	  /*Create a spinner*/
    lv_timer_handler();
    HAL_Delay(5);
    //	  HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void my_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * color_p)
{
  //Set the drawing region
//  set_draw_window(area->x1, area->y1, area->x2, area->y2);

  int height = area->y2 - area->y1 + 1;
  int width = area->x2 - area->x1 + 1;

  //We will do the SPI write manually here for speed
//  HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_SET);
  //CS low to begin data
//  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);

  //Write colour to each pixel
  for (int i = 0; i < width * height; i = i + 1)
  {
//    uint16_t color_full = (color_p->red << 11) | (color_p->green << 5) | (color_p->blue);
//    nextFrameToDraw[2*i] = (uint8_t)((color_full & 0xFF00) >> 8 );
//    nextFrameToDraw[2*i + 1] = (uint8_t)((color_full & 0x00FF));
	  nextFrameToDraw[2 * i] = *(color_p + 1);
	  nextFrameToDraw[2 * i + 1] = *(color_p);
//    parallel_write(color_full);

    color_p++;
    color_p++;
  }

  //Return CS to high
//  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);

  /* IMPORTANT!!!
  * Inform the graphics library that you are ready with the flushing*/
  displayNextFrame();
  lv_display_flush_ready(disp);

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
