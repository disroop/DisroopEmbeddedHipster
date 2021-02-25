#include <stdbool.h>
#include <stdint.h>
#include "LedStrip.hpp"
#include "Hal.hpp"
#include "HalNrf.hpp"
#include <memory>
int main(void)
{
    std::unique_ptr<Hal> hal = std::unique_ptr<HalNrf>(new HalNrf());
    LedStrip ledStrip(std::move(hal));
    ledStrip.runLedPattern(LedStrip::Cycle::Cycle1000);
}
