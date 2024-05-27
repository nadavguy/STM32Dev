/**
 * @file tft.h
 *
 */

#ifndef DISP_H
#define DISP_H

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include "../../lvgl/src/misc/lv_color.h"
#include "../../lvgl/src/misc/lv_area.h"

/*********************
 *      DEFINES
 *********************/
#define TFT_HOR_RES 160
#define TFT_VER_RES 128

/**********************
 *      TYPEDEFS
 **********************/
#define LCD_LAYER_0_ADDRESS                 0xD0000000U
/**********************
 * GLOBAL PROTOTYPES
 **********************/
void tft_init(void);

/**********************
 *      MACROS
 **********************/

#endif
