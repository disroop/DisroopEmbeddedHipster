#pragma once
#include <stdbool.h>

#include "rotation.h"

void tracker_set_range(uint16_t value);
void tracker_reset_start_position();

void tracker_update_position(angle_degree angle);
bool tracker_is_within_range(angle_degree angle_changes);