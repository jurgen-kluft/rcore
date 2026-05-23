#include "rcore/c_timer.h"

#ifdef TARGET_ARDUINO

#    include "Arduino.h"

namespace ncore
{
    namespace ntimer
    {
        u64  millis() { return ::millis(); }
        u64  micros() { return ::micros(); }
        void delay(u32 ms) { ::delay(ms); }
        void delay_us(u32 us) { ::delayMicroseconds(us); }

        void tick_periodic_task(periodic_task_t* task, u64 now_ms)
        {
            if ((now_ms - task->last_run_ms) >= task->interval_ms)
            {
                task->last_run_ms = now_ms;
                task->task_fn(task->m_user);
            }
        }
    }  // namespace ntimer
}  // namespace ncore

#else

#    include <chrono>
#    include <thread>

namespace ncore
{
    namespace ntimer
    {
        u64  millis() { return static_cast<u64>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()); }
        u64  micros() { return static_cast<u64>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()); }
        void delay(u32 ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
        void delay_us(u32 us) { std::this_thread::sleep_for(std::chrono::microseconds(us)); }

        void tick_periodic_task(periodic_task_t* task, u64 now_ms)
        {
            if ((now_ms - task->last_run_ms) >= task->interval_ms)
            {
                task->last_run_ms = now_ms;
                task->task_fn(task->m_user);
            }
        }

    }  // namespace ntimer
}  // namespace ncore

#endif
