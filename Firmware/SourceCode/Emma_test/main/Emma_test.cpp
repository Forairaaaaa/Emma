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

EMMA Emma;



void setup(void);

extern "C" void app_main(void)
{
    Emma.Init();

    printf(Emma.Cowsay("Meow~~").c_str());
    Emma.lcd.printf(Emma.Cowsay("Meow~~").c_str());


    Emma.BuzzerTest();

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

