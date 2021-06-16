extern "C" {
#include "timer.h"
}
#include "gtest/gtest.h"

timer timerA;
class UT_Timer : public testing::Test {
   public:
    void SetUp() override { timerA = eiger_timer_create(10); }

    void TearDown() override { eiger_timer_destroy(timerA); }
};

TEST_F(UT_Timer, elapsedTime) {
    for (uint8_t i = 0; i < 11; i++) {
        eiger_timer_update(timerA);
    }
    EXPECT_EQ(110, eiger_timer_elapsed_time_ms(timerA));
}

TEST_F(UT_Timer, SmallElapsedTIme) {
    for (uint8_t i = 0; i < 1; i++) {
        eiger_timer_update(timerA);
    }
    EXPECT_EQ(10, eiger_timer_elapsed_time_ms(timerA));
}

TEST_F(UT_Timer, reset) {
    for (uint8_t i = 0; i < 10; i++) {
        eiger_timer_update(timerA);
    }
    EXPECT_EQ(100, eiger_timer_elapsed_time_ms(timerA));
    eiger_timer_reset(timerA);
    EXPECT_EQ(0, eiger_timer_elapsed_time_ms(timerA));
}
