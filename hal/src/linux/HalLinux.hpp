#pragma once
#include "Hal.hpp"

class HalLinux : public Hal
{
public:
	explicit HalLinux(void);
	void delay(uint16_t ms);
	void toggle(uint16_t lednumber);
	uint8_t getMaxLedsOfStrip(void);
	void init(void);
};