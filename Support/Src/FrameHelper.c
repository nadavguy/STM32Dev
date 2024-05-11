/*
 * FrameHelper.c
 *
 *  Created on: May 5, 2021
 *      Author: gilad
 */

#include "main.h"
#include "DEV_Config.h"
#include "LCD_1in8.h"
#include "GUI_Paint.h"

uint8_t numberOfDisplayedSafeAirIcons = 0;

uint32_t LCDArraySize = 40960;

void createEmptyFrame(bool isMenuFrame)
{
	if (!isMenuFrame)
	{
		//Set Frame Black
		memset(nextFrameToDraw,0x00,LCDArraySize);

		//Set White part
		for (int i = 0 ; i < (LCDArraySize - SCREEN_WIDTH * STATUSBAR_HEIGHT * 2) /2 ; i++)
		{
			nextFrameToDraw[(i + SCREEN_WIDTH * STATUSBAR_HEIGHT) * 2] = BACKGROUND_HIGH_BYTE;
			nextFrameToDraw[(i + SCREEN_WIDTH * STATUSBAR_HEIGHT) * 2 + 1] = BACKGROUND_LOW_BYTE;
		}

		//Set screen lower part black
//		Paint_DrawRectangle(0, 80, 128, 160, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		addRectangleToFrame(0, 80, 128, 160, BLACK);

		//Set Ampere-meter grid
		for (int i = 100; i <= 160 ; i = i + 20)
		{
			Paint_DrawLine(20, i, 120, i, YELLOW, DOT_PIXEL_1X1, LINE_STYLE_DOTTED); // Horizontal line

		}
		for (int i = 20; i <= 120 ; i = i + 20)
		{
			Paint_DrawLine(i, 100, i, 160, YELLOW, DOT_PIXEL_1X1, LINE_STYLE_DOTTED); // Vertical line

		}


		Paint_DrawString_EN(5, 136, "-5", &Font8, BLACK, WHITE);
		Paint_DrawString_EN(5, 116, " 0", &Font8, BLACK, WHITE);
		Paint_DrawString_EN(5, 96, " 5", &Font8, BLACK, WHITE);
		Paint_DrawString_EN(5, 86, "[mbar]", &Font8, BLACK, WHITE);



	}
	else if (isMenuFrame)
	{
		memset(nextFrameToDraw,0xFF,LCDArraySize);
	}
}

void displayNextFrame(void)
{
//	LCD_1IN8_SetCursor(0, 0);
	if (HAL_GetTick() - lastFrameDisplayed > 30)
	{
		HAL_SPI_Transmit(&DEV_SPI, (uint8_t *)nextFrameToDraw, LCDArraySize, 1500);
//		createEmptyFrame(false);
		lastFrameDisplayed = HAL_GetTick();
	}
}

void addImageToNextFrame(const unsigned char *image, uint8_t Height, uint8_t Width, uint8_t Xstart, uint8_t Ystart)
{
	for (int i = 0 ; i < Height ; i++)
	{
		memcpy(&nextFrameToDraw[(Ystart + i) * SCREEN_WIDTH * 2 + Xstart * 2],&image[Width * 2 * i], Width * 2);
	}
}

void addRectangleToFrame(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd, uint16_t Color)
{
	for (int i = 0 ; i < (xEnd - xStart) * (yEnd - yStart) ; i++)
	{
		nextFrameToDraw[(i + SCREEN_WIDTH * yStart + xStart) * 2] = (uint8_t)((Color & 0xFF00) >> 8 );
		nextFrameToDraw[(i + SCREEN_WIDTH * yStart + xStart) * 2 + 1] = (uint8_t)((Color & 0x00FF));
	}
}

void prepareNextFrame(void)
{

}
