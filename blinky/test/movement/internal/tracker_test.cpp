extern "C" {
#include "internal/tracker.h"

#include "internal/rotation.h"
}
#include "gtest/gtest.h"
using namespace ::testing;
tracker tracker_instance;
class UT_Tracker : public testing::Test {
   public:
    void SetUp() override {
        tracker_instance = tracker_create();
        tracker_reset(tracker_instance);
    }

    void TearDown() override { tracker_delete(tracker_instance); }
};

TEST_F(UT_Tracker, overrange_x) {
    rotation_mdegps rotation_data;
    rotation_data.x = 501;
    rotation_data.y = 200;
    rotation_data.z = 100;
    tracker_set_threashold_rotation(tracker_instance, 500);
    tracker_update_position(tracker_instance, rotation_data);
    EXPECT_TRUE(tracker_has_rotated(tracker_instance));
}

TEST_F(UT_Tracker, overrange_y) {
    rotation_mdegps rotation_data;
    rotation_data.x = 301;
    rotation_data.y = 100;
    rotation_data.z = 502;
    tracker_set_threashold_rotation(tracker_instance, 500);
    tracker_update_position(tracker_instance, rotation_data);
    EXPECT_TRUE(tracker_has_rotated(tracker_instance));
}

TEST_F(UT_Tracker, overrange_z) {
    rotation_mdegps rotation_data;
    rotation_data.x = 101;
    rotation_data.y = 101;
    rotation_data.z = 501;
    tracker_set_threashold_rotation(tracker_instance, 500);
    tracker_update_position(tracker_instance, rotation_data);
    EXPECT_TRUE(tracker_has_rotated(tracker_instance));
}

TEST_F(UT_Tracker, overrange_reset) {
    rotation_mdegps rotation_data;
    rotation_data.x = 501;
    rotation_data.y = 501;
    rotation_data.z = 501;
    tracker_set_threashold_rotation(tracker_instance, 500);
    tracker_update_position(tracker_instance, rotation_data);
    EXPECT_TRUE(tracker_has_rotated(tracker_instance));
    tracker_reset(tracker_instance);
    EXPECT_FALSE(tracker_has_rotated(tracker_instance));
}

TEST_F(UT_Tracker, inrange) {
    rotation_mdegps rotation_data;
    rotation_data.x = 499;
    rotation_data.y = 200;
    rotation_data.z = 100;
    tracker_set_threashold_rotation(tracker_instance, 500);
    tracker_update_position(tracker_instance, rotation_data);
    EXPECT_FALSE(tracker_has_rotated(tracker_instance));
}
