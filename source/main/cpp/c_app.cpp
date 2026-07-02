#include "rcore/c_target.h"
#include "rcore/c_system.h"
#include "rcore/c_eeprom.h"
#include "rcore/c_log.h"
#include "rcore/c_serial.h"
#include "rcore/c_timer.h"
#include "rcore/c_app.h"
#include "rcore/c_deepsleep.h"

#ifdef TARGET_ARDUINO

namespace ncore
{
    static state_t gState;
};  // namespace ncore

#    include "Arduino.h"

void setup()
{
    ncore::gState.reset();

    ncore::gState.WiFiSSID            = ncore::WIFI_SSID();
    ncore::gState.WiFiPassword        = ncore::WIFI_PASSWORD();
    ncore::gState.SensorServerIP      = ncore::SENSOR_SERVER_IP();
    ncore::gState.SensorServerTcpPort = ncore::SENSOR_SERVER_TCPPORT();
    ncore::gState.SensorServerUdpPort = ncore::SENSOR_SERVER_UDPPORT();
    ncore::napp::wakeup(&ncore::gState, ncore::nwakeup::reason());

#    ifdef TARGET_ESP8266
    ncore::nserial::begin(ncore::nbaud::Rate74880);  // Initialize serial communication at 74880 baud
#    else
    ncore::nserial::begin(ncore::nbaud::Rate115200);  // Initialize serial communication at 115200 baud
#    endif

    ncore::nlog::log_info("setup", "started...");

#    ifdef TARGET_ESP32
    if (ncore::nsystem::has_psram())
    {
        ncore::nlog::log_info("setup", "PSRAM available.");
        if (ncore::nsystem::init_psram())
        {
            ncore::nlog::log_info("setup", "PSRAM initialized successfully.");

            ncore::gState.Flags |= ncore::state_t::FLAG_PSRAM;
            const ncore::u32 psram_size = ncore::nsystem::total_psram();
            const ncore::u32 free_psram = ncore::nsystem::free_psram();
            ncore::nlog::log_infof("setup", "PSRAM Size: %u Kbytes with %u Kbytes free.", ncore::va_list_t(ncore::va_t(psram_size >> 10), ncore::va_t(free_psram >> 10)));
        }
        else
        {
            ncore::nlog::log_info("setup", "PSRAM initialization failed.");
        }
    }
    else
    {
        ncore::nlog::log_info("setup", "PSRAM not available.");
    }
#    endif

    const ncore::u32 free_memory = ncore::nsystem::free_heap();
    ncore::nlog::log_infof("setup", "Free heap memory: %u Kbytes", ncore::va_list_t(ncore::va_t(free_memory >> 10)));

    ncore::gState.TimeMs = ncore::ntimer::millis();
    ncore::napp::setup(&ncore::gState);

    ncore::nlog::log_info("setup", "done...");
}

void loop()
{
    ncore::gState.TimeMs = ncore::ntimer::millis();
    ncore::napp::tick(&ncore::gState);
}

#endif
