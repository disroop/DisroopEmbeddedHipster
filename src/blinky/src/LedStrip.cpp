#include "LedStrip.hpp"
#include "Hal.hpp"
#include <exception>

LedStrip::LedStrip(std::unique_ptr<Hal> hal) : hal(std::move(hal)) {}

void LedStrip::on(const Led &led)
{
}

void LedStrip::off(const Led &led)
{
}

uint16_t LedStrip::convert(const Cycle &cycle)
{
    uint16_t cycleConverted = 0;
    switch (cycle)
    {
    case Cycle::Cycle1:
        cycleConverted = 1;
        break;
    case Cycle::Cycle10:
        cycleConverted = 10;
        break;
    case Cycle::Cycle100:
        cycleConverted = 100;
        break;
    case Cycle::Cycle1000:
        cycleConverted = 1000;
        break;
    default:
        //TODO CREATE ERROR
        break;
    }
    return cycleConverted;
}
void LedStrip::runLedPattern(const Cycle &cycle)
{
    uint16_t runs = convert(cycle);
    uint8_t numberOfLeds = hal.get()->getMaxLedsOfStrip();
    for (size_t i = 0; i < runs; i++)
    {
        for (int i = 0; i < numberOfLeds; i++)
        {
            hal.get()->toggle(i);
            hal.get()->delay(500);
        }
    }
}