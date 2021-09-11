extern "C" {
#include "movement.h"
}
#include "gtest/gtest.h"
using namespace ::testing;

TEST(UT_Movement, run_over_threshold) {
    auto gyro_fake = [](float *xyz) {
        xyz[0] = 100;
        xyz[1] = 200;
        xyz[2] = 10001;
    };
    movement movement_instance = movement_create(gyro_fake);
    movement_reset(movement_instance);
    movement_run(movement_instance);
    EXPECT_TRUE(movement_has_rotated(movement_instance));
    movement_delete(movement_instance);
}

TEST(UT_Movement, run_below_threshold) {
    auto gyro_fake = [](float *xyz) {
        xyz[0] = 10000;
        xyz[1] = 200;
        xyz[2] = 400;
    };
    movement movement_instance = movement_create(gyro_fake);
    movement_reset(movement_instance);
    movement_run(movement_instance);
    EXPECT_FALSE(movement_has_rotated(movement_instance));
    movement_delete(movement_instance);
}

TEST(UT_Movement, not_run_over_threshold) {
    auto gyro_fake = [](float *xyz) {
        xyz[0] = 100;
        xyz[1] = 200;
        xyz[2] = 10001;
    };
    movement movement_instance = movement_create(gyro_fake);
    movement_reset(movement_instance);
    EXPECT_FALSE(movement_has_rotated(movement_instance));
    movement_delete(movement_instance);
}

TEST(UT_Movement, reset) {
    auto gyro_fake = [](float *xyz) {
        xyz[0] = 100;
        xyz[1] = 200;
        xyz[2] = 10001;
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
