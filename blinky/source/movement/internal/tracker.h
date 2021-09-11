#ifndef INTERNAL_TRACKER_H
#define INTERNAL_TRACKER_H
#include <stdbool.h>

#include "rotation.h"

typedef struct tracker_struct *tracker;

tracker tracker_create();

void tracker_delete(tracker self);

void tracker_set_threashold_rotation(tracker self, uint16_t threshold_mdegps);

void tracker_reset(tracker self);

bool tracker_has_rotated(tracker self);

void tracker_update_position(tracker self, rotation_mdegps rotation);

#endif