#include "rotation.h"

angle_degree calculate_moved_angle(void (*gyro_xyz)(float *),
                                   uint16_t diff_time_ms) {
    float gyro_raw_data[3];
    gyro_xyz(gyro_raw_data);
    angle_degree angle;
    angle.x = (int16_t)(gyro_raw_data[0] / diff_time_ms);
    angle.y = (int16_t)(gyro_raw_data[1] / diff_time_ms);
    angle.z = (int16_t)(gyro_raw_data[2] / diff_time_ms);
    return angle;
}
