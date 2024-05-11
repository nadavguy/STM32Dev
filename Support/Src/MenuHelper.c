/*
 * MenuHelper.c
 *
 *  Created on: Apr 20, 2021
 *      Author: gilad
 */


#include "main.h"
#include "LCD_1in8.h"

MENULEVELType menuLevel = BASIC;

tMENU_PAGE MainPage;
tMENU_PAGE rcSettingsPage;
tMENU_PAGE safeAirSettingsPage;
tMENU_PAGE blueToothSettingsPage;

tMENU_PAGE pagesArray[5];

tUINT16_ITEM brightnessItem;
tUINT16_ITEM motorDelayItem;

tSTRING_ITEM triggerModeItem;
tSTRING_ITEM armModeItem;
tSTRING_ITEM loggingModeItem;
tSTRING_ITEM platformTypeItem;
tSTRING_ITEM safeairStateItem;
//tSTRING_ITEM bleMakeVisibleItem;
//tSTRING_ITEM bleDisableItem;

tPOPUP noConnectionMessage;
tPOPUP safeairForceDisarmMessage;
tPOPUP rcClearStorageMessage;
tPOPUP safeAirClearStorageMessage;
tPOPUP bleMakeVisibleMessage;
tPOPUP bleDisableMessage;
tPOPUP massStorageMessage;

uint32_t itemIDtoUpdate = 0;

