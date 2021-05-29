#pragma once

class FakeGyro {
   public:
    explicit FakeGyro(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void set_gyro(float x, float y, float z);
    void gyro_xyz(float *xyz);

   private:
    typedef struct angle_type {
        float x;
        float y;
        float z;
    } angle;
    angle angle_diff;
};