#pragma once
#include <stdbool.h>

void movement_init(void (*gyro_xyz)(float*));
void movement_reset();
bool movement_has_rotated();
void movement_run();
