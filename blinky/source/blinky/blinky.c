#include "blinky.h"

timer timerIndicationOn;
indication indicator;
movement movement_sensor;

enum state_enum { STATE_IDLE, STATE_DETECTED };

enum state_enum state = STATE_IDLE;

void blinky_init(timer timer_instance, indication indication_instance,
                 movement movement_instance) {
    timerIndicationOn = timer_instance;
    indicator = indication_instance;
    movement_sensor = movement_instance;
    indication_reset(indicator);
    state = STATE_IDLE;
}

void update_state() {
    uint16_t elapsed_time_ms = eiger_timer_elapsed_time_ms(timerIndicationOn);
    bool rotated = movement_has_rotated(movement_sensor);
    if (state == STATE_DETECTED && elapsed_time_ms > 2000) {
        state = STATE_IDLE;
    } else if (state == STATE_IDLE && rotated) {
        state = STATE_DETECTED;
    }
}

void action() {
    if (state == STATE_IDLE) {
        indication_reset(indicator);
        eiger_timer_reset(timerIndicationOn);
    } else if (state == STATE_DETECTED) {
        indication_indicate(indicator);
        eiger_timer_update(timerIndicationOn);
        movement_reset(movement_sensor);
    }
}

void blinky_update() {
    update_state();
    action();
}
