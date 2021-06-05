#include "movement.h"

#include "internal/rotation.h"
#include "internal/tracker.h"

void (*gyro_hw_xyz)(float*);

void movement_init(void (*gyro_xyz)(float*)) {
    gyro_hw_xyz = gyro_xyz;
    tracker_reset();
    tracker_set_threashold_rotation(1000);
}

void movement_reset() { tracker_reset(); }

bool movement_has_rotated() { return tracker_has_rotated(); }

void movement_run() {
    rotation_mdegps rotation_mdegps = get_rotation(gyro_hw_xyz);
    tracker_update_position(rotation_mdegps);
}