#pragma once
#include "Hal.hpp"

class HalNrf : public Hal
{
public:
	void delay(uint16_t ms);
	void toggle(uint16_t lednumber);
	uint8_t getMaxLedsOfStrip(void);
	void init(void);
};