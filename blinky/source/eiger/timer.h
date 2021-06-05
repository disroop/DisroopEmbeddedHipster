#pragma once
#include <inttypes.h>

typedef struct timer_struct *timer;

timer timer_create(int16_t base_ms);

void timer_destroy(timer self);

void timer_reset(timer self);

uint16_t timer_elapsed_time_ms(timer self);

void timer_update(timer self);