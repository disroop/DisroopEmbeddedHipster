#pragma once
#include <stdbool.h>

#include "rotation.h"

void tracker_set_threashold_rotation(uint16_t threshold_mdegps);

void tracker_reset();

bool tracker_has_rotated();

void tracker_update_position(rotation_mdegps rotation);