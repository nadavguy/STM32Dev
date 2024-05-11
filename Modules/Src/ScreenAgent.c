/*
 * ScreenAgent.c
 *
 *  Created on: Mar 25, 2021
 *      Author: gilad
 */


#include "main.h"
#include "image.h"

#include "LogoImages.h"
#include "LEDImages.h"
#include "FanImages.h"
#include "BatteryImages.h"
//#include "LCD_Test.h"
#include "GUI_Paint.h"
#include "LCD_1in8.h"
#include "DEV_Config.h"

#include "PushButtonAgent.h"

const unsigned char *previousBluetoothImage;
const unsigned char *previousPlatformImage;
const unsigned char *previousAutoPilotImage;
const unsigned char *previousTriggerModeImage;
const unsigned char *previousSignalImage;
const unsigned char *previousBatteryImage;
const unsigned char *previousRCBatteryImage;

bool shouldRenderBatteryPercent = false;
bool shouldRenderMenu = false;
bool isMenuDisplayed = false;
bool shouldClearScreen = false;
bool shouldRenderItem = false;
bool isItemDisplayed = false;
bool isParameterUpdateRequired = false;
bool shouldRenderPopup = false;
bool isPopupDisplayed = false;
bool isPortrait = true;
bool renderCompleteFrame = false;
bool isBluetoothDisplayed = false;
bool isAutoPilotDisplayed = false;
bool isPlatformDisplayed = false;
bool isTriggerModeDisplayed = true;
bool isSafeAirBatteryDisplayed = true;
bool isAltitudeDisplayed = true;
bool isGPSPositionDisplayed = false;

uint8_t PlatfomTypeX = 0;
uint8_t PlatfomTypeY = 0;
uint8_t AutoPilotX = 0;
uint8_t AutoPilotY = 0;
uint8_t TBSSignalX = 0;
uint8_t TBSSignalY = 0;
uint8_t BluetoothX = 0;
uint8_t BluetoothY = 0;
uint8_t TriggerModeX = 0;
uint8_t TriggerModeY = 0;
uint8_t BatteryX = 0;
uint8_t BatteryY = 0;

uint8_t SystemTextX = 0;
uint8_t SystemTextY = 0;

uint8_t TempMeasurementX = 0;
uint8_t TempMeasurementY = 0;

uint8_t SetPointTextX = 0;
uint8_t SetPointTextY = 0;

uint8_t SetPointValueX = 0;
uint8_t SetPointValueY = 0;

uint8_t SafeAirBatteryX = 0;
uint8_t SafeAirBatteryY = 0;
uint8_t Parachute1X = 0;
uint8_t Parachute1Y = 0;
uint8_t Parachute2X = 0;
uint8_t Parachute2Y = 0;
uint8_t SystemStatusTextX = 0;
uint8_t SystemStatusTextY = 0;
uint8_t WarningIconX = 0;
uint8_t WarningIconY = 0;
uint8_t WarningTextX = 0;
uint8_t WarningTextY = 0;

uint32_t lastThermistorUpdate = 0;
uint32_t lastBITStatusChange = 0;
uint32_t lastFrameDisplayed = 0;
uint32_t lastFullFrameDisplayed = 0 ;
uint32_t lastLidarBoresight = 0;

float lidarBoresightAngle = 0;
float currentLidarAngle = 0;

tUINT8_ITEM uint8Item;
tUINT16_ITEM uint16Item;
tUINT32_ITEM uint32Item;

tSTRING_ITEM stringItem;

MENUDRAWType menuDrawDirection = FULL;
MENUDRAWType itemDrawDirection = FULL;
MENUDRAWType popupDrawDirection = FULL;

tPOPUP popupToShow;

tIMAGE_DATA statusBarImageArray[5];
tIMAGE_DATA safeairBarImageArray[5];

uint8_t nextFrameToDraw[40960] = {0xFF};

