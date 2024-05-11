/*
 * LogAgent.h
 *
 *  Created on: Apr 26, 2024
 *      Author: user
 */

#ifndef INC_LOGAGENT_H_
#define INC_LOGAGENT_H_

#include "time.h"

#define GENERALBUFFERSIZE 1024
#define TERMINALBUFFERSIZE 512

typedef enum colorsForDisplay {GREEN, BLUE, WHITE, RED, BLACK, MAGENTA, COLOROVERRIDE, ORANGE, NOCOLOR} tColorsForDisplay; //Green - if tested True, BLUE - info, RED - Error, MAGENTA - Debug

//extern char terminalBuffer[TERMINALBUFFERSIZE];

extern void logData(bool printToScreen, bool screenOnly, tColorsForDisplay selectedColor);
extern char *resolvePointerToLogsBuffer(void);

#endif /* INC_LOGAGENT_H_ */
