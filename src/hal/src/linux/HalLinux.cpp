#include "HalNrf.hpp" 
#include <stdio>
#include <string>

HalLinux::HalLinux(void){
    std::cout<<"Init"<<std::endl;
}

void HalLinux::delay(uint16_t ms){
    std::cout<<"Delay - ms: "<<std::to_string(ms)<<std::endl;
}

void HalLinux::toggle(uint16_t lednumber){
    std::cout<<"Invert LED: Number"<<std::to_string(lednumber)<<std::endl;
}

uint8_t HalLinux::getMaxLedsOfStrip(void){
    return 4;
}