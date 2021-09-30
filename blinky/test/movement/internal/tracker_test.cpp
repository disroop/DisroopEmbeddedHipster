extern "C" {
#include "internal/tracker.h"

#include "internal/rotation.h"
}
#include "gtest/gtest.h"

tracker tracker_instance;
class UTTracker : public testing::Test {
   public:
    void SetUp() override {
        tracker_instance = tracker_create();
        tracker_reset(tracker_instance);
    }

    void TearDown() override { tracker_delete(tracker_instance); }
};

TEST_F(UTTracker, overrangeX) {
    rotation_mdegps rotation_data;

    rotation_data.x = 501;                                   // NOLINT
    rotation_data.y = 200;                                   // NOLINT
    rotation_data.z = 100;                                   // NOLINT
    tracker_set_threashold_rotation(tracker_instance, 500);  // NOLINT
    tracker_update_position(tracker_instance, rotation_data);
    EXPECT_TRUE(tracker_has_rotated(tracker_instance));
}

TEST_F(UTTracker, overrangeY) {
    rotation_mdegps rotation_data;
    rotation_data.x = 301;                                   // NOLINT
    rotation_data.y = 100;                                   // NOLINT
    rotation_data.z = 502;                                   // NOLINT
    tracker_set_threashold_rotation(tracker_instance, 500);  // NOLINT
    tracker_update_position(tracker_instance, rotation_data);
    EXPECT_TRUE(tracker_has_rotated(tracker_instance));
}

TEST_F(UTTracker, overrangeZ) {
    rotation_mdegps rotation_data;
    rotation_data.x = 101;                                   // NOLINT
    rotation_data.y = 101;                                   // NOLINT
    rotation_data.z = 501;                                   // NOLINT
    tracker_set_threashold_rotation(tracker_instance, 500);  // NOLINT
    tracker_update_position(tracker_instance, rotation_data);
    EXPECT_TRUE(tracker_has_rotated(tracker_instance));
}

TEST_F(UTTracker, overrangeReset) {
    rotation_mdegps rotation_data;
    rotation_data.x = 501;                                   // NOLINT
    rotation_data.y = 501;                                   // NOLINT
    rotation_data.z = 501;                                   // NOLINT
    tracker_set_threashold_rotation(tracker_instance, 500);  // NOLINT
    tracker_update_position(tracker_instance, rotation_data);
    EXPECT_TRUE(tracker_has_rotated(tracker_instance));
    tracker_reset(tracker_instance);
    EXPECT_FALSE(tracker_has_rotated(tracker_instance));
}

TEST_F(UTTracker, inRange) {
    rotation_mdegps rotation_data;
    rotation_data.x = 499;                                   // NOLINT
    rotation_data.y = 200;                                   // NOLINT
    rotation_data.z = 100;                                   // NOLINT
    tracker_set_threashold_rotation(tracker_instance, 500);  // NOLINT
    tracker_update_position(tracker_instance, rotation_data);
    EXPECT_FALSE(tracker_has_rotated(tracker_instance));
}
