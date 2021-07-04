#include "coordinator.h"

#include "indication.h"
#include "movement.h"
#include "timer.h"

timer timerIndicationOn;
indication indicator;

enum state_enum { STATE_IDLE, STATE_DETECTED };

enum state_enum state = STATE_IDLE;

void coordinator_init(timer t, indication indication_instance) {
    timerIndicationOn = t;
    indicator = indication_instance;
    indication_reset(indicator);
    state = STATE_IDLE;
}

void update_state() {
    uint16_t elapsed_time_ms = eiger_timer_elapsed_time_ms(timerIndicationOn);
    bool has_rotated = movement_has_rotated();
    if (state == STATE_DETECTED && elapsed_time_ms > 2000) {
        state = STATE_IDLE;
    } else if (state == STATE_IDLE && has_rotated) {
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
        movement_reset();
    }
}

void coordinator_update() {
    update_state();
    action();
}
