#ifndef BLINKY_H
#define BLINKY_H

#include <inttypes.h>

#include "indication.h"
#include "movement.h"
#include "timer.h"

void blinky_init(timer t, indication indication_instance,
                 movement movement_instance);
void blinky_update();

#endif