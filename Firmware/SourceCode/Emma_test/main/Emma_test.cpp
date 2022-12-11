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

#include "Encoder.h"
Encoder ec;


extern "C" void app_main(void)
{
    Emma.Init();

    printf(Emma.Cowsay("Meow~~").c_str());
    Emma.Lcd.printf(Emma.Cowsay("Meow~~").c_str());
    Emma.BuzzerTest();

    

    ec.Init(EMMA_PIN_EC_A, EMMA_PIN_EC_B, EMMA_PIN_EC_BTN);
    while (1) {
        cout << ec.Btn.pressed() << endl;
        delay(100);
    }


    while (1) {
        delay(5000);
    }
}


