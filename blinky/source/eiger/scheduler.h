#pragma once
#include <inttypes.h>
void scheduler_config_time(void (*delay_ms)(uint32_t));
void scheduler_add_task(void (*task)(void), uint8_t update_time_ms);
void scheduler_update();