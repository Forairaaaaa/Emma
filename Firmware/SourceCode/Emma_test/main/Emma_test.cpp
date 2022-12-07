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






static void LedTask(void* param);


extern "C" void app_main(void)
{
    Emma.Init();

    printf(Emma.Cowsay("Meow~~").c_str());
    Emma.lcd.printf(Emma.Cowsay("Meow~~").c_str());

    xTaskCreate(LedTask, "RGB-LED", 1024, NULL, 1, NULL);

    Emma.BuzzerTest();





    ec.Init(EMMA_PIN_EC_A, EMMA_PIN_EC_B);
    while (1) {
        printf("%d\n", ec.GetDirection());
        EmmaDelay(100);
    }




    


    

    while (1) {
        EmmaDelay(5000);
    }
}



static void LedTask(void* param)
{
    uint8_t brightness = 0;
    uint8_t color = 0;
    while (1) {
        Emma.RgbLedShow((brightness++) << color);
        if (brightness == 70) {
            brightness = 0;
            color += 8;
            if (color > 16)
                color = 0;
        }
        EmmaDelay(40);
    }
    vTaskDelete(NULL);
}
