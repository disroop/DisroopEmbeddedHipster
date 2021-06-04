#include "tracker.h"

#include <stdlib.h>
angle_degree angle_movement = {0, 0, 0};
uint16_t range = 0;

void tracker_set_range(uint16_t value) { range = value; }

void tracker_reset_start_position() {
    angle_movement.x = 0;
    angle_movement.y = 0;
    angle_movement.z = 0;
}

void tracker_update_position(angle_degree angle) {
    angle_movement.x = +angle.x;
    angle_movement.y = +angle.y;
    angle_movement.z = +angle.z;
}
bool is_smaller_than_range(uint16_t angle) { return angle < range; }
bool tracker_is_within_range(angle_degree angle_changes) {
    angle_changes.x = abs(angle_movement.x);
    angle_changes.y = abs(angle_movement.y);
    angle_changes.z = abs(angle_movement.z);

    if (is_smaller_than_range(angle_changes.x) &&
        is_smaller_than_range(angle_changes.y) &&
        is_smaller_than_range(angle_changes.z)) {
        return true;
    } else {
        return false;
    }
}