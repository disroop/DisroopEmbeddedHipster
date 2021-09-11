#include "B-L475E-IOT01/stm32l475e_iot01_gyro.h"
#include "SystemClock.h"
#include "blinky/blinky.h"
#include "eiger/scheduler.h"
#include "indication/indication.h"
#include "movement/movement.h"

void platform_init() {
    HAL_Init();
    SystemClock_Config();
    BSP_LED_Init(LED_GREEN);
    BSP_GYRO_Init();
    BSP_GYRO_LowPower(0);
}

void setup() {
    platform_init();
    indication indicator =
        indication_create(LED_GREEN, BSP_LED_On, BSP_LED_Off);
    uint8_t base_ms = 100;
    timer timerIndicationOn = eiger_timer_create(base_ms);
    movement hw_movement = movement_create(BSP_GYRO_GetXYZ);
    blinky_init(timerIndicationOn, indicator, hw_movement);
    eiger_scheduler_config_time(HAL_Delay);
    eiger_scheduler_add_task(blinky_update, base_ms);
    eiger_scheduler_add_task(movement_run, 20);
}

void infinite() { eiger_scheduler_update(); }

void main() {
    setup();
    while (1) {
        infinite();
    }
}

void assert_failed(char *file, uint32_t line) {}