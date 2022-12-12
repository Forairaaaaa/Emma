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

// #include "Encoder.h"
// ENCODER ec;


extern "C" void app_main(void)
{
    Emma.Init();

    printf(Emma.Cowsay("Meow~~").c_str());
    Emma.Lcd.printf(Emma.Cowsay("Meow~~").c_str());
    Emma.BuzzerTest();

    

    // ec.Init(EMMA_PIN_EC_A, EMMA_PIN_EC_B, EMMA_PIN_EC_BTN);
    while (1) {

        if (Emma.Encoder.Btn.pressed()) {
            Emma.Encoder.ResetPosition();
            cout << Emma.Encoder.GetPosition() << endl;
        }

        if (Emma.Encoder.Moved())
            cout << Emma.Encoder.GetPosition() << endl;



        delay(10);
    }


    while (1) {
        delay(5000);
    }
}


