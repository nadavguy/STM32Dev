/*
 * LogAgent.c
 *
 *  Created on: Apr 26, 2024
 *      Author: user
 */


#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "time.h"
#include "LogAgent.h"

char *pointerToBuffer;

char terminalBuffer[TERMINALBUFFERSIZE] = {0};

void logData(bool printToScreen, bool screenOnly, tColorsForDisplay selectedColor)
{
	static char localBuffer[GENERALBUFFERSIZE] = {0};
	static char screen_buffer[GENERALBUFFERSIZE] = {0};

	memset(localBuffer, 0, GENERALBUFFERSIZE);
	memset(screen_buffer, 0, GENERALBUFFERSIZE);

	uint16_t localStringLength = 0;

	localStringLength = fmin(sizeof(terminalBuffer) * 1.0, strlen(terminalBuffer) * 1.0);
	memcpy(localBuffer, terminalBuffer, localStringLength);

	if (strlen(localBuffer) > 0)
	{
		if (printToScreen)
		{
			uint16_t localLengthToPrint = fmin((float)GENERALBUFFERSIZE, strlen(localBuffer));
			memset(screen_buffer, 0, GENERALBUFFERSIZE);
			if (selectedColor == WHITE)
			{
				strcat(screen_buffer, "\033[39m");
				memcpy(&screen_buffer[5], localBuffer, localLengthToPrint);
			}
			else if (selectedColor == MAGENTA)
			{
				strcat(screen_buffer, "\033[35m");
				memcpy(&screen_buffer[5], localBuffer, localLengthToPrint);
			}
			else if (selectedColor == BLUE)
			{
				strcat(screen_buffer, "\033[34m");
				memcpy(&screen_buffer[5], localBuffer, localLengthToPrint);
			}
			else if (selectedColor == ORANGE)
			{
				strcat(screen_buffer, "\033[33m");
				memcpy(&screen_buffer[5], localBuffer, localLengthToPrint);
			}
			else if (selectedColor == GREEN)
			{
				strcat(screen_buffer, "\033[32m");
				memcpy(&screen_buffer[5], localBuffer, localLengthToPrint);
			}
			else if (selectedColor == RED)
			{
				strcat(screen_buffer, "\033[31m");
				memcpy(&screen_buffer[5], localBuffer, localLengthToPrint);
			}
			else if (selectedColor == BLACK)
			{
				strcat(screen_buffer, "\033[30m");
				memcpy(&screen_buffer[5], localBuffer, localLengthToPrint);
			}
			else if (selectedColor == COLOROVERRIDE)
			{
				strcat(screen_buffer, "");
				memcpy(screen_buffer, localBuffer, localLengthToPrint);
			}
			else
			{
				memcpy(screen_buffer, localBuffer, localLengthToPrint);
			}

			if ( (selectedColor != NOCOLOR) && (localLengthToPrint < GENERALBUFFERSIZE - 5) )
			{
				strcat(screen_buffer, "\033[39m");
				localLengthToPrint = fmin((float)GENERALBUFFERSIZE, strlen(screen_buffer));
//				HAL_UART_Transmit(&terminalUART, (uint8_t *)screen_buffer, localLengthToPrint, 150);
			}
			else if ((selectedColor != NOCOLOR) && (localLengthToPrint >= 4090))
			{
//				HAL_UART_Transmit(&terminalUART, (uint8_t *)screen_buffer, localLengthToPrint, 150);
//				HAL_UART_Transmit(&terminalUART, (uint8_t *)"\033[39m", 6, 150);
			}
			else
			{
//				HAL_UART_Transmit(&terminalUART, (uint8_t *)screen_buffer, localLengthToPrint, 150);
			}


			if (screenOnly)
			{
				memset(localBuffer, 0, sizeof(localBuffer));
				return;
			}
		}
		memset(localBuffer, 0, sizeof(localBuffer));
	}
	else
	{
//		if (ee.DebugLevel == 18)
//		{
//			//			HAL_UART_Transmit(&terminalUART, (uint8_t *)"Buffer size is 0\r\n", 18, 150);
//		}
	}
//	if (ee.DebugLevel == 2)
//	{
//		//	    HAL_UART_Transmit(&terminalUART, (uint8_t *)"logData Rel Sem - 2\r\n", 21, 150);
//	}

}

char *resolvePointerToLogsBuffer(void)
{
	if (true)
	{
		return ((char *)terminalBuffer);
	}
	else
	{
		//TODO: LED Indication?
//		Error_Handler();
	}
	return ((char *)terminalBuffer);
}
