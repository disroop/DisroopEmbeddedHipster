#include "LedStrip.hpp"
#include "Hal.hpp"

LedStrip::LedStrip(std::unique_ptr<Hal> hal): hal(std::move(hal)){}

void LedStrip::on(const Led& led){

}

void LedStrip::off(const Led& led){

}


void LedStrip::runLedPattern(const Cycle& cycle){
    
    uint8_t numberOfLeds = hal.get()->getMaxLedsOfStrip();
    for (int i = 0; i < numberOfLeds; i++)
    {
        hal.get()->toggle(i);
        hal.get()->delay(500);
    }
}