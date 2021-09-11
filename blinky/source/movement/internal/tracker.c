#include "tracker.h"

#include <stdlib.h>

typedef struct tracker_struct {
    uint16_t rotation_threshold_mdegps;
    bool hasRotated;
} tracker_struct;

tracker tracker_create() {
    tracker tracker = malloc(sizeof(tracker_struct));
    tracker->hasRotated = false;
    tracker->rotation_threshold_mdegps = 0;
    return tracker;
}

void tracker_delete(tracker self) { free(self); }

void tracker_set_threashold_rotation(tracker self, uint16_t threshold_mdegps) {
    self->rotation_threshold_mdegps = threshold_mdegps;
}

void tracker_reset(tracker self) { self->hasRotated = false; }

bool tracker_has_rotated(tracker self) { return self->hasRotated; }

void tracker_update_position(tracker self, rotation_mdegps rotation) {
    if ((rotation.x > self->rotation_threshold_mdegps) ||
        (rotation.y > self->rotation_threshold_mdegps) ||
        (rotation.z > self->rotation_threshold_mdegps)) {
        self->hasRotated = true;
    }
}
