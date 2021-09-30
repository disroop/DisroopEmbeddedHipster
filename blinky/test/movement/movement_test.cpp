extern "C" {
#include "movement.h"
}
#include "gtest/gtest.h"

TEST(UTMovement, runOverThreshold) {
    auto gyro_fake = [](float *xyz) {
        xyz[0] = 100;    // NOLINT
        xyz[1] = 200;    // NOLINT
        xyz[2] = 10001;  // NOLINT
    };
    movement movement_instance = movement_create(gyro_fake);
    movement_reset(movement_instance);
    movement_run(movement_instance);
    EXPECT_TRUE(movement_has_rotated(movement_instance));
    movement_delete(movement_instance);
}

TEST(UTMovement, runBelowThreshold) {
    auto gyro_fake = [](float *xyz) {
        xyz[0] = 10000;  // NOLINT
        xyz[1] = 200;    // NOLINT
        xyz[2] = 400;    // NOLINT
    };
    movement movement_instance = movement_create(gyro_fake);
    movement_reset(movement_instance);
    movement_run(movement_instance);
    EXPECT_FALSE(movement_has_rotated(movement_instance));
    movement_delete(movement_instance);
}

TEST(UTMovement, notRunOverThreshold) {
    auto gyro_fake = [](float *xyz) {
        xyz[0] = 100;    // NOLINT
        xyz[1] = 200;    // NOLINT
        xyz[2] = 10001;  // NOLINT
    };
    movement movement_instance = movement_create(gyro_fake);
    movement_reset(movement_instance);
    EXPECT_FALSE(movement_has_rotated(movement_instance));
    movement_delete(movement_instance);
}

TEST(UTMovement, reset) {
    auto gyro_fake = [](float *xyz) {
        xyz[0] = 100;    // NOLINT
        xyz[1] = 200;    // NOLINT
        xyz[2] = 10001;  // NOLINT
    };
    movement movement_instance = movement_create(gyro_fake);
    movement_reset(movement_instance);
    EXPECT_FALSE(movement_has_rotated(movement_instance));
    movement_run(movement_instance);
    EXPECT_TRUE(movement_has_rotated(movement_instance));
    movement_reset(movement_instance);
    EXPECT_FALSE(movement_has_rotated(movement_instance));
    movement_delete(movement_instance);
}
