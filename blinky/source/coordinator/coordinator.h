#pragma once
#include <inttypes.h>
#include <indication.h>

void coordinator_init(uint8_t base_ms, indication indication_instance);
void coordinator_destroy();
void coordinator_run();