void initMenuPages(void)
{

	for (int i = 0 ; i < MAX_ITEMS_IN_PAGE ; i++ )
	{
		memset(MainPage.itemsArray[i],0 , MAX_CHARACTERS_IN_ITEM);
		memset(rcSettingsPage.itemsArray[i],0 , MAX_CHARACTERS_IN_ITEM);
		memset(safeAirSettingsPage.itemsArray[i],0 , MAX_CHARACTERS_IN_ITEM);
		memset(blueToothSettingsPage.itemsArray[i],0 , MAX_CHARACTERS_IN_ITEM);
	}

	MainPage.pageID = 1;
	if ( (menuLevel == DEVELOPER) || (menuLevel == OEM) )
	{
		MainPage.numberOfItemsInPage = 3;
		memcpy(&MainPage.itemsArray[0],"RC Settings",strlen("RC Settings"));
		memcpy(&MainPage.itemsArray[1],"SA Settings",strlen("SA Settings"));
		memcpy(&MainPage.itemsArray[2],"Close menu",strlen("Close menu"));

		MainPage.cellTypeArray[0] = PAGE;
		MainPage.cellTypeArray[1] = PAGE;
		MainPage.cellTypeArray[2] = CLOSE;

		MainPage.nextCellIDArray[0] = 2;
		MainPage.nextCellIDArray[1] = 3;
		MainPage.nextCellIDArray[2] = 0;
	}
	else
	{
		MainPage.numberOfItemsInPage = 2;
		memcpy(&MainPage.itemsArray[0],"RC Settings",strlen("RC Settings"));
//		memcpy(&MainPage.itemsArray[1],"SA Settings",strlen("SA Settings"));
		memcpy(&MainPage.itemsArray[1],"Close menu",strlen("Close menu"));

		MainPage.cellTypeArray[0] = PAGE;
//		MainPage.cellTypeArray[1] = PAGE;
		MainPage.cellTypeArray[1] = CLOSE;

		MainPage.nextCellIDArray[0] = 2;
//		MainPage.nextCellIDArray[1] = 3;
		MainPage.nextCellIDArray[1] = 0;
	}

	rcSettingsPage.pageID = 2;
	if (menuLevel == DEVELOPER)
	{
		rcSettingsPage.numberOfItemsInPage = 5;
		memcpy(&rcSettingsPage.itemsArray[0],"Brightness",strlen("Brightness"));
		memcpy(&rcSettingsPage.itemsArray[1],"Mass Storage",strlen("Mass Storage"));
		memcpy(&rcSettingsPage.itemsArray[2],"Clear Storage",strlen("Clear Storage"));
		memcpy(&rcSettingsPage.itemsArray[3],"Back",strlen("Back"));
		memcpy(&rcSettingsPage.itemsArray[4],"Close menu",strlen("Close menu"));
		rcSettingsPage.cellTypeArray[0] = UINT16_ITEM;
		rcSettingsPage.cellTypeArray[1] = POPUP;
		rcSettingsPage.cellTypeArray[2] = POPUP;
		rcSettingsPage.cellTypeArray[3] = BACK;
		rcSettingsPage.cellTypeArray[4] = CLOSE;
		rcSettingsPage.nextCellIDArray[0] = (uint32_t)&brightnessItem;
		rcSettingsPage.nextCellIDArray[1] = (uint32_t)&massStorageMessage;
		rcSettingsPage.nextCellIDArray[2] = (uint32_t)&rcClearStorageMessage;
		rcSettingsPage.nextCellIDArray[3] = 0;
		rcSettingsPage.nextCellIDArray[4] = 0;
	}
	else
	{
		rcSettingsPage.numberOfItemsInPage = 5;
		memcpy(&rcSettingsPage.itemsArray[0],"Brightness",strlen("Brightness"));
		memcpy(&rcSettingsPage.itemsArray[1],"Mass Storage",strlen("Mass Storage"));
		memcpy(&rcSettingsPage.itemsArray[2],"Clear Storage",strlen("Clear Storage"));
		memcpy(&rcSettingsPage.itemsArray[3],"Back",strlen("Back"));
		memcpy(&rcSettingsPage.itemsArray[4],"Close menu",strlen("Close menu"));
		rcSettingsPage.cellTypeArray[0] = UINT16_ITEM;
		rcSettingsPage.cellTypeArray[1] = POPUP;
		rcSettingsPage.cellTypeArray[2] = POPUP;
		rcSettingsPage.cellTypeArray[3] = BACK;
		rcSettingsPage.cellTypeArray[4] = CLOSE;
		rcSettingsPage.nextCellIDArray[0] = (uint32_t)&brightnessItem;
		rcSettingsPage.nextCellIDArray[1] = (uint32_t)&massStorageMessage;
		rcSettingsPage.nextCellIDArray[2] = (uint32_t)&rcClearStorageMessage;
		rcSettingsPage.nextCellIDArray[3] = 0;
		rcSettingsPage.nextCellIDArray[4] = 0;
	}

	safeAirSettingsPage.pageID = 3;
	safeAirSettingsPage.numberOfItemsInPage = 9;
	memcpy(&safeAirSettingsPage.itemsArray[0],"Trigger Mode",strlen("Trigger Mode"));
	memcpy(&safeAirSettingsPage.itemsArray[1],"Arm Mode",strlen("Arm Mode"));
	memcpy(&safeAirSettingsPage.itemsArray[2],"Logging Mode",strlen("Logging Mode"));
	memcpy(&safeAirSettingsPage.itemsArray[3],"Motors Delay",strlen("Motors Delay"));
	memcpy(&safeAirSettingsPage.itemsArray[4],"Platform Type",strlen("Platform Type"));
	memcpy(&safeAirSettingsPage.itemsArray[5],"Change State",strlen("Change State"));
	memcpy(&safeAirSettingsPage.itemsArray[6],"Clear Storage",strlen("Clear Storage"));
	memcpy(&safeAirSettingsPage.itemsArray[7],"Back",strlen("Back"));
	memcpy(&safeAirSettingsPage.itemsArray[8],"Close menu",strlen("Close menu"));
	safeAirSettingsPage.cellTypeArray[0] = STRING_ITEM;
	safeAirSettingsPage.cellTypeArray[1] = STRING_ITEM;
	safeAirSettingsPage.cellTypeArray[2] = STRING_ITEM;
	safeAirSettingsPage.cellTypeArray[3] = UINT16_ITEM;
	safeAirSettingsPage.cellTypeArray[4] = STRING_ITEM;
	safeAirSettingsPage.cellTypeArray[5] = STRING_ITEM;
	safeAirSettingsPage.cellTypeArray[6] = POPUP;
	safeAirSettingsPage.cellTypeArray[7] = BACK;
	safeAirSettingsPage.cellTypeArray[8] = CLOSE;
	safeAirSettingsPage.nextCellIDArray[0] = (uint32_t)&triggerModeItem;
	safeAirSettingsPage.nextCellIDArray[1] = (uint32_t)&armModeItem;
	safeAirSettingsPage.nextCellIDArray[2] = (uint32_t)&loggingModeItem;
	safeAirSettingsPage.nextCellIDArray[3] = (uint32_t)&motorDelayItem;
	safeAirSettingsPage.nextCellIDArray[4] = (uint32_t)&platformTypeItem;
	safeAirSettingsPage.nextCellIDArray[5] = (uint32_t)&safeairStateItem;
	safeAirSettingsPage.nextCellIDArray[6] = (uint32_t)&safeAirClearStorageMessage;
	safeAirSettingsPage.nextCellIDArray[7] = 0;
	safeAirSettingsPage.nextCellIDArray[8] = 0;

	blueToothSettingsPage.pageID = 4;
	blueToothSettingsPage.numberOfItemsInPage = 5;
	memcpy(&blueToothSettingsPage.itemsArray[0],"Make visible",strlen("Make visible"));
	memcpy(&blueToothSettingsPage.itemsArray[1],"Disable BLE",strlen("Disable BLE"));
//	memcpy(&blueToothSettingsPage.itemsArray[2],"Clear Storage",strlen("Clear Storage"));
	memcpy(&blueToothSettingsPage.itemsArray[2],"Back",strlen("Back"));
	memcpy(&blueToothSettingsPage.itemsArray[3],"Close menu",strlen("Close menu"));
	blueToothSettingsPage.cellTypeArray[0] = POPUP;
	blueToothSettingsPage.cellTypeArray[1] = POPUP;
//	blueToothSettingsPage.cellTypeArray[2] = POPUP;
	blueToothSettingsPage.cellTypeArray[2] = BACK;
	blueToothSettingsPage.cellTypeArray[3] = CLOSE;
	blueToothSettingsPage.nextCellIDArray[0] = (uint32_t)&bleMakeVisibleMessage;
	blueToothSettingsPage.nextCellIDArray[1] = (uint32_t)&bleDisableMessage;
//	blueToothSettingsPage.nextCellIDArray[2] = (uint32_t)&rcClearStorageMessage;
	blueToothSettingsPage.nextCellIDArray[2] = 0;
	blueToothSettingsPage.nextCellIDArray[3] = 0;


	pagesArray[1] = MainPage;
	pagesArray[2] = rcSettingsPage;
	pagesArray[3] = safeAirSettingsPage;
	pagesArray[4] = blueToothSettingsPage;

//	safeairConfiguration.MTD = 0;
//	safeairConfiguration.armMode = 0;
//	safeairConfiguration.forceDisarm = 0;
//	safeairConfiguration.formatSD = 0;
//	safeairConfiguration.loggingMode = 0;
//	safeairConfiguration.platformType = 0;
//	safeairConfiguration.state = 0;
//	safeairConfiguration.triggerMode = 0;
}

