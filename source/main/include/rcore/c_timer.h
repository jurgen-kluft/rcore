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

        typedef void (*periodic_task_fn)(void* user, u64 now_ms);

        struct periodic_task_t
        {
            u64              m_next_ms;
            u32              m_interval_ms;
            void*            m_user;
            periodic_task_fn m_task_fn;
        };
        static inline bool due_periodic_task(periodic_task_t* task, u64 now_ms) { return now_ms >= task->m_next_ms; }
        static inline void mark_periodic_task(periodic_task_t* task, u64 now_ms) { task->m_next_ms = now_ms + task->m_interval_ms; }
        static inline void init_periodic_task(periodic_task_t* task, u32 interval_ms, void* user, periodic_task_fn fn)
        {
            task->m_interval_ms = interval_ms;
            task->m_next_ms     = 0;
            task->m_user        = user;
            task->m_task_fn     = fn;
        }

        void tick_periodic_task(periodic_task_t* task, u64 now_ms);

    }  // namespace ntimer
}  // namespace ncore

#endif  // __ARDUINO_CORE_TIMER_H__
