#include "coordinator.h"

#include "indication.h"
#include "movement.h"
#include "timer.h"

timer timerIndicationOn;
indication indicator;

void coordinator_init(timer t, indication indication_instance) {
    timerIndicationOn = t;
    indicator = indication_instance;
    indication_reset(indicator);
}

void coordinator_run() {
    if (movement_has_rotated()) {
        indication_indicate(indicator);
        eiger_timer_update(timerIndicationOn);
        movement_reset();
    } else if (eiger_timer_elapsed_time_ms(timerIndicationOn) > 2000) {
        indication_reset(indicator);
        eiger_timer_reset(timerIndicationOn);
    }
}
