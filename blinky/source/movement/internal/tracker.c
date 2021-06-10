#include "tracker.h"

#include <stdlib.h>

uint16_t rotation_threshold_mdegps = 0;
bool hasRotated = false;

void tracker_set_threashold_rotation(uint16_t threshold_mdegps) {
    rotation_threshold_mdegps = threshold_mdegps;
}

void tracker_reset() { hasRotated = false; }

bool tracker_has_rotated() { return hasRotated; }

void tracker_update_position(rotation_mdegps rotation) {
    if ((rotation.x > rotation_threshold_mdegps) ||
        (rotation.y > rotation_threshold_mdegps) ||
        (rotation.z > rotation_threshold_mdegps)) {
        hasRotated = true;
    }
}