void screenInit(void)
{
	isPortrait = true;
	DEV_Module_Init();

	if (isPortrait)
	{
		LCD_1IN8_Init(L2R_U2D);
		LCD_1IN8_Clear(BLACK);
		Paint_NewImage(LCD_1IN8_HEIGHT,LCD_1IN8_WIDTH, 0, WHITE);
	}
	else
	{
		LCD_1IN8_Init(U2D_R2L);
		LCD_1IN8_Clear(BLACK);
		Paint_NewImage(LCD_1IN8_WIDTH,LCD_1IN8_HEIGHT, 0, WHITE);
	}

	Paint_SetClearFuntion(LCD_1IN8_Clear);
	Paint_SetDisplayFuntion(LCD_1IN8_DrawPaint);

//	printf("Paint_Clear\r\n");
	Paint_Clear(WHITE);
	DEV_Delay_ms(1000);

	if (isPortrait)
	{
		Paint_DrawImage(gImage_Rain, 0, 0, 128, 128);
		Paint_DrawString_EN(1, 130, "Version", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (1, 142 , versionID, 2,  &Font12, BLACK, WHITE);
		Paint_DrawString_EN(70, 130, "BuildID", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (70, 142 , buildID, 2,  &Font12, BLACK, WHITE);
	}
	else
	{
		Paint_DrawImage(gImage_Rain, 16, 0, 128, 128);
		Paint_DrawString_EN(1, 98, "Version", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (1, 110 , versionID, 2,  &Font12, BLACK, WHITE);
		Paint_DrawString_EN(104, 98, "BuildID", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (124, 110 , buildID, 2,  &Font12, BLACK, WHITE);
	}


	HAL_Delay(1000);
}

void screenClear(void)
{
	if (isPortrait)
	{
		Paint_NewImage(LCD_1IN8_HEIGHT,LCD_1IN8_WIDTH, 0, WHITE);
	}
	else
	{
		Paint_NewImage(LCD_1IN8_WIDTH,LCD_1IN8_HEIGHT, 0, WHITE);
	}

	Paint_Clear(WHITE);
	DEV_Delay_ms(1000);
}

void centeredString(UWORD XCenterstart, UWORD Ystart, const char * pString, uint16_t textColor, uint16_t backgroundColor, uint8_t numberOfCharactersToClear, sFONT localFont)
{
	uint8_t Xstart = 0;

	Xstart = fmax( XCenterstart - numberOfCharactersToClear * localFont.Width / 2, 0) ;
//	Paint_DrawString_EN(Xstart, Ystart, "MAINTENANCE", &Font12, WHITE,  WHITE);
	if (!renderCompleteFrame)
	{
		Paint_ClearWindows(Xstart, Ystart, Xstart + numberOfCharactersToClear * localFont.Width, Ystart + localFont.Height, WHITE);
	}
	else if ( (renderCompleteFrame) && (!isMenuDisplayed) && (!isPopupDisplayed) )
	{
		Paint_ClearWindows(Xstart, Ystart, Xstart + numberOfCharactersToClear * localFont.Width, Ystart + localFont.Height, backgroundColor);
	}
	else if ( (renderCompleteFrame) && ( (isMenuDisplayed) || (isPopupDisplayed) ) )
	{
		Paint_ClearWindows(Xstart, Ystart, Xstart + numberOfCharactersToClear * localFont.Width, Ystart + localFont.Height, WHITE);
	}
	Xstart = strlen(pString);
	Xstart = fmax( XCenterstart - strlen(pString) * localFont.Width / 2, 0) ;
	Paint_DrawString_EN(Xstart, Ystart, pString, &localFont, backgroundColor,  textColor);
}

void screenUpdate(bool drawDeltaImage)
{

	setIconPositionOnScreen();
	if ( (!isMenuDisplayed) && (!isPopupDisplayed) )
	{
		createEmptyFrame(false);
		//TODO: Draw data to screen

		/*Current Measurement Disaply*/
		for (int i = 0; i <= 98; i++)
		{
			Paint_DrawLine(20 + i, baroReadingArray[i], 20 + i, baroReadingArray[i + 1], CYAN, DOT_PIXEL_1X1, LINE_STYLE_SOLID); // Horizontal line
		}

		/*LED State Indication*/
//		switch (LEDSwitchState)
//		{
//			case (SwitchOff):
//			{
//				addImageToNextFrame(gImage_LEDOff, 40, 28, 5, 30);
//				break;
//			}
//			case (SwitchOn):
//			{
//				addImageToNextFrame(gImage_LEDOn, 40, 28, 5, 30);
//				break;
//			}
//			default:
//			{
//				break;
//			}
//		}


//		if (isBatteryCharging)
//		{
//			addImageToNextFrame(gImage_ChargingBattery, 40, 18, 85, 30);
//		}
//		else
//		{
//			addImageToNextFrame(gImage_ChargingOff, 40, 18, 85, 30);
//		}
//
//
//		//(XCenterstart, Ystart, pString, textColor, backgroundColor, numberOfCharactersToClear, localFont)
		char localAmps[12]= "";
		sprintf(localAmps,"%6.3f", ms5607Baro.rawData.air_pressure_out);
//		if (milliAmpsForDisplay <= 2500)
//		{
			centeredString(64, 86, localAmps, WHITE, BLACK, 8, Font8);
//		}
//		else
//		{
//			centeredString(64, 86, localAmps, RED, BLACK, 8, Font8);
//		}

	}
	else if (isMenuDisplayed)
	{
		if (shouldRenderMenu)
		{
			drawMenu(shouldClearScreen, menuDrawDirection);
			shouldRenderMenu = false;
		}
		if (shouldRenderItem)
		{
			drawItem(false, itemDrawDirection);
			shouldRenderItem = false;
		}

	} // End of is Menu displayed
	if(shouldRenderPopup)
	{
		drawPopup();
		shouldRenderPopup = false;
	}
}

void drawMenu(bool clearScreen, MENUDRAWType howToDraw)
{
	if (clearScreen)
	{
		Paint_Clear(WHITE);
		createEmptyFrame(true);
	}

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

	if (howToDraw == FULL)
	{
		for (int i = 0; i < pagesArray[currentCursorPosition.currentPageID].numberOfItemsInPage; i++)
		{
			Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
					MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * ( i + 1),
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			if (i == currentCursorPosition.cursorPosition)
			{
				centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * i,
						pagesArray[currentCursorPosition.currentPageID].itemsArray[i], BLACK, LGRAY, 16, Font12);
			}
			else
			{
				centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * i,
						pagesArray[currentCursorPosition.currentPageID].itemsArray[i], BLACK, WHITE, 16, Font12);
			}
		}
	}
	else if (howToDraw == UP)
	{
		centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * (currentCursorPosition.cursorPosition + 1),
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition + 1], BLACK, WHITE, 16, Font12);
		centeredString(DisplayCenterWidth, MenuRectangleStartY+ 1 + MenuRectangleHeight * currentCursorPosition.cursorPosition,
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition], BLACK, LGRAY, 16, Font12);
	}
	else if (howToDraw == DOWN)
	{
		centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * (currentCursorPosition.cursorPosition - 1),
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition - 1], BLACK, WHITE, 16, Font12);
		centeredString(DisplayCenterWidth, MenuRectangleStartY+ 1 + MenuRectangleHeight * currentCursorPosition.cursorPosition,
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition], BLACK, LGRAY, 16, Font12);
	}
}

