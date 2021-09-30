#include "scheduler.h"

#include "stdlib.h"
typedef struct task_map_type {
    void (*task)(void);
    uint8_t update_time_ms;
} task_map;

#define MAX_AMOUNT_TASKS 5
static const int max_time_slots_ms = 10000;

typedef struct scheduler_struct {
    void (*delay_func)(uint32_t);
    task_map tasks[MAX_AMOUNT_TASKS];
    uint8_t amount_task;
    uint8_t time_base_ms;
    uint16_t max_time_slot_ms;
    uint16_t time_cnt_ms;
} scheduler_struct;

scheduler eiger_scheduler_create(void (*delay_ms)(uint32_t)) {
    scheduler scheduler = malloc(sizeof(scheduler_struct));
    scheduler->delay_func = delay_ms;
    scheduler->amount_task = 0;
    scheduler->time_base_ms = 1;
    scheduler->max_time_slot_ms = max_time_slots_ms;
    scheduler->time_cnt_ms = 1;
    return scheduler;
}

void eiger_scheduler_delete(scheduler self) { free(self); }

void eiger_scheduler_add_task(scheduler self, void (*task)(void),
                              uint8_t update_time_ms) {
    task_map added_task = {.task = task, .update_time_ms = update_time_ms};
    self->tasks[self->amount_task] = added_task;
    self->amount_task++;
}

bool eiger_scheduler_update(scheduler self) {
    if (self->amount_task == 0) {
        return false;
    }
    for (uint8_t task_nr = 0; task_nr < self->amount_task; task_nr++) {
        task_map current_task = self->tasks[task_nr];
        if (self->time_cnt_ms % (current_task.update_time_ms + 1) == 0) {
            current_task.task();
        }
    }
    if (self->time_cnt_ms > self->max_time_slot_ms) {
        self->time_cnt_ms = 1;
    } else {
        self->time_cnt_ms++;
    }
    self->delay_func(self->time_base_ms);
    return true;
}
