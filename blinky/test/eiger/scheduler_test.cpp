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
static eiger_scheduler schedulertest = nullptr;
class UTschedulertest : public testing::Test {
   private:
   public:
    void SetUp() override {
        runCounter = 0;
        fakeDelay = absl::make_unique<FakeDelay>();
        schedulertest = eiger_scheduler_create(&fake_delay);
    }

    void TearDown() override { eiger_scheduler_delete(schedulertest); }
};

auto update_timer(eiger_scheduler schedulertest, const uint16_t &max_updates)
    -> bool {
    eiger_scheduler_add_task(schedulertest, &run, 1);
    bool succesUpdate = true;
    for (uint32_t i = 0; (i < max_updates) && succesUpdate; i++) {
        succesUpdate = eiger_scheduler_update(schedulertest);
    }
    return succesUpdate;
}
TEST_F(UTschedulertest, updateTimeMax) {
    const uint16_t max_updates = 10000;
    EXPECT_TRUE(update_timer(schedulertest, max_updates));
    EXPECT_EQ(1, fakeDelay->getDelayValue());
    EXPECT_EQ(max_updates, fakeDelay->getAmountCals());
}

TEST_F(UTschedulertest, updateTimeMaxOverflow) {
    const uint16_t max_updates = 10001;
    EXPECT_TRUE(update_timer(schedulertest, max_updates));
    EXPECT_EQ(1, fakeDelay->getDelayValue());
    EXPECT_EQ(max_updates, fakeDelay->getAmountCals());
}

TEST(schedulertestNoSetup, noinit) {
    eiger_scheduler schedulertestnosetup = eiger_scheduler_create(&fake_delay);
    EXPECT_FALSE(eiger_scheduler_update(schedulertestnosetup));
    eiger_scheduler_delete(schedulertestnosetup);
}