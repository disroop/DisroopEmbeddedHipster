#pragma once
#include <inttypes.h>

class Hal
{
public:
	virtual void delay(uint16_t ms) = 0;
	virtual void toggle(uint16_t lednumber) = 0;
	virtual uint8_t getMaxLedsOfStrip(void) = 0;
};