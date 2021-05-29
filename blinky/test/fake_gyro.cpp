#include "fake_gyro.hpp"

FakeGyro::FakeGyro(float x, float y, float z) : angle_diff({x, y, z}){};

void FakeGyro::gyro_xyz(float *xyz) {
    xyz[0] = angle_diff.x;
    xyz[1] = angle_diff.y;
    xyz[2] = angle_diff.z;
}

void FakeGyro::set_gyro(float x, float y, float z) {
    angle_diff.x = x;
    angle_diff.y = y;
    angle_diff.z = z;
}
