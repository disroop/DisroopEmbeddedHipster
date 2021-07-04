extern "C" {
#include "internal/rotation.h"
}
#include "gtest/gtest.h"

TEST(UT_Rotation, positive) {
    auto gyro_fake = [](float* xyz) {
        xyz[0] = 100;
        xyz[1] = 200;
        xyz[2] = 300;
    };
    rotation_mdegps moved_angle = get_rotation(gyro_fake);
    EXPECT_EQ(100, moved_angle.x);
    EXPECT_EQ(200, moved_angle.y);
    EXPECT_EQ(300, moved_angle.z);
}
