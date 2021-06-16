#include "coordinator.h"

#include <stddef.h>

#include "indication.h"
#include "movement.h"
#include "timer.h"

timer timerIndicationOn = NULL;
enum mode_enum { MODE_IDLE, MODE_DETECTED } mode = MODE_IDLE;
indication indicator;

void coordinator_init(uint8_t base_ms, indication indication_instance) {
    if (timerIndicationOn == NULL) {
        timerIndicationOn = eiger_timer_create(base_ms);
    }
    indicator = indication_instance;
    indication_reset(indicator);
    mode = MODE_IDLE;
}

void coordinator_destroy() { eiger_timer_destroy(timerIndicationOn); }

void set_mode() {
    if (movement_has_rotated()) {
        mode = MODE_DETECTED;
    }
    if (eiger_timer_elapsed_time_ms(timerIndicationOn) > 2000) {
        mode = MODE_IDLE;
    }
}

void action() {
    if (mode == MODE_IDLE) {
        indication_reset(indicator);
        eiger_timer_reset(timerIndicationOn);
    }
    if (mode == MODE_DETECTED) {
        indication_indicate(indicator);
        eiger_timer_update(timerIndicationOn);
        movement_reset();
    }
}

void coordinator_run() {
    set_mode();
    action();
}
