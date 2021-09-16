#include "movement_fake.h"

#include <stdlib.h>

typedef struct movement_struct {
    bool rotated;
    int counter;
} movement_struct;

movement movement_create(void (*gyro_xyz)(float*)) {
    movement movement = malloc(sizeof(movement_struct));
    movement->rotated = false;
    movement->counter = 0;
    return movement;
}

void movement_delete(movement self) { free(self); }

void movement_reset(movement self) { self->rotated = false; }

bool movement_has_rotated(movement self) { return self->rotated; }

void movement_run(movement self) { self->counter++; }

void movement_set_rotated(movement self, bool rotation_detection) {
    self->rotated = rotation_detection;
}

void movement_reset_run(movement self) { self->counter = 0; }