#include "scheduler.h"
typedef struct task_map_type {
    void (*task)(void);
    uint8_t update_time_ms;
} task_map;

struct scheduler_type {
    void (*delay_func)(uint32_t);
    task_map tasks[5];
    uint8_t amount_task;
    uint8_t time_base_ms;
    uint16_t max_time_slot_ms;
    uint16_t time_cnt_ms;
} scheduler;

void eiger_scheduler_config_time(void (*delay_ms)(uint32_t)) {
    scheduler.delay_func = delay_ms;
    scheduler.amount_task = 0;
    scheduler.time_base_ms = 1;
    scheduler.max_time_slot_ms = 10000;
    scheduler.time_cnt_ms = 1;
}

void eiger_scheduler_add_task(void (*task)(void), uint8_t update_time_ms) {
    task_map added_task = {.task = task, .update_time_ms = update_time_ms};
    scheduler.tasks[scheduler.amount_task] = added_task;
    scheduler.amount_task++;
}

void eiger_scheduler_update() {
    for (uint8_t task_nr = 0; task_nr < scheduler.amount_task; task_nr++) {
        task_map current_tast = scheduler.tasks[task_nr];
        if (scheduler.time_cnt_ms % (current_tast.update_time_ms + 1) == 0) {
            current_tast.task();
        }
    }
    if (scheduler.time_cnt_ms > scheduler.max_time_slot_ms) {
        scheduler.time_cnt_ms = 1;
    } else {
        scheduler.time_cnt_ms++;
    }
    scheduler.delay_func(scheduler.time_base_ms);
}
