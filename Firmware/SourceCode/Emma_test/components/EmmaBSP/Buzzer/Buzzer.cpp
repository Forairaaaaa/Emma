/**
 * @file Buzzer.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Buzzer.h"


inline void EMMA::StartTone(unsigned int frequency, unsigned long duration)
{
    tone(EMMA_PIN_BUZZER, frequency, duration);
}

inline void EMMA::StopTone()
{
    noTone(EMMA_PIN_BUZZER);
}

/**
 * @brief Simple buzzer test
 * 
 */
void EMMA::BuzzerTest()
{
    printf(Cowsay("Beep Test :)", 34).c_str());
    /* Play tones */
    int f;
    for (f = 0; f < 2; f++) {
        StartTone(1000);
        delay(50);
        StopTone();
        delay(20);
    }
    delay(400);
    for (f = 100; f < 3000; f += 100) {
        StartTone(f);
        delay(20);
        StopTone();
    }
    for (f = 3000; f > 100; f -= 100) {
        StartTone(f);
        delay(20);
        StopTone();
    }
}

