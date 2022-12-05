/**
 * @file Emma_test.cpp
 * @author Forairaaaaa
 * @brief App entrance
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Emma.h"
#include "led_strip.h"

EMMA Emma;



void setup(void);

extern "C" void app_main(void)
{
    Emma.Init();

    printf(Emma.Cowsay("Meow~~").c_str());
    Emma.lcd.printf(Emma.Cowsay("Meow~~").c_str());


    Emma.BuzzerTest();
    

    // led_strip_config_t led_gpio;
    // led_gpio.max_leds = 1;
    // led_gpio.strip_gpio_num = EMMA_PIN_RGB_LED;
    // led_strip_rmt_config_t led_rmt;
    // led_rmt.resolution_hz = 0;
    // led_strip_handle_t rgb_led;

    // led_strip_new_rmt_device(&led_gpio, &led_rmt, &rgb_led);


    // while (1) {
    //     led_strip_set_pixel(rgb_led, 0, 255, 0, 0);
    //     led_strip_refresh(rgb_led);
    //     printf("%s", emma.Cowsay("R", ANSI_RED).c_str());
    //     EmmaDelay(1000);
    //     led_strip_set_pixel(rgb_led, 0, 0, 255, 0);
    //     led_strip_refresh(rgb_led);
    //     printf("%s", emma.Cowsay("G", ANSI_GREEN).c_str());
    //     EmmaDelay(1000);
    //     led_strip_set_pixel(rgb_led, 0, 0, 0, 255);
    //     led_strip_refresh(rgb_led);
    //     printf("%s", emma.Cowsay("B", ANSI_BLUE).c_str());
    //     EmmaDelay(1000);
    // }


    while (1) {
        Emma.RgbLedShow(0xFF0000);
        printf("%s", Emma.Cowsay("R", ANSI_RED).c_str());
        EmmaDelay(1000);
        Emma.RgbLedShow(0x00FF00);
        printf("%s", Emma.Cowsay("G", ANSI_GREEN).c_str());
        EmmaDelay(1000);
        Emma.RgbLedShow(0x0000FF);
        printf("%s", Emma.Cowsay("B", ANSI_BLUE).c_str());
        EmmaDelay(1000);
    }

    

    while (1) {
        EmmaDelay(5000);
    }
}

