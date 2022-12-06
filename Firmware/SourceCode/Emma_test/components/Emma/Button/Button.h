/**
 * @file Button.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "iot_button.h"


/**
 * @brief Pack iot_button lib to a class
 * 
 */
class Button {
    private:
        button_handle_t _buttonHandle;
    public:
        /**
         * @brief Construct a new Button object
         * 
         * @param pin Button pin
         * @param activeLevel Active level
         */
        Button(int pin, uint8_t activeLevel = 0)
        {
            button_config_t ButtonCfg = {
                .type = BUTTON_TYPE_GPIO,
                .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS,
                .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS,
                .gpio_button_config = {
                    .gpio_num = pin,
                    .active_level = activeLevel,
                },
            };
            _buttonHandle = iot_button_create(&ButtonCfg);
        }


        /**
         * @brief Register the button event callback function
         * 
         * @param event 
         * @param cb 
         * @param usr_data 
         */
        inline void RegisterCb(button_event_t event, button_cb_t cb, void *usr_data)
        {
            iot_button_register_cb(_buttonHandle, event, cb, usr_data);
        }


        /**
         * @brief Get button event
         * 
         * @return button_event_t 
         */
        inline button_event_t GetEvent()
        {
            return iot_button_get_event(_buttonHandle);
        }
};

