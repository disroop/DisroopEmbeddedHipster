extern "C" {
#include "rotation.h"
}
#include "fake_gyro.hpp"
#include "gtest/gtest.h"
using namespace ::testing;

// Wrapper function uses a global to remember the object:
static std::unique_ptr<FakeGyro> pfakeGyro;
static void fake_gyro_wrapper(float* xyz) { pfakeGyro->gyro_xyz(xyz); }

class UT_Rotation : public testing::Test {
   public:
    void SetUp() override {
        pfakeGyro = std::unique_ptr<FakeGyro>(new FakeGyro());
    }

    void TearDown() override {}
};

TEST(UT_Rotation, positive) {
    angle_degree moved_angle = calculate_moved_angle(&fake_gyro_wrapper, 0);
    EXPECT_TRUE(false);
}
