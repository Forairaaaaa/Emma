/**
 * @file Emma.h
 * @author Forairaaaaa
 * @brief Emma BSP
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define EmmaDelay(ms) vTaskDelay(ms / portTICK_PERIOD_MS)

#include <iostream>
#include <string>
using namespace std;

#include <LovyanGFX_Emma.hpp>
#include "led_strip.h"



/* Configs */
#define BSP_VERISON             "v1.0"
#define LCD_PRINT_INIT_INFO     1
/* GPIO map */
#define EMMA_PIN_BUZZER         46
#define EMMA_PIN_RGB_LED        1
#define EMMA_PIN_EC_BT          2
#define EMMA_PIN_EC_A           18
#define EMMA_PIN_EC_B           3
#define EMMA_PIN_LCD_RST        17
#define EMMA_PIN_LCD_SDA        15
#define EMMA_PIN_LCD_SCL        13
#define EMMA_PIN_LCD_CS         21
#define EMMA_PIN_LCD_DC         16
#define EMMA_PIN_LCD_BL         14
/* ANSI colors */
#define ANSI_BLACK              30
#define ANSI_RED                31
#define ANSI_GREEN              32
#define ANSI_YELLOW             33
#define ANSI_BLUE               34
#define ANSI_MAGENTA            35
#define ANSI_CYAN               36
#define ANSI_WHITE              37



class EMMA {
    private:
        led_strip_handle_t _RGB_LED_Handler;
    public:
        const string EmmaLogo = R"(
 ______  __    __  __    __  ______
/\  ___\/\ "-./  \/\ "-./  \/\  __ \
\ \  __\\ \ \-./\ \ \ \-./\ \ \  __ \
 \ \_____\ \_\ \ \_\ \_\ \ \_\ \_\ \_\
  \/_____/\/_/  \/_/\/_/  \/_/\/_/\/_/

)";
        LGFX_Emma lcd;

        /**
         * Functions
         */
        void Init(bool enLcd = true, bool enEncoder = true, bool enLedRGB = true, bool enBuzzer = true);
        void PrintBoardInfos();
        /* Cowsay */
        string Cowsay(string whatCowSay, int ANSIcolor);
        string Cowsay(string whatCowSay) { return Cowsay(whatCowSay, 0); }
        /* Buzzer */
        inline void StartTone(unsigned int frequency, unsigned long duration = 0);
        inline void StopTone();
        void BuzzerTest();
        /* RGB LED */
        void RgbLedInit(uint32_t ledNum = 1);
        void RgbLedSet(uint32_t index, uint32_t colorRGB);
        void RgbLedSet(int colorRGB) { RgbLedSet(0, colorRGB); };
        inline void RgbLedUpdate();
        void RgbLedShow(uint32_t index, int colorRGB);
        void RgbLedShow(int colorRGB) { RgbLedShow(0, colorRGB); };
};
