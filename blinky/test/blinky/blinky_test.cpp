extern "C" {
#include "blinky.h"
}

#include "gtest/gtest.h"

class UT_Blinky : public testing::Test {
   public:
    void SetUp() override {}

    void TearDown() override {}
};

// Test notes
// The blinky application shall detect a movement.
// A movement detection shall be indicated with a led.
// The led shall run for 2 seconds longer than the movement has been detected.
// after two seconds of no movement detection the led shall be switched off.
// a movement ist detected if the device rotated at as speed above n degrees/per second. How much is n?

TEST_F(UT_Blinky, test1) {
    // int ledID = 4;
    // indication indicator =
    // indication_create(ledID, &fake_led_set, &fake_led_disable);
    // indication_indicate(indicator);
    EXPECT_EQ(1, 1);
    // EXPECT_TRUE(pfakeLed->isSet());
}
