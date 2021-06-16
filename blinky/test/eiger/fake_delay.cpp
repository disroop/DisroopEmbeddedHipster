#include "fake_delay.hpp"

FakeDelay::FakeDelay() : delayTimeMs(0), amountOfCalls(0){};

void FakeDelay::delayMs(uint32_t milliseconds) {
    delayTimeMs = milliseconds;
    amountOfCalls++;
}

uint32_t FakeDelay::getAmountCals() { return amountOfCalls; }

uint32_t FakeDelay::getDelayValue() { return delayTimeMs; }