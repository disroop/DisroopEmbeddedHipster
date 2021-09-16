#include "indication_fake.h"

#include <inttypes.h>
#include <stdlib.h>

typedef struct indication_struct {
    uint8_t led_indicate_counter;
    uint8_t led_reset_counter;
} indication_struct;

indication indication_create(uint8_t led_number, void (*enable_led)(int),
                             void (*disable_led)(int)) {
    indication indication = malloc(sizeof(indication_struct));
    indication->led_reset_counter = 0;
    indication->led_indicate_counter = 0;
    return indication;
}

void indication_destroy(indication self) { free(self); }

void indication_indicate(indication self) { self->led_indicate_counter++; }

void indication_reset(indication self) { self->led_reset_counter++; }

uint8_t indication_get_indicate_counter(indication self) {
    return self->led_indicate_counter;
}

uint8_t indication_get_reset_counter(indication self) {
    return self->led_reset_counter;
}