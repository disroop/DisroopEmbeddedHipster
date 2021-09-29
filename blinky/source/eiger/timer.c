#include "timer.h"

#include <stdint.h>
#include <stdlib.h>
typedef struct timer_struct {
    uint16_t counter;
    uint16_t base_ms;
} __attribute__((aligned(4))) timer_struct;

timer eiger_timer_create(int16_t base_ms) {
    timer timer_instance = malloc(sizeof(timer_struct));
    timer_instance->counter = 0;
    timer_instance->base_ms = base_ms;
    return timer_instance;
}

void eiger_timer_destroy(timer self) { free(self); }

void eiger_timer_reset(timer self) { self->counter = 0; }

uint16_t eiger_timer_elapsed_time_ms(timer self) {
    return self->counter * self->base_ms;
}

void eiger_timer_update(timer self) {
    if (self->counter < UINT16_MAX) {
        self->counter++;
    } else {
        self->counter = UINT16_MAX;
    }
}
