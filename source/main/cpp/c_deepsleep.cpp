#include "rcore/c_str.h"
#include "rcore/c_deepsleep.h"

#ifdef TARGET_ESP32
#    include "Arduino.h"
#endif

namespace ncore
{
    namespace nsystem
    {
        namespace ndeepsleep
        {
            namespace nwakeup
            {
                reason_t reason()
                {
#ifdef TARGET_ESP32
                    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
                    switch (cause)
                    {
                        case ESP_SLEEP_WAKEUP_UNDEFINED: return REASON_UNDEFINED;
                        case ESP_SLEEP_WAKEUP_EXT0: return REASON_EXT0;
                        case ESP_SLEEP_WAKEUP_EXT1: return REASON_EXT1;
                        case ESP_SLEEP_WAKEUP_TIMER: return REASON_TIMER;
                        case ESP_SLEEP_WAKEUP_TOUCHPAD: return REASON_TOUCHPAD;
                        case ESP_SLEEP_WAKEUP_ULP: return REASON_ULP;
                        case ESP_SLEEP_WAKEUP_GPIO: return REASON_GPIO;
                        case ESP_SLEEP_WAKEUP_UART: return REASON_UART;
                        case ESP_SLEEP_WAKEUP_WIFI: return REASON_WIFI;
                        case ESP_SLEEP_WAKEUP_COCPU: return REASON_COCPU;
                        case ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG: return REASON_COCPU_TRAP_TRIG;
                        case ESP_SLEEP_WAKEUP_BT: return REASON_BT;
                        default: break;
                    }
#endif
                    return REASON_UNDEFINED;
                }

                const char* to_string(reason_t reason)
                {
                    switch (reason)
                    {
                        case REASON_EXT0: return "Wakeup caused by external signal using RTC_IO";
                        case REASON_EXT1: return "Wakeup caused by external signal using RTC_CNTL";
                        case REASON_TIMER: return "Wakeup caused by timer";
                        case REASON_TOUCHPAD: return "Wakeup caused by touchpad";
                        case REASON_ULP: return "Wakeup caused by ULP program";
                        case REASON_GPIO: return "Wakeup caused by GPIO (light sleep only)";
                        case REASON_UART: return "Wakeup caused by UART (light sleep only)";
                        case REASON_WIFI: return "Wakeup caused by WIFI (light sleep only)";
                        case REASON_COCPU: return "Wakeup caused by COCPU int";
                        case REASON_COCPU_TRAP_TRIG: return "Wakeup caused by COCPU crash";
                        case REASON_BT: return "Wakeup caused by BT (light sleep only)";
                        case REASON_UNDEFINED: break;
                        default: break;
                    }
                    return "Wakeup was not caused by deep sleep";
                }

            }  // namespace nwakeup

            void snooze(u32 seconds)  // start deep sleep with a timer wakeup
            {
#ifdef TARGET_ESP32
                esp_sleep_enable_timer_wakeup((uint64_t)seconds * 1000000);
                esp_deep_sleep_start();
#else
                // For non-ESP32 platforms, we can just simulate deep sleep by halting execution
#endif
            }

        }  // namespace ndeepsleep
    }  // namespace nsystem
}  // namespace ncore
