#ifndef INDICATION_H
#define INDICATION_H

#include <inttypes.h>

typedef struct indication_struct *indication;

indication indication_create(uint8_t led_number, void (*enable_led)(int),
                             void (*disable_led)(int));

void indication_destroy(indication self);

void indication_indicate(indication self);

void indication_reset(indication self);

#endif