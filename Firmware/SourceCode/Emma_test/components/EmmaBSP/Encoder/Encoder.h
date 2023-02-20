/**
 * @file Encoder.h
 * @author Forairaaaaa 
 * @brief Encoder driver by using GPIO lib
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Button/Button.h"


class ENCODER {
    private:
        int _pinA;
        int _pinB;
        int _pinBTN;
        TaskHandle_t _ecTaskHandle;
        unsigned int _ecTaskPriority;
        int _oldPosition;
    public:
        /* Button */
        Button Btn;
        /* Public methods */
        ENCODER();
        ~ENCODER();
        void Init(int pinA = -1, int pinB = -1, int pinBTN = -1);
        void Uninit();
        int GetDirection();
        int GetPosition();
        void ResetPosition();
        bool Moved();
};

