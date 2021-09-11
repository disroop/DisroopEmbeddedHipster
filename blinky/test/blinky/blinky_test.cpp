extern "C" {
#include "blinky.h"
}

#include "gtest/gtest.h"

std::function<void(int)> set_led, disable_led;
extern "C" void wrapper_set_led(int i) { set_led(i); }
extern "C" void wrapper_disable_led(int i) { disable_led(i); }

class UT_Blinky : public testing::Test {
   public:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(UT_Blinky, test1) {
    // TODO: Needs refactoring - WIP
    auto gyro_fake = [](float *xyz) {
        xyz[0] = 100;
        xyz[1] = 200;
        xyz[2] = 10001;
    };
    movement movement_instance = movement_create(gyro_fake);
    uint8_t base_ms = 100;
    timer timerIndicationOn = eiger_timer_create(base_ms);

    int ledId = 4;
    int hwLedId = 0;
    bool hwLedOn = false;

    set_led = [&](int id) {
        hwLedId = id;
        hwLedOn = true;
    };
    disable_led = [&](int id) { hwLedOn = false; };

    indication indicator =
        indication_create(ledId, wrapper_set_led, wrapper_disable_led);

    movement_run(movement_instance);
    blinky_init(timerIndicationOn, indicator, movement_instance);
    blinky_update();
    EXPECT_TRUE(hwLedOn);
}
