#pragma once

class FakeLed {
   public:
    explicit FakeLed(bool isOn = false);
    void setLed(int id);
    void disableLed(int id);
    int getId();
    bool isSet();

   private:
    int ledId;
    bool ledIsOn;
};
