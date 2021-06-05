#pragma once
#include "inttypes.h"

typedef struct rotation_mdegps_type {
    int16_t x;
    int16_t y;
    int16_t z;
} rotation_mdegps;

rotation_mdegps get_rotation(void (*gyro_xyz)(float*));
