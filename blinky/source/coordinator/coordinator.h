#pragma once
#include <indication.h>
#include <inttypes.h>
#include <timer.h>

void coordinator_init(timer  t, indication indication_instance);
void coordinator_update();
