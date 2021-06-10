#include "fake_led.hpp"

FakeLed::FakeLed(bool isOn) : ledId(0), ledIsOn(isOn) {}

void FakeLed::setLed(int id) {
    ledId = id;
    ledIsOn = true;
}

void FakeLed::disableLed(int id) {
    ledId = id;
    ledIsOn = false;
}

int FakeLed::getId() { return ledId; }

bool FakeLed::isSet() { return ledIsOn; }
