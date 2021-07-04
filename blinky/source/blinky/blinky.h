#pragma once
#include <indication.h>
#include <inttypes.h>
#include <timer.h>

void blinky_init(timer  t, indication indication_instance);
void blinky_update();
