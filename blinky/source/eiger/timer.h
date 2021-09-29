#pragma once
#include <inttypes.h>
#include <stdint.h>

typedef struct timer_struct *timer;

timer eiger_timer_create(int16_t base_ms);

void eiger_timer_destroy(timer self);

void eiger_timer_reset(timer self);

uint16_t eiger_timer_elapsed_time_ms(timer self);

void eiger_timer_update(timer self);
