extern "C" {
#include "blinky.h"
}

#include "gtest/gtest.h"

class UT_Blinky : public testing::Test {
   public:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(UT_Blinky, test1) {
    // int ledID = 4;
    // indication indicator =
    // indication_create(ledID, &fake_led_set, &fake_led_disable);
    // indication_indicate(indicator);
    EXPECT_EQ(1, 1);
    // EXPECT_TRUE(pfakeLed->isSet());
}
