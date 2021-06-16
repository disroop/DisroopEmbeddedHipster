extern "C" {
#include "indication.h"
}
#include "fake_led.hpp"
#include "gtest/gtest.h"
using namespace ::testing;

// Wrapper function uses a global to remember the object:
static std::unique_ptr<FakeLed> pfakeLed;
static void fake_led_set(int id) { pfakeLed->setLed(id); }
static void fake_led_disable(int id) { pfakeLed->disableLed(id); }

class UT_Indication : public testing::Test {
   public:
    void SetUp() override {
        pfakeLed = std::unique_ptr<FakeLed>(new FakeLed());
    }

    void TearDown() override {}
};

TEST_F(UT_Indication, indicate) {
    int ledID = 4;
    indication indicator =
        indication_create(ledID, &fake_led_set, &fake_led_disable);
    indication_indicate(indicator);
    EXPECT_EQ(ledID, pfakeLed->getId());
    EXPECT_TRUE(pfakeLed->isSet());
}

TEST_F(UT_Indication, reset_after_set) {
    int ledID = 4;
    indication indicator =
        indication_create(ledID, &fake_led_set, &fake_led_disable);
    indication_indicate(indicator);
    EXPECT_EQ(ledID, pfakeLed->getId());
    EXPECT_TRUE(pfakeLed->isSet());
    indication_reset(indicator);
    EXPECT_FALSE(pfakeLed->isSet());
}
