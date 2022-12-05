/**
 * @file RGBLED.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2022-12-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Emma.h"
#include "led_strip.h"


/**
 * @brief Init RGB LED
 * 
 * @param ledNum Empty to init with default pin
 */
void EMMA::RgbLedInit(uint32_t ledNum)
{
    /* Init strip led */
    led_strip_config_t led_gpio;
    led_gpio.max_leds = ledNum;
    led_gpio.strip_gpio_num = EMMA_PIN_RGB_LED;
    led_strip_rmt_config_t led_rmt;
    led_rmt.resolution_hz = 0;
    led_strip_new_rmt_device(&led_gpio, &led_rmt, &__RGB_LED_Handler);
}


/**
 * @brief Set LED into appoint color. RgbLedUpdate() needed, or use RgbLedShow() instead
 * 
 * @param index LED index, empty to set LED on board (led 0)
 * @param colorRGB RGB888  e.g. Blue:0x00FF00
 */
void EMMA::RgbLedSet(uint32_t index, uint32_t colorRGB)
{
    /* Get RGB individually from RGB888 */
    int red = (colorRGB >> 16) & 0xFF;
    int green = (colorRGB >> 8) & 0xFF;
    int blue = colorRGB & 0xFF;
    led_strip_set_pixel(__RGB_LED_Handler, index, red, green, blue);
}


/**
 * @brief Refresh RGB color data into led strip
 * 
 */
inline void EMMA::RgbLedUpdate()
{
    led_strip_refresh(__RGB_LED_Handler);
}


/**
 * @brief Set LED to show appoint color
 * 
 * @param index LED index, empty to set LED on board (led 0)
 * @param colorRGB RGB888  e.g. Blue:0x00FF00
 */
void EMMA::RgbLedShow(uint32_t index, int colorRGB)
{
    RgbLedSet(index, colorRGB);
    RgbLedUpdate();
}
