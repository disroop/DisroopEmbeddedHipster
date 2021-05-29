#pragma once
#include "inttypes.h"

typedef struct angle_degree_type {
    int16_t x;
    int16_t y;
    int16_t z;
} angle_degree;

angle_degree calculate_moved_angle(void (*gyro_xyz)(float*),
                                   uint16_t diff_time_ms);