#pragma once
#include "inttypes.h"

typedef struct angle_degree_type {
    uint8_t x;
    uint8_t y;
    uint8_t z;
} angle_degree;

angle_degree calculate_moved_angle(void (*gyro_xyz)(float*),
                                   uint16_t diff_time_ms);