void initMenuItems(void)
{
	brightnessItem.itemID = 1;
	brightnessItem.maxValue = 10;
	brightnessItem.minValue = 1;
	brightnessItem.startValue = 10;
	brightnessItem.deltaMultiplier = 1;
	brightnessItem.numberOfItemsInPage = 6;
	brightnessItem.parameterPointer = 0x00;
	memcpy(&brightnessItem.itemsArray[0],"Brightness",strlen("Brightness"));
	memcpy(&brightnessItem.itemsArray[1],"Units: [uSec]",strlen("Units: [uSec]"));
	memcpy(&brightnessItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&brightnessItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&brightnessItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&brightnessItem.itemsArray[5],"OK",strlen("OK"));

	triggerModeItem.itemID = 2;
	triggerModeItem.maxValue = 1;
	triggerModeItem.minValue = 0;
	triggerModeItem.startValue = 0;
	triggerModeItem.deltaMultiplier = 1;
	triggerModeItem.numberOfItemsInPage = 6;
	memcpy(&triggerModeItem.itemsArray[0],"Trigger Mode",strlen("Trigger Mode"));
	memcpy(&triggerModeItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&triggerModeItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&triggerModeItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&triggerModeItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&triggerModeItem.itemsArray[5],"OK",strlen("OK"));
	triggerModeItem.numberOfValuesInArray = 2;
	memcpy(&triggerModeItem.valuesArray[0],"Manual",strlen("Manual"));
	memcpy(&triggerModeItem.valuesArray[1],"Auto  ",strlen("Auto  "));
//	triggerModeItem.parameterPointer = (uint32_t)&safeairConfiguration.triggerMode;

	armModeItem.itemID = 3;
	armModeItem.maxValue = 1;
	armModeItem.minValue = 0;
	armModeItem.startValue = 0;
	armModeItem.deltaMultiplier = 1;
	armModeItem.numberOfItemsInPage = 6;
	memcpy(&armModeItem.itemsArray[0],"Arm Mode",strlen("Arm Mode"));
	memcpy(&armModeItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&armModeItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&armModeItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&armModeItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&armModeItem.itemsArray[5],"OK",strlen("OK"));
	armModeItem.numberOfValuesInArray = 2;
	memcpy(&armModeItem.valuesArray[0],"Manual",strlen("Manual"));
	memcpy(&armModeItem.valuesArray[1],"Auto  ",strlen("Auto  "));
//	armModeItem.parameterPointer = (uint32_t)&safeairConfiguration.armMode;

	loggingModeItem.itemID = 4;
	loggingModeItem.maxValue = 3;
	loggingModeItem.minValue = 0;
	loggingModeItem.startValue = 0;
	loggingModeItem.deltaMultiplier = 1;
	loggingModeItem.numberOfItemsInPage = 6;
	memcpy(&loggingModeItem.itemsArray[0],"Logging Mode",strlen("Logging Mode"));
	memcpy(&loggingModeItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&loggingModeItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&loggingModeItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&loggingModeItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&loggingModeItem.itemsArray[5],"OK",strlen("OK"));
	loggingModeItem.numberOfValuesInArray = 4;
	memcpy(&loggingModeItem.valuesArray[0],"0 - Raw ",strlen("0 - Raw "));
	memcpy(&loggingModeItem.valuesArray[1],"Minimal ",strlen("Minimal "));
	memcpy(&loggingModeItem.valuesArray[2],"Ext. IMU",strlen("Ext. IMU"));
	memcpy(&loggingModeItem.valuesArray[3],"Diluted ",strlen("Diluted "));
//	loggingModeItem.parameterPointer = (uint32_t)&safeairConfiguration.loggingMode;

	motorDelayItem.itemID = 5;
	motorDelayItem.maxValue = 5000;
	motorDelayItem.minValue = 50;
	motorDelayItem.startValue = 50;
	motorDelayItem.deltaMultiplier = 1;
	motorDelayItem.numberOfItemsInPage = 6;
	motorDelayItem.parameterPointer = 0x00;
	memcpy(&motorDelayItem.itemsArray[0],"Motor Delay",strlen("Motor Delay"));
	memcpy(&motorDelayItem.itemsArray[1],"Units: [mSec]",strlen("Units: [mSec]"));
	memcpy(&motorDelayItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&motorDelayItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&motorDelayItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&motorDelayItem.itemsArray[5],"OK",strlen("OK"));

	platformTypeItem.itemID = 6;
	platformTypeItem.maxValue = 4;
	platformTypeItem.minValue = 1;
	platformTypeItem.startValue = 1;
	platformTypeItem.deltaMultiplier = 1;
	platformTypeItem.numberOfItemsInPage = 6;
	memcpy(&platformTypeItem.itemsArray[0],"Platform Type",strlen("Platform Type"));
	memcpy(&platformTypeItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&platformTypeItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&platformTypeItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&platformTypeItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&platformTypeItem.itemsArray[5],"OK",strlen("OK"));
	platformTypeItem.numberOfValuesInArray = 4;
	memcpy(&platformTypeItem.valuesArray[0],"Multi-rotor    ",strlen("Multi-rotor    "));
	memcpy(&platformTypeItem.valuesArray[1],"VTOL Vertical  ",strlen("VTOL Vertical  "));
	memcpy(&platformTypeItem.valuesArray[2],"VTOL Transition",strlen("VTOL Transition"));
	memcpy(&platformTypeItem.valuesArray[3],"VTOL Horizontal",strlen("VTOL Horizontal"));
//	platformTypeItem.parameterPointer = (uint32_t)&safeairConfiguration.platformType;

	safeairStateItem.itemID = 7;
	safeairStateItem.maxValue = 4;
	safeairStateItem.minValue = 3;
	safeairStateItem.startValue = 3;
	safeairStateItem.deltaMultiplier = 1;
	safeairStateItem.numberOfItemsInPage = 6;
	memcpy(&safeairStateItem.itemsArray[0],"Platform Type",strlen("Platform Type"));
	memcpy(&safeairStateItem.itemsArray[1],"Units: [N/A]",strlen("Units: [N/A]"));
	memcpy(&safeairStateItem.itemsArray[2],"Value",strlen("Value"));
	memcpy(&safeairStateItem.itemsArray[3],"Delta",strlen("Delta"));
	memcpy(&safeairStateItem.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&safeairStateItem.itemsArray[5],"OK",strlen("OK"));
	safeairStateItem.numberOfValuesInArray = 2;
	memcpy(&safeairStateItem.valuesArray[0],"Maintenance     ",strlen("Maintenance     "));
	memcpy(&safeairStateItem.valuesArray[1],"Auto-Calibration",strlen("Auto-Calibration"));
//	safeairStateItem.parameterPointer = (uint32_t)&safeairConfiguration.state;

//	bleMakeVisibleItem.itemID = 4;
//	bleMakeVisibleItem.maxValue = 1;
//	bleMakeVisibleItem.minValue = 0;
//	bleMakeVisibleItem.startValue = 0;
//	bleMakeVisibleItem.deltaMultiplier = 1;
//	bleMakeVisibleItem.numberOfItemsInPage = 6;
//	memcpy(&bleMakeVisibleItem.itemsArray[0],"Bluetooth",strlen("Bluetooth"));
//	memcpy(&bleMakeVisibleItem.itemsArray[1],"Make visible",strlen("Make visible"));
//	memcpy(&bleMakeVisibleItem.itemsArray[2],"Value",strlen("Value"));
//	memcpy(&bleMakeVisibleItem.itemsArray[3],"Delta",strlen("Delta"));
//	memcpy(&bleMakeVisibleItem.itemsArray[4],"Cancel",strlen("Cancel"));
//	memcpy(&bleMakeVisibleItem.itemsArray[5],"OK",strlen("OK"));
//	bleMakeVisibleItem.numberOfValuesInArray = 2;
//	memcpy(&bleMakeVisibleItem.valuesArray[0],"On ",strlen("On "));
//	memcpy(&bleMakeVisibleItem.valuesArray[1],"Off",strlen("Off"));
//	bleMakeVisibleItem.parameterPointer = (uint32_t)&isBLEOn;
}

