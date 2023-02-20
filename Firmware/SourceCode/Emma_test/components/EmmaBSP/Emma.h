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
#include <iostream>
#include <string>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Lcd/LovyanGFX_Emma.hpp"
#include "Encoder/Encoder.h"


/* Configs */
#define BSP_VERISON             "v2.1"
/* GPIO map */
#define EMMA_PIN_BUZZER         46
#define EMMA_PIN_RGB_LED        1
#define EMMA_PIN_EC_BTN         2
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


/**
 * @brief Emma BSP class 
 * 
 */
class EMMA {
    private:
    
    public:
        const std::string Logo = R"(
 ______  __    __  __    __  ______
/\  ___\/\ "-./  \/\ "-./  \/\  __ \
\ \  __\\ \ \-./\ \ \ \-./\ \ \  __ \
 \ \_____\ \_\ \ \_\ \_\ \ \_\ \_\ \_\
  \/_____/\/_/  \/_/\/_/  \/_/\/_/\/_/
)";
        const std::string Cow = R"(
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
)";

        /* LovyanGFX */
        LGFX_Emma Lcd;
        /* Encoder */
        ENCODER Encoder;

        /* Public methods */
        void Init(bool enLcd = true, bool enEncoder = true, bool enLedRGB = true, bool enBuzzer = true);
        void PrintBoardInfo(bool printOnLcd = false);
        /* Cowsay */
        std::string Cowsay(std::string whatCowSay, int ANSIcolor = 0);
        /* Buzzer */
        inline void StartTone(unsigned int frequency, unsigned long duration = 0);
        inline void StopTone();
        void BuzzerTest();

};

/* Pack like Arduino */
void delay(uint32_t ms);
