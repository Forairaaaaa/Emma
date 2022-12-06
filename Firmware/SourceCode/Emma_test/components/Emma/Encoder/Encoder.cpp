/**
 * @file Encoder.cpp
 * @author Forairaaaaa 
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Encoder.h"
#include "driver/gpio.h"


/* Struct to pass pin config to task */
struct EncoderPins_t
{
    int pinA;
    int pinB;
};
static EncoderPins_t EncoderPins;

/* Status of encoder */
static int EncoderStatus = 0;



/**
 * @brief Encoder task
 * 
 * @param param 
 */
static void EncoderTask(void* param)
{
    /* Get encoder pin config */
    EncoderPins_t* encoderPins = (EncoderPins_t*)param;

    while (1) {


    }
    vTaskDelete(NULL);
}


/**
 * @brief Init encoder, Should call SetPin() first
 * 
 * @param enPullup 
 */
void Encoder::Init()
{   
    /* If no pin config */
    if ((_pinA <= 0) || (_pinB <= 0))
        return;

    /* GPIO setup */
    gpio_set_direction((gpio_num_t)_pinA, GPIO_MODE_INPUT);
    gpio_set_direction((gpio_num_t)_pinB, GPIO_MODE_INPUT);
    if (_enPullup) {
        gpio_pullup_en((gpio_num_t)_pinA);
        gpio_pullup_en((gpio_num_t)_pinB);
    }

    /* Create encoder task */
    EncoderPins.pinA = _pinA;
    EncoderPins.pinB = _pinB;
    xTaskCreate(EncoderTask, "Encoder", 1024, (void*)&EncoderPins, _ecTaskPriority, &_ecTaskHandle);
}


/**
 * @brief Uinit encoder
 * 
 */
void Encoder::Uninit()
{
    vTaskDelete(_ecTaskHandle);
    gpio_reset_pin((gpio_num_t)_pinA);
    gpio_reset_pin((gpio_num_t)_pinB);
}


/**
 * @brief Config encoder pins
 * 
 * @param pinA 
 * @param pinB 
 */
void Encoder::SetPin(int pinA, int pinB)
{
    _pinA = pinA;
    _pinB = pinB;
}


/**
 * @brief Return status of encoder
 * 
 * @return int 
 */
int Encoder::Status()
{
    /* if lock ... */
    return EncoderStatus;
}




/**
 * @brief Construct a new Encoder:: Encoder object
 * 
 */
Encoder::Encoder()
{
    _pinA = -1;
    _pinB = -1;
    _enPullup = true;
    _ecTaskHandle = NULL;
    _ecTaskPriority = 1;
}


/**
 * @brief Destroy the Encoder:: Encoder object
 * 
 */
Encoder::~Encoder()
{
    Uninit();
}
