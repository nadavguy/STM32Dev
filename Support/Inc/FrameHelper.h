/*
 * FrameHelper.h
 *
 *  Created on: May 5, 2021
 *      Author: gilad
 */

#ifndef INC_FRAMEHELPER_H_
#define INC_FRAMEHELPER_H_

#define BACKGROUND_HIGH_BYTE 0XFF
#define BACKGROUND_LOW_BYTE 0xFF
#define BACKGROUND 0xFFFF

#define SCREEN_WIDTH 128

#define STATUSBAR_HEIGHT 25

extern uint8_t numberOfDisplayedSafeAirIcons;

extern uint32_t LCDArraySize;

extern void createEmptyFrame(bool isMenuFrame);
extern void displayNextFrame(void);
extern void addImageToNextFrame(const unsigned char *image, uint8_t Height, uint8_t Width, uint8_t Xstart, uint8_t Ystart);
extern void addRectangleToFrame(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd, uint16_t Color);
extern void prepareNextFrame(void);

#endif /* INC_FRAMEHELPER_H_ */
