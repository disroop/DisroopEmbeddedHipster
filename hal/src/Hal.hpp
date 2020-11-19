#pragma once
#include <inttypes.h>

class Hal
{
public:
	//Hal(Hal const &other) = default;
	//Hal &operator=(Hal const &other) = default;
	//Hal(Hal &&other) = default;
	//Hal &operator=(Hal &&other) = default;
	~Hal() = default;
	virtual void delay(uint16_t ms) = 0;
	virtual void toggle(uint16_t lednumber) = 0;
	virtual void init(void) = 0;
	virtual uint8_t getMaxLedsOfStrip(void) = 0;
};