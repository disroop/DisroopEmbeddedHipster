#include "indication.h"

#include <stdlib.h>

typedef struct indication_struct {
    void (*indicate)(int);
    void (*reset)(int);
    uint8_t led_number;
} indication_struct;

indication indication_create(uint8_t led_number, void (*enable_led)(int),
                             void (*disable_led)(int)) {
    indication indicator = malloc(sizeof(indication_struct));
    indicator->led_number = led_number;
    indicator->indicate = enable_led;
    indicator->reset = disable_led;
    return indicator;
}

void indication_destroy(indication self) { free(self); }

void indication_indicate(indication self) { self->indicate(self->led_number); }

void indication_reset(indication self) { self->reset(self->led_number); }
