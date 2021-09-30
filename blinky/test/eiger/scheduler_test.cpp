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

bool update_timer(const uint16_t &max_updates) {
    eiger_scheduler_add_task(&run, 1);
    bool succesUpdate = true;
    for (uint32_t i = 0; (i < max_updates) && succesUpdate; i++) {
        succesUpdate = eiger_scheduler_update();
    }
    return succesUpdate;
}
TEST_F(UTScheduler, updateTimeMax) {
    const uint16_t max_updates = 10000;
    EXPECT_TRUE(update_timer(max_updates));
    EXPECT_EQ(1, fakeDelay->getDelayValue());
    EXPECT_EQ(max_updates, fakeDelay->getAmountCals());
}

TEST_F(UTScheduler, updateTimeMaxOverflow) {
    const uint16_t max_updates = 10001;
    EXPECT_TRUE(update_timer(max_updates));
    EXPECT_EQ(1, fakeDelay->getDelayValue());
    EXPECT_EQ(max_updates, fakeDelay->getAmountCals());
}

TEST(SchedulerNoSetup, noinit) { EXPECT_FALSE(eiger_scheduler_update()); }