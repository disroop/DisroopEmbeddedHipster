extern "C" {
#include "internal/rotation.h"
}
#include "gtest/gtest.h"

TEST(UTRotation, positive) {
    auto gyro_fake = [](float* xyz) {
        xyz[0] = 100;  // NOLINT
        xyz[1] = 200;  // NOLINT
        xyz[2] = 300;  // NOLINT
    };
    rotation_mdegps moved_angle = get_rotation(gyro_fake);
    EXPECT_EQ(100, moved_angle.x);
    EXPECT_EQ(200, moved_angle.y);
    EXPECT_EQ(300, moved_angle.z);
}
