
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

extern TIM_HandleTypeDef htim6;

void TIM6_DAC_IRQHandler(void) { HAL_TIM_IRQHandler(&htim6); }
