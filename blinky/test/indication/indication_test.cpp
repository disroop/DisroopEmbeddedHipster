extern "C" {
#include "indication.h"
}
#include "gtest/gtest.h"

std::function<void(int)> set_led, disable_led;
extern "C" void wrapper_set_led(int i) { set_led(i); }
extern "C" void wrapper_disable_led(int i) { disable_led(i); }

TEST(UTIndication, indicate) {
    int ledId = 4;
    int hwLedId = 0;
    bool hwLedOn = false;
    bool runDisableLed = false;

    set_led = [&](int id) {
        hwLedId = id;
        hwLedOn = true;
    };
    disable_led = [&](int /*id*/) { runDisableLed = true; };

    indication indicator =
        indication_create(ledId, wrapper_set_led, wrapper_disable_led);

    indication_indicate(indicator);
    EXPECT_EQ(ledId, hwLedId);
    EXPECT_TRUE(hwLedOn);
    EXPECT_FALSE(runDisableLed);
}

TEST(UTIndication, resetled) {
    int ledId = 4;
    int hwLedId = 0;
    bool hwLedOn = false;
    bool runEnableLed = false;

    set_led = [&](int /*id*/) { runEnableLed = true; };
    disable_led = [&](int id) {
        hwLedId = id;
        hwLedOn = false;
    };

    indication indicator =
        indication_create(ledId, wrapper_set_led, wrapper_disable_led);

    indication_reset(indicator);
    EXPECT_EQ(ledId, hwLedId);
    EXPECT_FALSE(hwLedOn);
    EXPECT_FALSE(runEnableLed);
}