void initPopupMessages(void)
{
	noConnectionMessage.popupID = 1;
	noConnectionMessage.numberOfItemsInPopup = 6;
	noConnectionMessage.isQuestion = true;
	memcpy(&noConnectionMessage.itemsArray[0],"SafeAir unit",strlen("SafeAir unit"));
	memcpy(&noConnectionMessage.itemsArray[1],"not detected,",strlen("not detected,"));
	memcpy(&noConnectionMessage.itemsArray[2],"Changes will",strlen("Changes will "));
	memcpy(&noConnectionMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&noConnectionMessage.itemsArray[4],"Cancel",strlen("Cancel"));
	memcpy(&noConnectionMessage.itemsArray[5],"OK (Long Press)",strlen("OK (Long Press)"));

	safeairForceDisarmMessage.popupID = 2;
	safeairForceDisarmMessage.numberOfItemsInPopup = 5;
	safeairForceDisarmMessage.isQuestion = true;
	memcpy(&safeairForceDisarmMessage.itemsArray[0],"Force Disarm",strlen("Force Disarm"));
	memcpy(&safeairForceDisarmMessage.itemsArray[1],"SafeAir unit?,",strlen("SafeAir unit?"));
	memcpy(&safeairForceDisarmMessage.itemsArray[2],"Are you sure?",strlen("Are you sure?"));
//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&safeairForceDisarmMessage.itemsArray[3],"Cancel",strlen("Cancel"));
	memcpy(&safeairForceDisarmMessage.itemsArray[4],"OK (Long Press)",strlen("OK (Long Press)"));

	rcClearStorageMessage.popupID = 3;
	rcClearStorageMessage.numberOfItemsInPopup = 5;
	rcClearStorageMessage.isQuestion = true;
	memcpy(&rcClearStorageMessage.itemsArray[0],"Clear RC",strlen("Clear RC"));
	memcpy(&rcClearStorageMessage.itemsArray[1],"Storage,",strlen("Storage,"));
	memcpy(&rcClearStorageMessage.itemsArray[2],"Are you sure?",strlen("Are you sure?"));
//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&rcClearStorageMessage.itemsArray[3],"Cancel",strlen("Cancel"));
	memcpy(&rcClearStorageMessage.itemsArray[4],"OK (Long Press)",strlen("OK (Long Press)"));

	safeAirClearStorageMessage.popupID = 4;
	safeAirClearStorageMessage.numberOfItemsInPopup = 5;
	safeAirClearStorageMessage.isQuestion = true;
	memcpy(&safeAirClearStorageMessage.itemsArray[0],"Clear SafeAir",strlen("Clear SafeAir"));
	memcpy(&safeAirClearStorageMessage.itemsArray[1],"Storage,",strlen("Storage,"));
	memcpy(&safeAirClearStorageMessage.itemsArray[2],"Are you sure?",strlen("Are you sure?"));
	//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&safeAirClearStorageMessage.itemsArray[3],"Cancel",strlen("Cancel"));
	memcpy(&safeAirClearStorageMessage.itemsArray[4],"OK (Long Press)",strlen("OK (Long Press)"));

	bleMakeVisibleMessage.popupID = 5;
	bleMakeVisibleMessage.numberOfItemsInPopup = 5;
	bleMakeVisibleMessage.isQuestion = true;
	memcpy(&bleMakeVisibleMessage.itemsArray[0],"Make bluetooth",strlen("Make bluetooth"));
	memcpy(&bleMakeVisibleMessage.itemsArray[1],"visible for",strlen("visible for"));
	memcpy(&bleMakeVisibleMessage.itemsArray[2],"detection?",strlen("detection?"));
	//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&bleMakeVisibleMessage.itemsArray[3],"No",strlen("No"));
	memcpy(&bleMakeVisibleMessage.itemsArray[4],"Yes",strlen("Yes"));

	bleDisableMessage.popupID = 6;
	bleDisableMessage.numberOfItemsInPopup = 4;
	bleDisableMessage.isQuestion = true;
	memcpy(&bleDisableMessage.itemsArray[0],"Disable bluetooth",strlen("Disable bluetooth"));
	memcpy(&bleDisableMessage.itemsArray[1],"module?",strlen("module?"));
//	memcpy(&bleDisableMessage.itemsArray[2],"detection?",strlen("detection?"));
	//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&bleDisableMessage.itemsArray[2],"No",strlen("No"));
	memcpy(&bleDisableMessage.itemsArray[3],"Yes",strlen("Yes"));

	massStorageMessage.popupID = 7;
	massStorageMessage.numberOfItemsInPopup = 4;
	massStorageMessage.isQuestion = true;
	memcpy(&massStorageMessage.itemsArray[0],"Change to mass",strlen("Change to mass"));
	memcpy(&massStorageMessage.itemsArray[1],"storage device?",strlen("storage device?"));
//	memcpy(&massStorageMessage.itemsArray[2],"storage?",strlen("detection?"));
	//	memcpy(&safeairForceDisarmMessage.itemsArray[3],"be overwritten",strlen("be overwritten"));
	memcpy(&massStorageMessage.itemsArray[2],"No",strlen("No"));
	memcpy(&massStorageMessage.itemsArray[3],"Yes",strlen("Yes"));
}

