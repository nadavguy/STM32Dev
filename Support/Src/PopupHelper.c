/*
 * popupHelper.c
 *
 *  Created on: May 2, 2021
 *      Author: gilad
 */


#include "main.h"
//#include "usb_device.h"

void waitForPopupInput(void)
{
	if (popupToShow.popupID != 0)
	{
		shouldRenderPopup = true;
		screenUpdate(false);
		switch (popupToShow.popupID)
		{
			case 1:
			{

//				while ( (tbsLink == NOSIGNAL) )
//				{
//					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
//					{
//						break;
//					}
//					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
//					{
//						break;
//					}
//					sendChannelMessageToTBS();
//					updateRCState();
//					CheckButtons();
////					HAL_Delay(50);
//					screenUpdate(false);
//					updateNextFrame();
//				}
				break;
			}
			case 2:
			{
//				while ( (okButtonPressDuration < 3000) )
//				{
//					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
//					{
//						break;
//					}
//					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
//					{
//						forceDisarmEnabled = true;
//						waitForAckResponse = true;
//						break;
//					}
//					sendChannelMessageToTBS();
//					updateRCState();
//					CheckButtons();
////					HAL_Delay(50);
//					screenUpdate(false);
//					updateNextFrame();
//				}
//				while (waitForAckResponse)
//				{
//					sendChannelMessageToTBS();
//					updateRCState();
//					CheckButtons();
//				}
//				forceDisarmEnabled = false;
//				waitForAckResponse = false;
				break;
			} //End of Force Disarm
			case 3:
			{
//				while ( (okButtonPressDuration < 3000) )
//				{
//					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
//					{
//						break;
//					}
//					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
//					{
//						func_fmt();
//						break;
//					}
//					sendChannelMessageToTBS();
//					updateRCState();
//					CheckButtons();
//					screenUpdate(false);
//					updateNextFrame();
//				}
				break;
			} // End of RC clear storage
			case 4:
			{
//				while ( (okButtonPressDuration < 3000) )
//				{
//					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
//					{
//						break;
//					}
//					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
//					{
//						formatSDEnabled = true;
//						waitForAckResponse = true;
//						break;
//					}
//					sendChannelMessageToTBS();
//					updateRCState();
//					CheckButtons();
//					screenUpdate(false);
//					updateNextFrame();
//				}
//				while (waitForAckResponse)
//				{
//					sendChannelMessageToTBS();
//					updateRCState();
//					CheckButtons();
//				}
//				formatSDEnabled = false;
//				waitForAckResponse = false;
				break;
			} //End of Clear SafeAir storage
			case 5:
			{
//				while ( (okButtonPressDuration < 3000) )
//				{
//					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 10) )
//					{
//						break;
//					}
//					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 10) && (popupDrawDirection == DOWN))
//					{
//						//Make BLE visible
//						break;
//					}
//					sendChannelMessageToTBS();
//					updateRCState();
//					CheckButtons();
//					screenUpdate(false);
//					updateNextFrame();
//				}
				break;
			} //End of make bluetooth visible
			case 6:
			{
//				while ( (okButtonPressDuration < 3000) )
//				{
//					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 10) )
//					{
//						break;
//					}
//					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 10) && (popupDrawDirection == DOWN))
//					{
//						//Make BLE Active
//						ee.bluetoothStatus = 1;
//						isBLEOn = true;
//						ee_save1();
//						break;
//					}
//					sendChannelMessageToTBS();
//					updateRCState();
//					CheckButtons();
//					screenUpdate(false);
//					updateNextFrame();
//				}
				break;
			} //End of make bluetooth Active
			case 7:
			{
//				while ( (okButtonPressDuration < 3000) )
//				{
//					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 10) )
//					{
//						break;
//					}
//					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 10) && (popupDrawDirection == DOWN))
//					{
////						isMSCMode = true;
////						MX_MSC_DEVICE_Init();
//						break;
//					}
//					sendChannelMessageToTBS();
//					updateRCState();
//					CheckButtons();
//					screenUpdate(false);
//					updateNextFrame();
//				}
				break;
			} //End of change to mass storage
			default:
			{
				break;
			}
		}
		memset(&popupToShow, 0, sizeof(popupToShow));
		screenClear();
		setFullDisplay();
		screenUpdate(false);
	}
}
