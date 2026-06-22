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
            u64   interval_ms;
            u64   last_run_ms;
            void* m_user;
            void (*task_fn)(void* user);
        };
        static inline void mark_periodic_task(periodic_task_t* task, u64 now_ms) { task->last_run_ms = now_ms; }
        static inline void init_periodic_task(periodic_task_t* task, u64 interval_ms, void* user, void (*task_fn)(void* user))
        {
            task->interval_ms = interval_ms;
            task->last_run_ms = 0;
            task->m_user      = user;
            task->task_fn     = task_fn;
        }

        void tick_periodic_task(periodic_task_t* task, u64 now_ms);

    }  // namespace ntimer
}  // namespace ncore

#endif  // __ARDUINO_CORE_TIMER_H__
