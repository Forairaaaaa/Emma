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

// #include "iot_button.h"
#include "esp_log.h"
#define TAG "button"
#include "Button.h"



// static void LedTask(void* param)
// {
//     unsigned int 
//     while (1) {
        
//         Emma.RgbLedShow()
//     }
//     vTaskDelete(NULL);
// }


extern "C" void app_main(void)
{
    Emma.Init();

    printf(Emma.Cowsay("Meow~~").c_str());
    Emma.lcd.printf(Emma.Cowsay("Meow~~").c_str());



    Emma.BuzzerTest();



    


    

    while (1) {
        EmmaDelay(5000);
    }
}

