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


class Encoder {
    private:
        int _pinA;
        int _pinB;
        bool _enPullup;
        bool _reverse;
        TaskHandle_t _ecTaskHandle;
        unsigned int _ecTaskPriority;
    public:
        Encoder();
        ~Encoder();
        void SetPin(int pinA, int pinB);
        void Init();
        void Init(int pinA, int pinB) { SetPin(pinA, pinB); Init(); }
        void Uninit();
        int GetDirection();
        int GetPosition();
};





