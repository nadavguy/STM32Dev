/*
 * ItemHelper.c
 *
 *  Created on: Apr 28, 2021
 *      Author: gilad
 */
#include "main.h"
//#include "LCD_Test.h"
#include "GUI_Paint.h"
#include "LCD_1in8.h"
//#include "DEV_Config.h

uint8_t multiplierIndex = 1;

uint8_t uint8MultiplierArray[6] = {1, 2, 5, 10, 50, 100};
uint16_t uint16MultiplierArray[8] = {1, 2, 5, 10, 50, 100, 500, 1000};
uint32_t uint32MultiplierArray[8] = {1, 2, 5, 10, 50, 100, 500, 1000};

uint8_t stringMultiplierArray[1] = {1};

tCURSOR_DATA currentCursorPosition;

void updateUint8Item(MENUDRAWType howToDraw)
{
	uint8_t MenuRectangleStartX = 0;
	uint8_t MenuRectangleStartY = 0;
	uint8_t MenuRectangleHeight = 0;
	uint8_t MenuRectangleWidth = 0;
	uint8_t DisplayCenterWidth = 0;

	if (isPortrait)
	{
		MenuRectangleStartX = VerticalMenuRectangleStartX;
		MenuRectangleStartY = VerticalMenuRectangleStartY;
		MenuRectangleHeight = VerticalMenuRectangleHeight;
		MenuRectangleWidth = VerticalMenuRectangleWidth;
		DisplayCenterWidth = VerticalDisplayCenterWidth;
	}
	else
	{
//		MenuRectangleStartX = HorizontalMenuRectangleStartX;
//		MenuRectangleStartY = HorizontalMenuRectangleStartY;
//		MenuRectangleHeight = HorizontalMenuRectangleHeight;
//		MenuRectangleWidth = HorizontalMenuRectangleWidth;
//		DisplayCenterWidth = HorizontalDisplayCenterWidth;
	}

	for (int i = 0; i < uint8Item.numberOfItemsInPage ; i++)
	{
		if  ( (i < 2) && (howToDraw == FULL) )
		{
			Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
					MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
					uint8Item.itemsArray[i], BLACK, WHITE, 16, Font12);
		}
		if ( (i >= 2) && (i < uint8Item.numberOfItemsInPage - 2) )
		{
			if (howToDraw == FULL)
			{
				Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX + MenuRectangleWidth / 2, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
				Paint_DrawRectangle( MenuRectangleStartX + MenuRectangleWidth / 2, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			}

			if ( (i == 2) )
			{
				char localString[8] = "";
				sprintf(localString,"%03d",uint8Item.startValue);
				if (currentCursorPosition.cursorPosition == 0x02)
				{
					if ( (howToDraw == LEFT) || (howToDraw == FULL) )
					{
						Paint_DrawString_EN( MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint8Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_ClearWindows(MenuRectangleStartX + MenuRectangleWidth / 2 + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + MenuRectangleWidth / 2 + 1 + strlen(uint8Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						Paint_ClearWindows( MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint8Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN( MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint8Item.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == UP)
					{
						Paint_ClearWindows( MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint8Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN( MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint8Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}

				}
				else if (currentCursorPosition.cursorPosition == VALUE)
				{
					if (howToDraw == RIGHT)
					{
						Paint_ClearWindows( MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint8Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN( MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint8Item.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						if (uint8Item.deltaMultiplier < uint8Item.startValue)
						{
							uint8Item.startValue = fmax(uint8Item.startValue - uint8Item.deltaMultiplier, uint8Item.minValue * 1.0);
						}
						else
						{
							uint8Item.startValue = uint8Item.minValue;
						}
						sprintf(localString,"%03d",uint8Item.startValue);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == UP)
					{
						uint8Item.startValue = fmin(uint8Item.startValue + uint8Item.deltaMultiplier, uint8Item.maxValue * 1.0);
						sprintf(localString,"%03d",uint8Item.startValue);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
				}
				else
				{
					Paint_ClearWindows( MenuRectangleStartX + 1,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							MenuRectangleStartX + 1 + strlen(uint8Item.itemsArray[i]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					Paint_DrawString_EN( MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint8Item.itemsArray[i], &Font12, WHITE,  BLACK);
					Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							localString, &Font12, WHITE,  BLACK);
				}
			}
			// Render value text of "Multiplier" with Grey or White background
			if ( (i == 3) )
			{
				char localString[8] = "";
				sprintf(localString,"%03d",uint8Item.deltaMultiplier);
				if (currentCursorPosition.cursorPosition == 0x03)
				{
					if ( (howToDraw == LEFT) || (howToDraw == FULL) )
					{
						Paint_DrawString_EN( MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint8Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_ClearWindows( MenuRectangleStartX + MenuRectangleWidth / 2 + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + MenuRectangleWidth / 2 + 1 + strlen(uint8Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						Paint_ClearWindows( MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint8Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN( MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint8Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == UP)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint8Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN( MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint8Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
				}
				else if (currentCursorPosition.cursorPosition == MULTIPLIER)
				{
					if (howToDraw == RIGHT)
					{
						Paint_ClearWindows( MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint8Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN( MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint8Item.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						if (multiplierIndex >= 1)
						{
							multiplierIndex = fmax(multiplierIndex - 1, 0);
						}
						else
						{
							multiplierIndex = 0;
						}
						uint8Item.deltaMultiplier = uint8MultiplierArray[multiplierIndex];
						sprintf(localString,"%03d",uint8Item.deltaMultiplier);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == UP)
					{
						multiplierIndex = fmin(multiplierIndex + 1, 7);
						uint8Item.deltaMultiplier = uint8MultiplierArray[multiplierIndex];
						sprintf(localString,"%03d",uint8Item.deltaMultiplier);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
				}
				else
				{
					Paint_ClearWindows( MenuRectangleStartX + 1,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							MenuRectangleStartX + 1 + strlen(uint8Item.itemsArray[i]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					Paint_DrawString_EN( MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint8Item.itemsArray[i], &Font12, WHITE,  BLACK);
					Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							localString, &Font12, WHITE,  BLACK);
				}
			}
		}
		if ( (i >= uint8Item.numberOfItemsInPage - 2) && (i < uint8Item.numberOfItemsInPage) )
		{
			if (howToDraw == FULL)
			{
				Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
				if (currentCursorPosition.cursorPosition == i)
				{
					centeredString( DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint8Item.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
				else
				{
					centeredString( DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint8Item.itemsArray[i], BLACK, WHITE, 16, Font12);
				}
			}
			else if (howToDraw == DOWN)
			{
				if ( (currentCursorPosition.cursorPosition == 4) && (i == 4) )
				{
					centeredString( DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint8Item.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
				else if ( (currentCursorPosition.cursorPosition == 5) && (i == 5) )
				{
					Paint_ClearWindows( DisplayCenterWidth,
							MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							DisplayCenterWidth + strlen(uint8Item.itemsArray[i - 1]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1 + Font12.Height, WHITE);
					centeredString( DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							uint8Item.itemsArray[(i - 1)], BLACK, WHITE, 16, Font12);
					centeredString( DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint8Item.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
			}
			else if (howToDraw == UP)
			{
				if ( (currentCursorPosition.cursorPosition == 3) && (i == 4) )
				{
					Paint_ClearWindows(DisplayCenterWidth - strlen(uint8Item.itemsArray[i]) * Font12.Width / 2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							DisplayCenterWidth + strlen(uint8Item.itemsArray[i]) * Font12.Width /2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint8Item.itemsArray[(i)], BLACK, WHITE, 16, Font12);
					//						centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * i + 1,
					//								uint16Item.itemsArray[i], BLACK, LGRAY, 16);
				}
				else if ( (currentCursorPosition.cursorPosition == 4) && (i == 5) )
				{
					Paint_ClearWindows( DisplayCenterWidth - strlen(uint8Item.itemsArray[i]) * Font12.Width / 2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							DisplayCenterWidth + strlen(uint8Item.itemsArray[i]) * Font12.Width /2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					centeredString( DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint8Item.itemsArray[(i)], BLACK, WHITE, 16, Font12);
					centeredString( DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							uint8Item.itemsArray[i - 1], BLACK, LGRAY, 16, Font12);
				}
			}
		}
	}
}

void updateUint16Item(MENUDRAWType howToDraw)
{

	uint8_t MenuRectangleStartX = 0;
	uint8_t MenuRectangleStartY = 0;
	uint8_t MenuRectangleHeight = 0;
	uint8_t MenuRectangleWidth = 0;
	uint8_t DisplayCenterWidth = 0;

	if (isPortrait)
	{
		MenuRectangleStartX = VerticalMenuRectangleStartX;
		MenuRectangleStartY = VerticalMenuRectangleStartY;
		MenuRectangleHeight = VerticalMenuRectangleHeight;
		MenuRectangleWidth = VerticalMenuRectangleWidth;
		DisplayCenterWidth = VerticalDisplayCenterWidth;
	}
	else
	{
//		MenuRectangleStartX = HorizontalMenuRectangleStartX;
//		MenuRectangleStartY = HorizontalMenuRectangleStartY;
//		MenuRectangleHeight = HorizontalMenuRectangleHeight;
//		MenuRectangleWidth = HorizontalMenuRectangleWidth;
//		DisplayCenterWidth = HorizontalDisplayCenterWidth;
	}

	for (int i = 0; i < uint16Item.numberOfItemsInPage ; i++)
	{
		if  ( (i < 2) && (howToDraw == FULL) )
		{
			Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
					MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
					uint16Item.itemsArray[i], BLACK, WHITE, 16, Font12);
		}
		if ( (i >= 2) && (i < uint16Item.numberOfItemsInPage - 2) )
		{
			if (howToDraw == FULL)
			{
				Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX + MenuRectangleWidth / 2, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
				Paint_DrawRectangle( MenuRectangleStartX + MenuRectangleWidth / 2, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			}

			if ( (i == 2) )
			{
				char localString[8] = "";
				sprintf(localString,"%04d",uint16Item.startValue);
				if (currentCursorPosition.cursorPosition == 0x02)
				{
					if ( (howToDraw == LEFT) || (howToDraw == FULL) )
					{
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint16Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_ClearWindows(MenuRectangleStartX + MenuRectangleWidth / 2 + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + MenuRectangleWidth / 2 + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint16Item.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == UP)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint16Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}

				}
				else if (currentCursorPosition.cursorPosition == VALUE)
				{
					if (howToDraw == RIGHT)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint16Item.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						if (uint16Item.deltaMultiplier < uint16Item.startValue)
						{
							uint16Item.startValue = fmax(uint16Item.startValue - uint16Item.deltaMultiplier, uint16Item.minValue * 1.0);
						}
						else
						{
							uint16Item.startValue = uint16Item.minValue;
						}

						sprintf(localString,"%04d",uint16Item.startValue);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == UP)
					{
						uint16Item.startValue = fmin(uint16Item.startValue + uint16Item.deltaMultiplier, uint16Item.maxValue * 1.0);
						sprintf(localString,"%04d",uint16Item.startValue);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
				}
				else
				{
					Paint_ClearWindows(MenuRectangleStartX + 1,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							MenuRectangleStartX + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint16Item.itemsArray[i], &Font12, WHITE,  BLACK);
					Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							localString, &Font12, WHITE,  BLACK);
				}
			}
			// Render value text of "Multiplier" with Grey or White background
			if ( (i == 3) )
			{
				char localString[8] = "";
				sprintf(localString,"%04d",uint16Item.deltaMultiplier);
				if (currentCursorPosition.cursorPosition == 0x03)
				{
					if ( (howToDraw == LEFT) || (howToDraw == FULL) )
					{
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint16Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_ClearWindows(MenuRectangleStartX + MenuRectangleWidth / 2 + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + MenuRectangleWidth / 2 + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint16Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == UP)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint16Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
				}
				else if (currentCursorPosition.cursorPosition == MULTIPLIER)
				{
					if (howToDraw == RIGHT)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint16Item.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						if (multiplierIndex >= 1)
						{
							multiplierIndex = fmax(multiplierIndex - 1, 0);
						}
						else
						{
							multiplierIndex = 0;
						}
						uint16Item.deltaMultiplier = uint16MultiplierArray[multiplierIndex];
						sprintf(localString,"%04d",uint16Item.deltaMultiplier);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == UP)
					{
						multiplierIndex = fmin(multiplierIndex + 1, 7);
						uint16Item.deltaMultiplier = uint16MultiplierArray[multiplierIndex];
						sprintf(localString,"%04d",uint16Item.deltaMultiplier);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					//						if (howToDraw == RIGHT)
					//						{
					//							Paint_ClearWindows(HorizontalMenuRectangleStartX + 1,
					//									HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * (i) + 1,
					//									HorizontalMenuRectangleStartX + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
					//									HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					//							Paint_DrawString_EN(HorizontalMenuRectangleStartX + 1, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * (i) + 1,
					//									uint16Item.itemsArray[i], &Font12, WHITE,  BLACK);
					//							Paint_DrawString_EN(HorizontalMenuRectangleStartX  + HorizontalMenuRectangleWidth / 2 + 1, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * (i) + 1,
					//									localString, &Font12, LGRAY,  BLACK);
					//						}
					//						else
					//						{
					//							Paint_DrawString_EN(HorizontalMenuRectangleStartX + 1, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * (i) + 1,
					//									uint16Item.itemsArray[i], &Font12, LGRAY,  BLACK);
					//							Paint_ClearWindows(HorizontalMenuRectangleStartX + HorizontalMenuRectangleWidth / 2 + 1,
					//									HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * (i) + 1,
					//									HorizontalMenuRectangleStartX + HorizontalMenuRectangleWidth / 2 + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
					//									HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					//							Paint_DrawString_EN(HorizontalMenuRectangleStartX  + HorizontalMenuRectangleWidth / 2 + 1, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * (i) + 1,
					//									localString, &Font12, WHITE,  BLACK);
					//						}
				}
				else
				{
					Paint_ClearWindows(MenuRectangleStartX + 1,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							MenuRectangleStartX + 1 + strlen(uint16Item.itemsArray[i]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint16Item.itemsArray[i], &Font12, WHITE,  BLACK);
					Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							localString, &Font12, WHITE,  BLACK);
				}
			}
		}
		//			Paint_DrawRectangle( HorizontalMenuRectangleStartX + HorizontalMenuRectangleWidth / 2, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * (i + 1),
		//					HorizontalMenuRectangleStartX + HorizontalMenuRectangleWidth, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * (i + 2),
		//					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
		if ( (i >= uint16Item.numberOfItemsInPage - 2) && (i < uint16Item.numberOfItemsInPage) )
		{
			if (howToDraw == FULL)
			{
				Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
				if (currentCursorPosition.cursorPosition == i)
				{
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint16Item.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
				else
				{
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint16Item.itemsArray[i], BLACK, WHITE, 16, Font12);
				}
			}
			else if (howToDraw == DOWN)
			{
				if ( (currentCursorPosition.cursorPosition == 4) && (i == 4) )
				{
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint16Item.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
				else if ( (currentCursorPosition.cursorPosition == 5) && (i == 5) )
				{
					Paint_ClearWindows(DisplayCenterWidth,
							MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							DisplayCenterWidth + strlen(uint16Item.itemsArray[i - 1]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1 + Font12.Height, WHITE);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							uint16Item.itemsArray[(i - 1)], BLACK, WHITE, 16, Font12);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint16Item.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
			}
			else if (howToDraw == UP)
			{
				if ( (currentCursorPosition.cursorPosition == 3) && (i == 4) )
				{
					Paint_ClearWindows(DisplayCenterWidth - strlen(uint16Item.itemsArray[i]) * Font12.Width / 2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							DisplayCenterWidth + strlen(uint16Item.itemsArray[i]) * Font12.Width /2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint16Item.itemsArray[(i)], BLACK, WHITE, 16, Font12);
					//						centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * i + 1,
					//								uint16Item.itemsArray[i], BLACK, LGRAY, 16);
				}
				else if ( (currentCursorPosition.cursorPosition == 4) && (i == 5) )
				{
					Paint_ClearWindows(DisplayCenterWidth - strlen(uint16Item.itemsArray[i]) * Font12.Width / 2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							DisplayCenterWidth + strlen(uint16Item.itemsArray[i]) * Font12.Width /2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint16Item.itemsArray[(i)], BLACK, WHITE, 16, Font12);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							uint16Item.itemsArray[i - 1], BLACK, LGRAY, 16, Font12);
				}
			}
		}
	}
}

void updateUint32Item(MENUDRAWType howToDraw)
{
	uint8_t MenuRectangleStartX = 0;
	uint8_t MenuRectangleStartY = 0;
	uint8_t MenuRectangleHeight = 0;
	uint8_t MenuRectangleWidth = 0;
	uint8_t DisplayCenterWidth = 0;

	if (isPortrait)
	{
		MenuRectangleStartX = VerticalMenuRectangleStartX;
		MenuRectangleStartY = VerticalMenuRectangleStartY;
		MenuRectangleHeight = VerticalMenuRectangleHeight;
		MenuRectangleWidth = VerticalMenuRectangleWidth;
		DisplayCenterWidth = VerticalDisplayCenterWidth;
	}
	else
	{
//		MenuRectangleStartX = HorizontalMenuRectangleStartX;
//		MenuRectangleStartY = HorizontalMenuRectangleStartY;
//		MenuRectangleHeight = HorizontalMenuRectangleHeight;
//		MenuRectangleWidth = HorizontalMenuRectangleWidth;
//		DisplayCenterWidth = HorizontalDisplayCenterWidth;
	}

	for (int i = 0; i < uint32Item.numberOfItemsInPage ; i++)
	{
		if  ( (i < 2) && (howToDraw == FULL) )
		{
			Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
					MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			centeredString( DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
					uint32Item.itemsArray[i], BLACK, WHITE, 16, Font12);
		}
		if ( (i >= 2) && (i < uint32Item.numberOfItemsInPage - 2) )
		{
			if (howToDraw == FULL)
			{
				Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX + MenuRectangleWidth / 2, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
				Paint_DrawRectangle( MenuRectangleStartX + MenuRectangleWidth / 2, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			}

			if ( (i == 2) )
			{
				char localString[8] = "";
				sprintf(localString,"%05ld",uint32Item.startValue);
				if (currentCursorPosition.cursorPosition == 0x02)
				{
					if ( (howToDraw == LEFT) || (howToDraw == FULL) )
					{
						Paint_DrawString_EN( MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint32Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_ClearWindows( MenuRectangleStartX + MenuRectangleWidth / 2 + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + MenuRectangleWidth / 2 + 1 + strlen(uint32Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN( MenuRectangleStartX + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint32Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint32Item.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == UP)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint32Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint32Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}

				}
				else if (currentCursorPosition.cursorPosition == VALUE)
				{
					if (howToDraw == RIGHT)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint32Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint32Item.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						if (uint32Item.deltaMultiplier < uint32Item.startValue)
						{
							uint32Item.startValue = fmax(uint32Item.startValue - uint32Item.deltaMultiplier, uint32Item.minValue * 1.0);
						}
						else
						{
							uint32Item.startValue = uint32Item.minValue;
						}

						sprintf(localString,"%05ld",uint32Item.startValue);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == UP)
					{
						uint32Item.startValue = fmin(uint32Item.startValue + uint32Item.deltaMultiplier, uint32Item.maxValue * 1.0);
						sprintf(localString,"%05ld",uint32Item.startValue);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
				}
				else
				{
					Paint_ClearWindows(MenuRectangleStartX + 1,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							MenuRectangleStartX + 1 + strlen(uint32Item.itemsArray[i]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint32Item.itemsArray[i], &Font12, WHITE,  BLACK);
					Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							localString, &Font12, WHITE,  BLACK);
				}
			}
			// Render value text of "Multiplier" with Grey or White background
			if ( (i == 3) )
			{
				char localString[8] = "";
				sprintf(localString,"%04ld",uint32Item.deltaMultiplier);
				if (currentCursorPosition.cursorPosition == 0x03)
				{
					if ( (howToDraw == LEFT) || (howToDraw == FULL) )
					{
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint32Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_ClearWindows(MenuRectangleStartX + MenuRectangleWidth / 2 + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + MenuRectangleWidth / 2 + 1 + strlen(uint32Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint32Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint32Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == UP)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint32Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint32Item.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
				}
				else if (currentCursorPosition.cursorPosition == MULTIPLIER)
				{
					if (howToDraw == RIGHT)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(uint32Item.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								uint32Item.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == DOWN)
					{

						if (multiplierIndex >= 1)
						{
							multiplierIndex = fmax(multiplierIndex - 1, 0);
						}
						else
						{
							multiplierIndex = 0;
						}
						uint32Item.deltaMultiplier = uint32MultiplierArray[multiplierIndex];
						sprintf(localString,"%04ld",uint32Item.deltaMultiplier);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == UP)
					{
						multiplierIndex = fmin(multiplierIndex + 1, 7);
						uint32Item.deltaMultiplier = uint32MultiplierArray[multiplierIndex];
						sprintf(localString,"%04ld",uint32Item.deltaMultiplier);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
				}
				else
				{
					Paint_ClearWindows(MenuRectangleStartX + 1,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							MenuRectangleStartX + 1 + strlen(uint32Item.itemsArray[i]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint32Item.itemsArray[i], &Font12, WHITE,  BLACK);
					Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							localString, &Font12, WHITE,  BLACK);
				}
			}
		}
		if ( (i >= uint32Item.numberOfItemsInPage - 2) && (i < uint32Item.numberOfItemsInPage) )
		{
			if (howToDraw == FULL)
			{
				Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX+MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
				if (currentCursorPosition.cursorPosition == i)
				{
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint32Item.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
				else
				{
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint32Item.itemsArray[i], BLACK, WHITE, 16, Font12);
				}
			}
			else if (howToDraw == DOWN)
			{
				if ( (currentCursorPosition.cursorPosition == 4) && (i == 4) )
				{
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint32Item.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
				else if ( (currentCursorPosition.cursorPosition == 5) && (i == 5) )
				{
					Paint_ClearWindows(DisplayCenterWidth,
							MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							DisplayCenterWidth + strlen(uint32Item.itemsArray[i - 1]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1 + Font12.Height, WHITE);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							uint32Item.itemsArray[(i - 1)], BLACK, WHITE, 16, Font12);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							uint32Item.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
			}
			else if (howToDraw == UP)
			{
				if ( (currentCursorPosition.cursorPosition == 3) && (i == 4) )
				{
					Paint_ClearWindows(DisplayCenterWidth - strlen(uint32Item.itemsArray[i]) * Font12.Width / 2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							DisplayCenterWidth + strlen(uint32Item.itemsArray[i]) * Font12.Width /2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint32Item.itemsArray[(i)], BLACK, WHITE, 16, Font12);
					//						centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * i + 1,
					//								uint16Item.itemsArray[i], BLACK, LGRAY, 16);
				}
				else if ( (currentCursorPosition.cursorPosition == 4) && (i == 5) )
				{
					Paint_ClearWindows(DisplayCenterWidth - strlen(uint32Item.itemsArray[i]) * Font12.Width / 2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							DisplayCenterWidth + strlen(uint32Item.itemsArray[i]) * Font12.Width /2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							uint32Item.itemsArray[(i)], BLACK, WHITE, 16, Font12);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							uint32Item.itemsArray[i - 1], BLACK, LGRAY, 16, Font12);
				}
			}
		}
	}
}

void updateStringItem(MENUDRAWType howToDraw)
{
	uint8_t MenuRectangleStartX = 0;
	uint8_t MenuRectangleStartY = 0;
	uint8_t MenuRectangleHeight = 0;
	uint8_t MenuRectangleWidth = 0;
	uint8_t DisplayCenterWidth = 0;

	if (isPortrait)
	{
		MenuRectangleStartX = VerticalMenuRectangleStartX;
		MenuRectangleStartY = VerticalMenuRectangleStartY;
		MenuRectangleHeight = VerticalMenuRectangleHeight;
		MenuRectangleWidth = VerticalMenuRectangleWidth;
		DisplayCenterWidth = VerticalDisplayCenterWidth;
	}
	else
	{
//		MenuRectangleStartX = HorizontalMenuRectangleStartX;
//		MenuRectangleStartY = HorizontalMenuRectangleStartY;
//		MenuRectangleHeight = HorizontalMenuRectangleHeight;
//		MenuRectangleWidth = HorizontalMenuRectangleWidth;
//		DisplayCenterWidth = HorizontalDisplayCenterWidth;
	}

	for (int i = 0; i < stringItem.numberOfItemsInPage ; i++)
	{
		if  ( (i < 2) && (howToDraw == FULL) )
		{
			Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
					MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
					stringItem.itemsArray[i], BLACK, WHITE, 16, Font12);
		}
		if ( (i >= 2) && (i < stringItem.numberOfItemsInPage - 2) )
		{
			if (howToDraw == FULL)
			{
				Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX + MenuRectangleWidth / 2, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
				Paint_DrawRectangle( MenuRectangleStartX + MenuRectangleWidth / 2, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			}

			if ( (i == 2) )
			{
//				char localString[8] = "";
//				sprintf(localString,"%03d",stringItem.startValue);
				if (currentCursorPosition.cursorPosition == 0x02)
				{
					if ( (howToDraw == LEFT) || (howToDraw == FULL) )
					{
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_ClearWindows(MenuRectangleStartX + MenuRectangleWidth / 2 + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + MenuRectangleWidth / 2 + 1 + strlen(stringItem.valuesArray[stringItem.startValue]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.valuesArray[stringItem.startValue], &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(stringItem.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.valuesArray[stringItem.startValue], &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == UP)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(stringItem.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.valuesArray[stringItem.startValue], &Font12, WHITE,  BLACK);
					}

				}
				else if (currentCursorPosition.cursorPosition == VALUE)
				{
					if (howToDraw == RIGHT)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(stringItem.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.valuesArray[stringItem.startValue], &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						stringItem.startValue = fmax(stringItem.startValue - stringItem.deltaMultiplier, stringItem.minValue * 1.0);
//						sprintf(localString,"%05d",stringItem.startValue);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.valuesArray[stringItem.startValue], &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == UP)
					{
						stringItem.startValue = fmin(stringItem.startValue + stringItem.deltaMultiplier, stringItem.maxValue * 1.0);
//						sprintf(localString,"%05d",stringItem.startValue);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.valuesArray[stringItem.startValue], &Font12, LGRAY,  BLACK);
					}
				}
				else
				{
					Paint_ClearWindows(MenuRectangleStartX + 1,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							MenuRectangleStartX + 1 + strlen(stringItem.itemsArray[i]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							stringItem.itemsArray[i], &Font12, WHITE,  BLACK);
					Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							stringItem.valuesArray[stringItem.startValue], &Font12, WHITE,  BLACK);
				}
			}
			// Render value text of "Multiplier" with Grey or White background
			if ( (i == 3) )
			{
				char localString[8] = "";
				sprintf(localString,"%d",stringItem.deltaMultiplier);
				if (currentCursorPosition.cursorPosition == 0x03)
				{
					if ( (howToDraw == LEFT) || (howToDraw == FULL) )
					{
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_ClearWindows(MenuRectangleStartX + MenuRectangleWidth / 2 + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + MenuRectangleWidth / 2 + 1 + strlen(stringItem.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == DOWN)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(stringItem.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
					else if (howToDraw == UP)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(stringItem.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.itemsArray[i], &Font12, LGRAY,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, WHITE,  BLACK);
					}
				}
				else if (currentCursorPosition.cursorPosition == MULTIPLIER)
				{
					if (howToDraw == RIGHT)
					{
						Paint_ClearWindows(MenuRectangleStartX + 1,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								MenuRectangleStartX + 1 + strlen(stringItem.itemsArray[i]) * Font12.Width,
								MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
						Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								stringItem.itemsArray[i], &Font12, WHITE,  BLACK);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == DOWN)
					{

						multiplierIndex = 0;
						stringItem.deltaMultiplier = stringMultiplierArray[multiplierIndex];
						sprintf(localString,"%d",stringItem.deltaMultiplier);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
					else if (howToDraw == UP)
					{
						multiplierIndex = fmin(multiplierIndex + 1, 7);
						stringItem.deltaMultiplier = stringMultiplierArray[multiplierIndex];
//						sprintf(localString,"%04d",stringItem.deltaMultiplier);
						Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
								localString, &Font12, LGRAY,  BLACK);
					}
				}
				else
				{
					Paint_ClearWindows(MenuRectangleStartX + 1,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							MenuRectangleStartX + 1 + strlen(stringItem.itemsArray[i]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					Paint_DrawString_EN(MenuRectangleStartX + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							stringItem.itemsArray[i], &Font12, WHITE,  BLACK);
					Paint_DrawString_EN(MenuRectangleStartX  + MenuRectangleWidth / 2 + 1, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							localString, &Font12, WHITE,  BLACK);
				}
			}
		}
		if ( (i >= stringItem.numberOfItemsInPage - 2) && (i < stringItem.numberOfItemsInPage) )
		{
			if (howToDraw == FULL)
			{
				Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
						MenuRectangleStartX+MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1),
						BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
				if (currentCursorPosition.cursorPosition == i)
				{
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							stringItem.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
				else
				{
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							stringItem.itemsArray[i], BLACK, WHITE, 16, Font12);
				}
			}
			else if (howToDraw == DOWN)
			{
				if ( (currentCursorPosition.cursorPosition == 4) && (i == 4) )
				{
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							stringItem.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
				else if ( (currentCursorPosition.cursorPosition == 5) && (i == 5) )
				{
					Paint_ClearWindows(DisplayCenterWidth,
							MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							DisplayCenterWidth + strlen(stringItem.itemsArray[i - 1]) * Font12.Width,
							MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1 + Font12.Height, WHITE);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							stringItem.itemsArray[(i - 1)], BLACK, WHITE, 16, Font12);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
							stringItem.itemsArray[i], BLACK, LGRAY, 16, Font12);
				}
			}
			else if (howToDraw == UP)
			{
				if ( (currentCursorPosition.cursorPosition == 3) && (i == 4) )
				{
					Paint_ClearWindows(DisplayCenterWidth - strlen(stringItem.itemsArray[i]) * Font12.Width / 2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							DisplayCenterWidth + strlen(stringItem.itemsArray[i]) * Font12.Width /2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							stringItem.itemsArray[(i)], BLACK, WHITE, 16, Font12);
					//						centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * i + 1,
					//								uint16Item.itemsArray[i], BLACK, LGRAY, 16);
				}
				else if ( (currentCursorPosition.cursorPosition == 4) && (i == 5) )
				{
					Paint_ClearWindows(DisplayCenterWidth - strlen(stringItem.itemsArray[i]) * Font12.Width / 2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							DisplayCenterWidth + strlen(stringItem.itemsArray[i]) * Font12.Width /2,
							MenuRectangleStartY + MenuRectangleHeight * (i) + 1 + Font12.Height, WHITE);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i) + 1,
							stringItem.itemsArray[(i)], BLACK, WHITE, 16, Font12);
					centeredString(DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i - 1) + 1,
							stringItem.itemsArray[i - 1], BLACK, LGRAY, 16, Font12);
				}
			}
		}
	}
}

