#include "fake_delay.hpp"

FakeDelay::FakeDelay() : delayTimeMs(0), amountOfCalls(0) {}

void FakeDelay::delayMs(uint32_t milliseconds) {
    delayTimeMs = milliseconds;
    amountOfCalls++;
}

auto FakeDelay::getAmountCals() const -> uint32_t { return amountOfCalls; }

auto FakeDelay::getDelayValue() const -> uint32_t { return delayTimeMs; }
