#pragma once
#include "Hal.hpp"
#include <memory>
class LedStrip
{
public:
    explicit LedStrip(std::unique_ptr<Hal> hal);
    enum class Led
    {
        LED1,
        LED2,
        LED3,
        LED4
    };
    enum class Cycle
    {
        Cycle1,
        Cycle10,
        Cycle100,
        Cycle1000
    };
    void on(const Led &led);
    void off(const Led &led);
    void runLedPattern(const Cycle &cycle);

private:
    std::unique_ptr<Hal> hal;
    uint16_t convert(const Cycle &cycle);
};
