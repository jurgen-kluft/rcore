#ifndef __ARDUINO_CORE_STATE_H__
#define __ARDUINO_CORE_STATE_H__
#include "rcore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

#include "rcore/c_network.secret.h"

namespace ncore
{
    struct state_wifi_t;
    struct state_tcp_t;
    struct state_udp_t;
    struct state_node_t;

    struct state_t
    {
        enum
        {
            FLAG_PSRAM = 0x00000001,
        };

        bool has_psram() const { return (Flags & FLAG_PSRAM) != 0; }

        void reset()
        {
            WiFiSSID     = nullptr;
            WiFiPassword = nullptr;
            for (u32 i = 0; i < 6; ++i)
                MACAddress[i] = 0;
            Flags         = 0;
            ServerTcpPort = 0;
            ServerUdpPort = 0;
            ServerIP      = 0;
            TimeMs        = 0;
            WiFi          = nullptr;
            Tcp           = nullptr;
            Udp           = nullptr;
            Node          = nullptr;
        }

        const char*   WiFiSSID;
        const char*   WiFiPassword;
        u8            MACAddress[6];
        u16           Flags;
        u16           ServerTcpPort;
        u16           ServerUdpPort;
        u32           ServerIP;
        u64           TimeMs;
        state_wifi_t* WiFi;
        state_tcp_t*  Tcp;
        state_udp_t*  Udp;
        state_node_t* Node;
    };

}  // namespace ncore

#endif  // __ARDUINO_CORE_STATE_H__
