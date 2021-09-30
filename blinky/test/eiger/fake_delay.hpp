#pragma once
#include <cinttypes>

class FakeDelay {
   public:
    FakeDelay();
    void delayMs(uint32_t milliseconds);
    auto getAmountCals() const -> uint32_t;
    auto getDelayValue() const -> uint32_t;

   private:
    uint32_t delayTimeMs;
    uint32_t amountOfCalls;
};
