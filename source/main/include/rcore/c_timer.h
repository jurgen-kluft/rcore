#ifndef __ARDUINO_CORE_TIMER_H__
#define __ARDUINO_CORE_TIMER_H__
#include "rcore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

namespace ncore
{
    namespace ntimer
    {
        u64 millis();
        u64 micros();

        // Delay waits for n milliseconds before resuming execution.
        // @see: https://docs.arduino.cc/language-reference/en/functions/time/delay/
        void delay(u32 ms);
        void delay_us(u32 us);

        struct periodic_task_t
        {
            u32     interval_ms;
            u32     last_run_ms;
            void (*task_fn)();
        };
        static inline void init_periodic_task(periodic_task_t* task, u32 interval_ms, void (*task_fn)())
        {
            task->interval_ms  = interval_ms;
            task->last_run_ms = 0;
            task->task_fn     = task_fn;
        }

        void tick(periodic_task_t* task);

    }  // namespace ntimer
}  // namespace ncore

#endif  // __ARDUINO_CORE_TIMER_H__
