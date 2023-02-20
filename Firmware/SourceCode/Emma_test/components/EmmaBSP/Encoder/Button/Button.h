/*
	Button - a small library for Arduino to handle button debouncing
	
	MIT licensed.
*/

#ifndef Button_h
#define Button_h
// #include "Arduino.h"
#include <stdio.h>

class Button
{
	public:
		Button(uint8_t pin = 0, uint16_t debounce_ms = 100);
        void setPin(uint8_t pin);
        void setDebounce(uint16_t ms);
		void begin();
		bool read();
		bool toggled();
		bool pressed();
		bool released();
		bool has_changed();
		
		const static bool PRESSED = 0;
		const static bool RELEASED = 1;
	
	private:
		uint8_t  _pin;
		uint16_t _delay;
		bool     _state;
		uint32_t _ignore_until;
		bool     _has_changed;
};

#endif