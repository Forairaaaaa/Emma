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
#include "freertos/semphr.h"
#include "driver/gpio.h"


/* Use "Button" to handle encoder's gpio */
static Button _EcA;
static Button _EcB;
/* Semaphore for shared data */
static SemaphoreHandle_t _SemaphoreMutex;
/* Values of encoder */
static int _EncoderPositoin;
static int _EncoderDirection;
static int _Ret;



/**
 * @brief Encoder task
 * 
 * @param param 
 */
static void EncoderTask(void* param)
{
    _EncoderPositoin = 0;
    _EncoderDirection = 0;
    while (1) {
        xSemaphoreTake(_SemaphoreMutex, portMAX_DELAY);
        /* If moved */
        if (_EcA.pressed()) {
            _EncoderDirection = (_EcB.read() ? 1 : -1);
            _EncoderPositoin += _EncoderDirection;
        }
        else {
            _EncoderDirection = 0;
        }
        xSemaphoreGive(_SemaphoreMutex);
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}


/**
 * @brief Construct a new Encoder:: Encoder object
 * 
 */
ENCODER::ENCODER()
{
    _pinA = -1;
    _pinB = -1;
    _pinBTN = -1;
    _ecTaskHandle = NULL;
    _ecTaskPriority = 1;
    _oldPosition = 0;
}


/**
 * @brief Destroy the Encoder:: Encoder object
 * 
 */
ENCODER::~ENCODER()
{
    Uninit();
}


/**
 * @brief Init encoder, Should call SetPin() first
 * 
 * @param enPullup 
 */
void ENCODER::Init(int pinA, int pinB, int pinBTN)
{   
    _pinA = pinA;
    _pinB = pinB;
    _pinBTN = pinBTN;

    /* If no pin config */
    if ((_pinA <= 0) || (_pinB <= 0) || (_pinBTN <= 0))
        return;

    /* Init A, B by using "Button" */
    _EcA.setPin(_pinA);
    _EcA.setDebounce(5);
    _EcA.begin();
    _EcB.setPin(_pinB);
    _EcB.setDebounce(5);
    _EcB.begin();
    /* Init button */
    Btn.setPin(_pinBTN);
    Btn.begin();

    /* Create encoder task */
    _SemaphoreMutex = xSemaphoreCreateMutex();
    xTaskCreate(EncoderTask, "Encoder", 1024, NULL, _ecTaskPriority, &_ecTaskHandle);
}


/**
 * @brief Uinit encoder
 * 
 */
void ENCODER::Uninit()
{
    vTaskDelete(_ecTaskHandle);
    gpio_reset_pin((gpio_num_t)_pinA);
    gpio_reset_pin((gpio_num_t)_pinB);
    gpio_reset_pin((gpio_num_t)_pinBTN);
}


/**
 * @brief Get encoder direction, mainly for internal use, high frequency call needed
 * 
 * @return int 114514:timeout
 */
int ENCODER::GetDirection()
{
    _Ret = 114514;
    if (xSemaphoreTake(_SemaphoreMutex, (TickType_t)100) == pdTRUE) {
        _Ret = _EncoderDirection;
        xSemaphoreGive(_SemaphoreMutex);
    }
    return _Ret;
}


/**
 * @brief Get encoder position
 * 
 * @return int 114514:timeout
 */
int ENCODER::GetPosition()
{
    _Ret = 114514;
    if (xSemaphoreTake(_SemaphoreMutex, (TickType_t)100) == pdTRUE) {
        _Ret = _EncoderPositoin;
        xSemaphoreGive(_SemaphoreMutex);
    }
    return _Ret;
}


/**
 * @brief Reset encoder position to 0
 * 
 */
void ENCODER::ResetPosition()
{
    if (xSemaphoreTake(_SemaphoreMutex, (TickType_t)100) == pdTRUE) {
        _oldPosition = 0;
        _EncoderPositoin = 0;
        xSemaphoreGive(_SemaphoreMutex);
    }
}


/**
 * @brief Is encider moved 
 * 
 * @return true 
 * @return false 
 */
bool ENCODER::Moved()
{
    if (GetPosition() == _oldPosition) {
        return false;
    }
    else {
        _oldPosition = GetPosition();
        return true;
    }
}
