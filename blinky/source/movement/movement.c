#include "movement.h"

#include <stdlib.h>

#include <inttypes.h>

#include "internal/rotation.h"
#include "internal/tracker.h"

const uint16_t threshold_rotation = 10000;

typedef struct movement_struct {
    tracker tracker;
    void (*gyro_hw_xyz)(float*);
} movement_struct;

movement movement_create(void (*gyro_xyz)(float*)) {
    movement movement = malloc(sizeof(movement_struct));
    movement->gyro_hw_xyz = gyro_xyz;
    movement->tracker = tracker_create();
    tracker_reset(movement->tracker);
    tracker_set_threashold_rotation(movement->tracker, threshold_rotation);
    return movement;
}

void movement_delete(movement self) {
    tracker_delete(self->tracker);
    free(self);
}

void movement_reset(movement self) { tracker_reset(self->tracker); }

bool movement_has_rotated(movement self) {
    return tracker_has_rotated(self->tracker);
}

void movement_run(movement self) {
    rotation_mdegps rotation_mdegps = get_rotation(self->gyro_hw_xyz);
    tracker_update_position(self->tracker, rotation_mdegps);
}
