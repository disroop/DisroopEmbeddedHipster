#include "rotation.h"

#include <stdbool.h>

rotation_mdegps get_rotation(void (*gyro_xyz)(float *)) {
    float gyro_raw_data[3];
    gyro_xyz(gyro_raw_data);
    return (rotation_mdegps){.x = (int16_t)(gyro_raw_data[0]),
                             .y = (int16_t)(gyro_raw_data[1]),
                             .z = (int16_t)(gyro_raw_data[2])};
}
