extern "C" {
#include "internal/rotation.h"
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

TEST_F(UT_Rotation, positive) {
    pfakeGyro->set_gyro(100, 200, 300);
    angle_degree moved_angle = calculate_moved_angle(&fake_gyro_wrapper, 100);
    EXPECT_EQ(1, moved_angle.x);
    EXPECT_EQ(2, moved_angle.y);
    EXPECT_EQ(3, moved_angle.z);
}
