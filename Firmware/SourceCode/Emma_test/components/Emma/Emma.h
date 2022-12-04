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


/**
 * @brief Configs
 * 
 */
#define BSP_VERISON             "v1.0"
#define LCD_PRINT_INIT_INFO     1







/**
 * @brief Emma class
 * 
 */
class Emma {
    private:
        
    public:
        const string EmmaLogo = R"(
 ______  __    __  __    __  ______
/\  ___\/\ "-./  \/\ "-./  \/\  __ \
\ \  __\\ \ \-./\ \ \ \-./\ \ \  __ \
 \ \_____\ \_\ \ \_\ \_\ \ \_\ \_\ \_\
  \/_____/\/_/  \/_/\/_/  \/_/\/_/\/_/

)";
        LGFX_Emma lcd;

        /* Fuctions */
        void Init(bool enLcd = true, bool enEncoder = true, bool enLedRGB = true, bool enBuzzer = true);
        void PrintBoardInfos();
        string Cowsay(string whatCowSay, int ANSIcolor);
        string Cowsay(string whatCowSay) {return Cowsay(whatCowSay, 0);}
};

