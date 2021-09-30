#include <B-L475E-IOT01/stm32l475e_iot01_gyro.h>

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
    const uint8_t blinky_update_time_ms = 100;
    const uint8_t movement_update_time_ms = 20;

    platform_init();
    indication indicator = indication_create(
        LED_GREEN, (void (*)(int))BSP_LED_On, (void (*)(int))BSP_LED_Off);

    timer timerIndicationOn = eiger_timer_create(blinky_update_time_ms);
    movement hw_movement = movement_create(BSP_GYRO_GetXYZ);
    blinky_init(timerIndicationOn, indicator, hw_movement);
    eiger_scheduler_config_time(HAL_Delay);
    eiger_scheduler_add_task(blinky_update, blinky_update_time_ms);
    eiger_scheduler_add_task((void (*)(void))movement_run,
                             movement_update_time_ms);
}

int main() {
    setup();
    while (1) {
        if (!eiger_scheduler_update()) {
            break;
        }
    }
    return -1;
}

void assert_failed(char *file, uint32_t line) {}