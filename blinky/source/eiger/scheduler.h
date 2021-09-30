#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct scheduler_struct *scheduler;

void eiger_scheduler_delete(scheduler self);
scheduler eiger_scheduler_create(void (*delay_ms)(uint32_t));
void eiger_scheduler_add_task(scheduler self, void (*task)(void),
                              uint8_t update_time_ms);
bool eiger_scheduler_update(scheduler self);