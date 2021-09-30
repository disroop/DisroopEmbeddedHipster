#pragma once

#include <stdbool.h>
#include <stdint.h>
void eiger_scheduler_config_time(void (*delay_ms)(uint32_t));
void eiger_scheduler_add_task(void (*task)(void), uint8_t update_time_ms);
bool eiger_scheduler_update();