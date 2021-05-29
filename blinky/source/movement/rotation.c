#include "rotation.h"

angle_degree calculate_moved_angle(void (*gyro_xyz)(float *),
                                   uint16_t diff_time_ms) {
    angle_degree angle;
    angle.x = 0;
    angle.y = 1;
    angle.z = 2;
    return angle;
}
