extern "C" {
#include "scheduler.h"
}
#include "fake_delay.hpp"
#include "gtest/gtest.h"
using namespace ::testing;

static std::unique_ptr<FakeDelay> fakeDelay;
static void fake_delay(uint32_t milliseconds) {
    fakeDelay->delayMs(milliseconds);
}

static uint32_t runCounter;
static void run() { runCounter++; }

class UT_Scheduler : public testing::Test {
   public:
    void SetUp() override {
        runCounter = 0;
        fakeDelay = std::unique_ptr<FakeDelay>(new FakeDelay());
        eiger_scheduler_config_time(&fake_delay);
    }

    void TearDown() override {}
};

TEST_F(UT_Scheduler, updateTimeMax) {
    eiger_scheduler_add_task(&run, 1);
    for (uint32_t i = 0; i < 10000; i++) {
        eiger_scheduler_update();
    }
    EXPECT_EQ(1, fakeDelay->getDelayValue());
    EXPECT_EQ(10000, fakeDelay->getAmountCals());
}
