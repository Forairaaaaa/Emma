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

Emma emma;

extern "C" void app_main(void)
{
    emma.Init();

    printf(emma.Cowsay("Hello Mother F'er~").c_str());
    emma.lcd.printf(emma.Cowsay("Hello Mother F'er~").c_str());
    

    while (1) {
        EmmaDelay(5000);
    }
}
