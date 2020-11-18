#include "HalNrf.hpp" 

extern "C" {
    #include "nrf_delay.h"
    #include "boards.h"
}

//TODO: Refactor
void HalNrf::init(void){
    bsp_board_init(BSP_INIT_LEDS);
}

void HalNrf::delay(uint16_t ms){
    nrf_delay_ms(500);
}

void HalNrf::toggle(uint16_t lednumber){
    bsp_board_led_invert(lednumber);
}

uint8_t HalNrf::getMaxLedsOfStrip(void){
    return LEDS_NUMBER;
}