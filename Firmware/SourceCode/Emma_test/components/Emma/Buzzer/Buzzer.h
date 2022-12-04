/**
 * @file Buzzer.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "Emma.h"


void setToneChannel(uint8_t channel = 0);
void tone(uint8_t _pin, unsigned int frequency, unsigned long duration = 0);
void noTone(uint8_t _pin);



