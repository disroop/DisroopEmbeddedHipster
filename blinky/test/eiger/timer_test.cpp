extern "C" {
#include "timer.h"
}
#include "gtest/gtest.h"
using namespace ::testing;

timer timerA;
class UT_Indication : public testing::Test {
   public:
    void SetUp() override { timerA = eiger_timer_create(10); }

    void TearDown() override { eiger_timer_destroy(timerA); }
};

TEST_F(UT_Indication, indicate) {
    for (uint8_t i = 0; i < 11; i++) {
        eiger_timer_update(timerA);
    }
    EXPECT_TRUE(eiger_timer_elapsed_time_ms(timerA));
}