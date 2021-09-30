#include <cstdint>
extern "C" {
#include "timer.h"
}
#include "gtest/gtest.h"

timer timerA;
class UTTimer : public testing::Test {
   private:
    const uint8_t timerA_update_time_ms = 10;

   public:
    void SetUp() override {
        timerA = eiger_timer_create(timerA_update_time_ms);
    }

    void TearDown() override { eiger_timer_destroy(timerA); }
};

TEST_F(UTTimer, elapsedTime) {
    const uint8_t max_updates = 11;
    for (uint8_t i = 0; i < max_updates; i++) {
        eiger_timer_update(timerA);
    }
    EXPECT_EQ(110, eiger_timer_elapsed_time_ms(timerA));
}

TEST_F(UTTimer, SmallElapsedTIme) {
    const uint8_t max_updates = 1;
    for (uint8_t i = 0; i < max_updates; i++) {
        eiger_timer_update(timerA);
    }
    EXPECT_EQ(10, eiger_timer_elapsed_time_ms(timerA));
}

TEST_F(UTTimer, reset) {
    const uint8_t max_updates = 10;
    for (uint8_t i = 0; i < max_updates; i++) {
        eiger_timer_update(timerA);
    }
    EXPECT_EQ(100, eiger_timer_elapsed_time_ms(timerA));
    eiger_timer_reset(timerA);
    EXPECT_EQ(0, eiger_timer_elapsed_time_ms(timerA));
}
