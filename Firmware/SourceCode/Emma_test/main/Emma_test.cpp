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



void setup(void);

extern "C" void app_main(void)
{
    emma.Init();

    printf(emma.Cowsay("Meow~~").c_str());
    emma.lcd.printf(emma.Cowsay("Meow~~").c_str());


    emma.BuzzerTest();
    





    

    while (1) {
        EmmaDelay(5000);
    }
}

