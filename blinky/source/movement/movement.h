#pragma once
#include <stdbool.h>

typedef struct movement_struct *movement;

movement movement_create(void (*gyro_xyz)(float *));
void movement_delete(movement self);
void movement_reset(movement self);
bool movement_has_rotated(movement self);
void movement_run(movement self);