void updateSelection(void)
{
	if ( (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] == CLOSE)
			&& (currentCursorPosition.currentPageID != 0x00) )
	{
		shouldRenderMenu = false;
		isMenuDisplayed = false;
//		shouldReDrawPlatformIcon = true;
//		shouldReDrawAutoPilotIcon = true;
//		shouldRedrawSignalStrengthIcon = true;
//		shouldReDrawBluetoothIcon = true;
//		shouldReDrawTriggerModeIcon = true;
//		shouldRedrawBatteryIcon = true;
//		shouldUpdatePlatformText = true;
//		shouldUpdateStatusText = true;
		setFullDisplay();
		screenClear();
		createEmptyFrame(false);
		screenUpdate(false);
	}
	else if ( (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] == BACK)
			&& (currentCursorPosition.currentPageID != 0x00) )
	{
		currentCursorPosition.cursorPosition = currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1];
		currentCursorPosition.currentPageID = currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1];
		currentCursorPosition.menuDepth--;
		shouldRenderMenu = true;
		shouldRenderItem = false;
		shouldRenderPopup = false;
	}
	else if ( (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] == PAGE)
			&& (currentCursorPosition.currentPageID != 0x00) )
	{
		currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth] = currentCursorPosition.cursorPosition;
		currentCursorPosition.previousPageID[currentCursorPosition.menuDepth] = currentCursorPosition.currentPageID;
		currentCursorPosition.currentPageID = pagesArray[currentCursorPosition.currentPageID].nextCellIDArray[currentCursorPosition.cursorPosition];
		currentCursorPosition.cursorPosition = 0;
		currentCursorPosition.menuDepth++;
		shouldRenderMenu = true;
		shouldRenderItem = false;
		shouldRenderPopup = false;
	}
	else if ( (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] == POPUP)
			&& (currentCursorPosition.currentPageID != 0x00) )
	{
		memcpy(&popupToShow, (uint32_t *)pagesArray[currentCursorPosition.currentPageID].nextCellIDArray[currentCursorPosition.cursorPosition] , sizeof(popupToShow));
		shouldRenderMenu = false;
		shouldRenderItem = false;
		shouldRenderPopup = true;
		popupDrawDirection = FULL;
		waitForPopupInput();
//
//		currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth] = currentCursorPosition.cursorPosition;
//		currentCursorPosition.previousPageID[currentCursorPosition.menuDepth] = currentCursorPosition.currentPageID;
//		currentCursorPosition.currentPageID = pagesArray[currentCursorPosition.currentPageID].nextCellIDArray[currentCursorPosition.cursorPosition];
//		currentCursorPosition.cursorPosition = 0;
//		currentCursorPosition.menuDepth++;
		isMenuDisplayed = true;
		shouldRenderMenu = true;
		shouldRenderItem = false;
		shouldRenderPopup = false;
	}
	else // handling Item navigation
	{
		if ( (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] != VALUE)
				&& (pagesArray[currentCursorPosition.currentPageID].cellTypeArray[currentCursorPosition.cursorPosition] != MULTIPLIER)
				&& (currentCursorPosition.currentPageID != 0x00))
		{
			currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth] = currentCursorPosition.cursorPosition;
			currentCursorPosition.previousPageID[currentCursorPosition.menuDepth] = currentCursorPosition.currentPageID;
			currentCursorPosition.currentPageID = 0;
			currentCursorPosition.cursorPosition = 2;
			currentCursorPosition.menuDepth++;
			shouldRenderMenu = false;
			shouldRenderItem = true;
			shouldRenderPopup = false;
		}
		else if ( ( (currentCursorPosition.cursorPosition == 0x02) || (currentCursorPosition.cursorPosition == VALUE) )
				&& (currentCursorPosition.currentPageID == 0x00) && (isItemDisplayed) )
		{
			shouldRenderMenu = false;
			shouldRenderItem = true;
			shouldRenderPopup = false;
		}
		else if ( ( (currentCursorPosition.cursorPosition == 0x03) || (currentCursorPosition.cursorPosition == MULTIPLIER) )
				&& (currentCursorPosition.currentPageID == 0x00) && (isItemDisplayed) )
		{
			shouldRenderMenu = false;
			shouldRenderItem = true;
			shouldRenderPopup = false;
		}
		else if ( (currentCursorPosition.cursorPosition == 0x04)
				&& (currentCursorPosition.currentPageID == 0x00) && (isMenuDisplayed) && (!isItemDisplayed) )
		{
			currentCursorPosition.cursorPosition = currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1];
			currentCursorPosition.currentPageID = currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1];
			currentCursorPosition.menuDepth--;
			isMenuDisplayed = true;
			shouldClearScreen = true;
			shouldRenderMenu = true;
			shouldRenderItem = false;
			shouldRenderPopup = false;
		}
		else if ( (currentCursorPosition.cursorPosition == 0x05)
				&& (currentCursorPosition.currentPageID == 0x00) && (isMenuDisplayed) && (!isItemDisplayed) )
		{
			if ( pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1]].
					cellTypeArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth - 1]] == UINT16_ITEM )
			{
				memcpy((uint32_t *)pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth -1]].
						nextCellIDArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1]], &uint16Item,  sizeof(tUINT16_ITEM));
			}
			else if (pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1]].
					cellTypeArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth - 1]] == STRING_ITEM)
			{
				memcpy((uint32_t *)pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth -1]].
						nextCellIDArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1]], &stringItem,  sizeof(tSTRING_ITEM));
			}
			currentCursorPosition.cursorPosition = currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1];
			currentCursorPosition.currentPageID = currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1];
			currentCursorPosition.menuDepth--;
			isItemDisplayed = false;
			isMenuDisplayed = true;
			shouldClearScreen = true;
			shouldRenderMenu = true;
			shouldRenderItem = false;
			shouldRenderPopup = false;
		}
	}
}

void updateSelectedParameter(void)
{
	if (itemIDtoUpdate == 1)
	{
//		ee.backLight = brightnessItem.startValue;
//		LCD_2IN4_SetBackLight(1000);
//		ee_save1();
	}
	else if (itemIDtoUpdate == 2)
	{
		//Send to Sma - How to Block if SMA not connected
//		safeairConfiguration.triggerMode = stringItem.startValue + 1;
//		sendSafeAirConfigurationMessage();
//		configurationMessageCounter++;
//		memset(stringItem, 0, sizeof(stringItem));
	}
	else if (itemIDtoUpdate == 3)
	{
//		safeairConfiguration.armMode = stringItem.startValue + 1;
//		configurationMessageCounter++;
	}
	else if (itemIDtoUpdate == 4)
	{
//		safeairConfiguration.loggingMode = stringItem.startValue + 1;
//		configurationMessageCounter++;
	}
	else if (itemIDtoUpdate == 5)
	{
//		safeairConfiguration.MTD = stringItem.startValue;
//		configurationMessageCounter++;
	}
	else if (itemIDtoUpdate == 6)
	{
//		safeairConfiguration.platformType = stringItem.startValue + 1;
//		configurationMessageCounter++;
	}
}
