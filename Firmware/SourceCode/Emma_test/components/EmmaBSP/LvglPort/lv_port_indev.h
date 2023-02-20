
/**
 * @file lv_port_indev_templ.h
 *
 */

/*Copy this file as "lv_port_indev.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_INDEV_TEMPL_H
#define LV_PORT_INDEV_TEMPL_H



/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "../Encoder/Encoder.h"

/*********************
 *      DEFINES
 *********************/
#define ENCODER_REVERSE 0

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
// void lv_port_indev_init(void);
void lv_port_indev_init(ENCODER* pEncoder);

/**********************
 *      MACROS
 **********************/


#endif /*LV_PORT_INDEV_TEMPL_H*/

#endif /*Disable/Enable content*/
