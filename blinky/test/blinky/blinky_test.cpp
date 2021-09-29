extern "C" {
#include "blinky.h"

#include "indication_fake.h"
#include "movement_fake.h"
#include "timer.h"
}
#include <cinttypes>

#include "gtest/gtest.h"

class UTBlinky : public testing::Test {
   public:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(UTBlinky, noindication) {
    const uint8_t timer_update_ms = 100;
    timer timer_indication = eiger_timer_create(timer_update_ms);
    indication indicator_fake = indication_create(0, nullptr, nullptr);
    movement movement_fake = movement_create(nullptr);
    blinky_init(timer_indication, indicator_fake, movement_fake);
    blinky_update();
    uint8_t cnt_reset = indication_get_reset_counter(indicator_fake);
    uint8_t cnt_indication = indication_get_indicate_counter(indicator_fake);

    EXPECT_EQ(2, cnt_reset);
    EXPECT_EQ(0, cnt_indication);
}
