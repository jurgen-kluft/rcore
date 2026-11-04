#include "rcore/c_timer.h"

#ifdef TARGET_ARDUINO

#    include "Arduino.h"

namespace ncore
{
    namespace ntimer
    {
        void delay(u32 ms) { ::delay(ms); }
        void delay_us(u32 us) { ::delayMicroseconds(us); }

        static u64 platform_millis(void*) { return ::millis(); }
        static u64 platform_micros(void*) { return ::micros(); }
        static clock_ops_t g_clock_ops = {nullptr, platform_millis, platform_micros};

        u64 millis() { return g_clock_ops.m_millis(g_clock_ops.m_context); }
        u64 micros() { return g_clock_ops.m_micros(g_clock_ops.m_context); }

        void default_clock_ops()
        {
            g_clock_ops.m_context = nullptr;
            g_clock_ops.m_millis  = platform_millis;
            g_clock_ops.m_micros  = platform_micros;
        }

        void set_clock_ops(void* context, clock_now_fn millis, clock_now_fn micros)
        {
            if (!millis) millis = platform_millis;
            if (!micros) micros = platform_micros;
            g_clock_ops.m_context = context;
            g_clock_ops.m_millis  = millis;
            g_clock_ops.m_micros  = micros;
        }

        void tick_periodic_task(periodic_task_t* task, u64 now_ms)
        {
            if (now_ms >= task->m_next_ms)
            {
                if (task->m_next_ms == 0)
                {
                    task->m_next_ms = now_ms;
                }
                else
                {
                    task->m_next_ms += task->m_interval_ms;
                }
                task->m_task_fn(task->m_user, now_ms);
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
        void delay(u32 ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
        void delay_us(u32 us) { std::this_thread::sleep_for(std::chrono::microseconds(us)); }

        static u64 platform_millis(void*) { return static_cast<u64>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()); }
        static u64 platform_micros(void*) { return static_cast<u64>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()); }
        static clock_ops_t g_clock_ops = {nullptr, platform_millis, platform_micros};

        u64 millis() { return g_clock_ops.m_millis(g_clock_ops.m_context); }
        u64 micros() { return g_clock_ops.m_micros(g_clock_ops.m_context); }

        void default_clock_ops()
        {
            g_clock_ops.m_context = nullptr;
            g_clock_ops.m_millis  = platform_millis;
            g_clock_ops.m_micros  = platform_micros;
        }

        void set_clock_ops(void* context, clock_now_fn millis, clock_now_fn micros)
        {
            if (!millis) millis = platform_millis;
            if (!micros) micros = platform_micros;
            g_clock_ops.m_context = context;
            g_clock_ops.m_millis  = millis;
            g_clock_ops.m_micros  = micros;
        }

        void tick_periodic_task(periodic_task_t* task, u64 now_ms)
        {
            if (due_periodic_task(task, now_ms))
            {
                task->m_task_fn(task->m_user, now_ms);
                mark_periodic_task(task, now_ms);
            }
        }

    }  // namespace ntimer
}  // namespace ncore

#endif
