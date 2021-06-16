#pragma once
#include <inttypes.h>

class FakeDelay {
   public:
    explicit FakeDelay();
    void delayMs(uint32_t milliseconds);
    uint32_t getAmountCals();
    uint32_t getDelayValue();

   private:
    uint32_t delayTimeMs;
    uint32_t amountOfCalls;
};