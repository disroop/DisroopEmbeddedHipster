extern "C" {
#include "movement.h"
}
#include "gtest/gtest.h"
#include "internal/fake_gyro.hpp"
using namespace ::testing;

// Wrapper function uses a global to remember the object:
static std::unique_ptr<FakeGyro> pfakeGyro;
static void fake_gyro_wrapper(float* xyz) { pfakeGyro->gyro_xyz(xyz); }

class UT_Movement : public testing::Test {
   public:
    void SetUp() override {
        pfakeGyro = std::unique_ptr<FakeGyro>(new FakeGyro());
    }

    void TearDown() override {}
};

TEST_F(UT_Movement, run_over_threshold) {
    pfakeGyro->set_gyro(100, 200, 10001);
    movement_init(&fake_gyro_wrapper);
    movement_reset();
    movement_run();
    EXPECT_TRUE(movement_has_rotated());
}

TEST_F(UT_Movement, run_below_threshold) {
    pfakeGyro->set_gyro(10000, 200, 400);
    movement_init(&fake_gyro_wrapper);
    movement_reset();
    movement_run();
    EXPECT_FALSE(movement_has_rotated());
}

TEST_F(UT_Movement, not_run_over_threshold) {
    pfakeGyro->set_gyro(100, 200, 10001);
    movement_init(&fake_gyro_wrapper);
    movement_reset();
    EXPECT_FALSE(movement_has_rotated());
}

TEST_F(UT_Movement, reset) {
    pfakeGyro->set_gyro(100, 200, 10001);
    movement_init(&fake_gyro_wrapper);
    movement_reset();
    EXPECT_FALSE(movement_has_rotated());
    movement_run();
    EXPECT_TRUE(movement_has_rotated());
    movement_reset();
    EXPECT_FALSE(movement_has_rotated());
}