void drawItem(bool clearScreen, MENUDRAWType howToDraw)
{
	if ((clearScreen) || (!isItemDisplayed) )
	{
		Paint_Clear(WHITE);
		createEmptyFrame(true);
	}
	if ( pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1]].
			cellTypeArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth - 1]] == UINT16_ITEM )
	{
		if ( !(isItemDisplayed) )
		{
			multiplierIndex = 0;
			memcpy(&uint16Item, (uint32_t *)pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth -1]].
					nextCellIDArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1]], sizeof(tUINT16_ITEM));
			itemIDtoUpdate = uint16Item.itemID;
		}
		isItemDisplayed = true;
		updateUint16Item(howToDraw);
	}
	if ( pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1]].
			cellTypeArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth - 1]] == STRING_ITEM )
	{
		if ( !(isItemDisplayed) )
		{
			multiplierIndex = 0;
			memcpy(&stringItem, (uint32_t *)pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth -1]].
					nextCellIDArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1]], sizeof(tSTRING_ITEM));
			itemIDtoUpdate = stringItem.itemID;
		}
		isItemDisplayed = true;
		updateStringItem(howToDraw);
	}
}

void drawPopup(void)
{
	uint8_t MenuRectangleStartX = 0;
	uint8_t MenuRectangleStartY = 0;
	uint8_t MenuRectangleHeight = 0;
	uint8_t MenuRectangleWidth = 0;
	uint8_t DisplayCenterWidth = 0;
	uint8_t PopupRectangleHeight = 0;
	uint8_t QuestionRectangleHeight = 0;

	if (isPortrait)
	{
		MenuRectangleStartX = VerticalMenuRectangleStartX;
		MenuRectangleStartY = VerticalMenuRectangleStartY;
		MenuRectangleHeight = VerticalMenuRectangleHeight;
		MenuRectangleWidth = VerticalMenuRectangleWidth;
		DisplayCenterWidth = VerticalDisplayCenterWidth;
		PopupRectangleHeight = VerticalPopupRectangleHeight;
		QuestionRectangleHeight = VerticalQuestionRectangleHeight;
	}
	else
	{
//		MenuRectangleStartX = HorizontalMenuRectangleStartX;
//		MenuRectangleStartY = HorizontalMenuRectangleStartY;
//		MenuRectangleHeight = HorizontalMenuRectangleHeight;
//		MenuRectangleWidth = HorizontalMenuRectangleWidth;
//		DisplayCenterWidth = HorizontalDisplayCenterWidth;
//		PopupRectangleHeight = HorizontalPopupRectangleHeight;
//		QuestionRectangleHeight = HorizontalQuestionRectangleHeight;
	}

	isPopupDisplayed = true;
	isItemDisplayed = false;
	isMenuDisplayed = false;
	if (popupDrawDirection == FULL)
	{
		Paint_Clear(WHITE);
		createEmptyFrame(true);
		Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY ,
				MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + PopupRectangleHeight,
				BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );

		if (popupToShow.isQuestion)
		{
			Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + QuestionRectangleHeight,
					MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + QuestionRectangleHeight + MenuRectangleHeight,
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
		}

		Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + PopupRectangleHeight,
				MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + PopupRectangleHeight + MenuRectangleHeight,
				BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );

		for (int i = 0 ; i < popupToShow.numberOfItemsInPopup - 2; i++)
		{
			centeredString( DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1) + 1,
					popupToShow.itemsArray[i], BLACK, WHITE, 16, Font12);
		}
	}

	if (popupToShow.isQuestion)
	{
		if ( (popupDrawDirection == FULL) || (popupDrawDirection == UP))
		{
			centeredString( DisplayCenterWidth, MenuRectangleStartY + QuestionRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 2], BLACK, LGRAY, 16, Font12);

			centeredString( DisplayCenterWidth, MenuRectangleStartY + PopupRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, WHITE, 16, Font12);
		}
		else
		{
			centeredString( DisplayCenterWidth, MenuRectangleStartY + QuestionRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 2], BLACK, WHITE, 16, Font12);

			centeredString( DisplayCenterWidth, MenuRectangleStartY + PopupRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, LGRAY, 16, Font12);
		}
	}
	else
	{
		centeredString( DisplayCenterWidth, MenuRectangleStartY + PopupRectangleHeight + 1,
				popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, LGRAY, 16, Font12);
	}
}

