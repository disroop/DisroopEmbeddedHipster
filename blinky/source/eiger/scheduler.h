#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct scheduler_struct *eiger_scheduler;

void eiger_scheduler_delete(eiger_scheduler self);
eiger_scheduler eiger_scheduler_create(void (*delay_ms)(uint32_t));
void eiger_scheduler_add_task(eiger_scheduler self, void (*task)(void),
                              uint8_t update_time_ms);
bool eiger_scheduler_update(eiger_scheduler self);