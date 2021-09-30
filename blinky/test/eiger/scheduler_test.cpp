extern "C" {
#include "scheduler.h"
}
#include <absl/memory/memory.h>

#include "fake_delay.hpp"
#include "gtest/gtest.h"

static std::unique_ptr<FakeDelay> fakeDelay;
static void fake_delay(uint32_t milliseconds) {
    fakeDelay->delayMs(milliseconds);
}

static uint32_t runCounter;
static void run() { runCounter++; }

class UTScheduler : public testing::Test {
   public:
    void SetUp() override {
        runCounter = 0;
        fakeDelay = absl::make_unique<FakeDelay>();
        eiger_scheduler_config_time(&fake_delay);
    }

    void TearDown() override {}
};

TEST_F(UTScheduler, updateTimeMax) {
    const uint16_t max_updates = 10000;
    eiger_scheduler_add_task(&run, 1);
    for (uint32_t i = 0; i < max_updates; i++) {
        eiger_scheduler_update();
    }
    EXPECT_EQ(1, fakeDelay->getDelayValue());
    EXPECT_EQ(max_updates, fakeDelay->getAmountCals());
}