void setFullDisplay(void)
{
//	shouldRedrawBatteryIcon = true;
//	shouldRedrawSignalStrengthIcon = true;
//	shouldReDrawBluetoothIcon = isBLEOn;
//
//	shouldUpdatePlatformText = true;
//
//	shouldUpdateStatusText = true;
//
//	shouldReDrawAutoPilotIcon = false;
//	shouldReDrawPlatformIcon = false;
//	shouldReDrawTriggerModeIcon = true;
//	shouldRedrawSafeAirBatteryIcon = true;
//
//	shouldClearDisplayedWarning = false;
	isPopupDisplayed = false;
	isMenuDisplayed = false;
	isItemDisplayed = false;
	shouldRenderPopup = false;
	shouldRenderItem = false;
	shouldRenderMenu = false;

//	shouldDrawRedAlertIcon = false;
}

void setIconPositionOnScreen(void)
{
	if (isPortrait)
	{

//		BluetoothX = VerticalBluetoothX;
//		BluetoothY = VerticalBluetoothY;
//		TBSSignalX = VerticalTBSSignalX;
//		TBSSignalY = VerticalTBSSignalY;
//		BatteryX = VerticalBatteryX;
//		BatteryY = VerticalBatteryY;
//
//		SystemStatusTextX = VerticalSystemStatusTextX;
//		SystemStatusTextY = VerticalSystemStatusTextY;
//
		SystemTextX = VerticalSystemTextX;
		SystemTextY = VerticalSystemTextY;

		TempMeasurementX = VerticalTempMeasurementX;
		TempMeasurementY = VerticalTempMeasurementY;

		SetPointTextX = VerticalSetPointTextX;
		SetPointTextY = VerticalSetPointTextY;

		SetPointValueX = VerticalSetPointValueX;
		SetPointValueY = VerticalSetPointValueY;
//
//		WarningTextX = VerticalWarningTextX;
//		WarningTextY = VerticalWarningTextY;


//		SafeAirBatteryX = (numberOfDisplayedSafeAirIcons /2 - 1 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;//VerticalSafeAirBatteryX;
//		SafeAirBatteryY = VerticalSafeAirBatteryY;
//		TriggerModeX = (numberOfDisplayedSafeAirIcons /2 - 2 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;
//		TriggerModeY = VerticalTriggerModeY;
//		PlatfomTypeX = (numberOfDisplayedSafeAirIcons /2 - 3 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;
//		PlatfomTypeY = VerticalPltfomTypeY;
//		AutoPilotX = (numberOfDisplayedSafeAirIcons /2 - 4 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;
//		AutoPilotY = VerticalAutoPilotY;
	}
	else
	{
//		PlatfomTypeX = HorizontalPltfomTypeX;
//		PlatfomTypeY = HorizontalPltfomTypeY;
//		AutoPilotX = HorizontalAutoPilotX;
//		AutoPilotY = HorizontalAutoPilotY;
//		TBSSignalX = HorizontalTBSSignalX;
//		TBSSignalY = HorizontalTBSSignalY;
//		BluetoothX = HorizontalBluetoothX;
//		BluetoothY = HorizontalBluetoothY;
//		TriggerModeX = HorizontalTriggerModeX;
//		TriggerModeY = HorizontalTriggerModeY;
//		BatteryX = HorizontalBatteryX;
//		BatteryY = HorizontalBatteryY;
//		SystemTextX = HorizontalSystemTextX;
//		SystemTextY = HorizontalSystemTextY;
//		SafeAirBatteryX = HorizontalSafeAirBatteryTextX;
//		SafeAirBatteryY = HorizontalSafeAirBatteryTextY;

	}
}
