#ifndef __ARDUINO_CORE_SYSTEM_DEEPSLEEP_H__
#define __ARDUINO_CORE_SYSTEM_DEEPSLEEP_H__
#include "rcore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

namespace ncore
{
    namespace nsystem
    {
        namespace ndeepsleep
        {
            namespace nwakeup
            {
                typedef s8 reason_t;

                const reason_t REASON_UNDEFINED       = 0;   // In case of deep sleep, reset was not caused by exit from deep sleep
                const reason_t REASON_EXT0            = 1;   // Wakeup caused by external signal using RTC_IO
                const reason_t REASON_EXT1            = 2;   // Wakeup caused by external signal using RTC_CNTL
                const reason_t REASON_TIMER           = 3;   // Wakeup caused by timer
                const reason_t REASON_TOUCHPAD        = 4;   // Wakeup caused by touchpad
                const reason_t REASON_ULP             = 5;   // Wakeup caused by ULP program
                const reason_t REASON_GPIO            = 6;   // Wakeup caused by GPIO (light sleep only on ESP32, S2 and S3)
                const reason_t REASON_UART            = 7;   // Wakeup caused by UART (light sleep only)
                const reason_t REASON_WIFI            = 8;   // Wakeup caused by WIFI (light sleep only)
                const reason_t REASON_COCPU           = 9;   // Wakeup caused by COCPU int
                const reason_t REASON_COCPU_TRAP_TRIG = 10;  // Wakeup caused by COCPU crash
                const reason_t REASON_BT              = 11;  // Wakeup caused by BT (light sleep only)

                reason_t    reason();
                const char* to_string(reason_t reason);
            }  // namespace nwakeup

            void snooze(u32 seconds);  // start deep sleep with a timer wakeup

        }  // namespace ndeepsleep

    }  // namespace nsystem
}  // namespace ncore

#endif  // __ARDUINO_CORE_SYSTEM_DEEPSLEEP_H__