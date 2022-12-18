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


#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "demos/lv_demos.h"
#include "examples/lv_examples.h"

using namespace std;


extern "C" void app_main(void)
{
    Emma.Init();

    printf(Emma.Cowsay("Meow~~").c_str());
    Emma.Lcd.printf(Emma.Cowsay("Meow~~").c_str());
    Emma.BuzzerTest();


    delay(1000);
    lv_init();
    lv_port_disp_init(&Emma.Lcd);
    lv_port_indev_init(&Emma.Encoder);
    

    lv_demo_keypad_encoder();
    // lv_demo_benchmark();
    // lv_demo_widgets();
    // lv_demo_stress();

    // lv_example_btn_3();
    // lv_example_led_1();
    // lv_example_roller_3();
    // lv_example_meter_2();
    // lv_example_chart_5();
    // lv_example_colorwheel_1();
    // lv_example_arc_1();



    while (1) {
        lv_timer_handler();
        delay(5);
    }
    



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


