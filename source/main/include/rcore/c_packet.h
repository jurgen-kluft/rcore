#ifndef __ARDUINO_CORE_PACKET_H__
#define __ARDUINO_CORE_PACKET_H__
#include "rcore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

namespace ncore
{
    namespace npacket
    {
        typedef u16 id_t;
        enum
        {
            ID_UNKNOWN     = 0,   // Unknown
            ID_TEMPERATURE = 1,   // Temperature
            ID_HUMIDITY    = 2,   // Humidity
            ID_PRESSURE    = 3,   // Pressure
            ID_LIGHT       = 4,   // Light
            ID_UV          = 5,   // UV
            ID_CO          = 6,   // Carbon Monoxide
            ID_CO2         = 7,   // Carbon Dioxide
            ID_HCHO        = 8,   // Formaldehyde
            ID_VOC         = 9,   // Volatile Organic Compounds
            ID_NOX         = 10,  // Nitrogen Oxides
            ID_PM005       = 11,  // Particulate Matter 0.5
            ID_PM010       = 12,  // Particulate Matter 1.0
            ID_PM025       = 13,  // Particulate Matter 2.5
            ID_PM040       = 14,  // Particulate Matter 4.0
            ID_PM100       = 15,  // Particulate Matter 10.0
            ID_NOISE       = 16,  // Noise
            ID_VIBRATION   = 17,  // Vibration
            ID_STATE       = 18,  // State
            ID_BATTERY     = 19,  // Battery
            ID_SWITCH1     = 21,  // On/Off, Open/Close (same as ID_SWITCH)
            ID_SWITCH2     = 22,  // On/Off, Open/Close
            ID_SWITCH3     = 23,  // On/Off, Open/Close
            ID_SWITCH4     = 24,  // On/Off, Open/Close
            ID_SWITCH5     = 25,  // On/Off, Open/Close
            ID_SWITCH6     = 26,  // On/Off, Open/Close
            ID_SWITCH7     = 27,  // On/Off, Open/Close
            ID_SWITCH8     = 28,  // On/Off, Open/Close
            ID_SWITCH9     = 29,  // On/Off, Open/Close
            ID_PRESENCE1   = 51,  // Presence1
            ID_PRESENCE2   = 52,  // Presence2
            ID_PRESENCE3   = 53,  // Presence3
            ID_DISTANCE1   = 54,  // Distance1
            ID_DISTANCE2   = 55,  // Distance2
            ID_DISTANCE3   = 56,  // Distance3
            ID_PX          = 57,  // X
            ID_PY          = 58,  // Y
            ID_PZ          = 59,  // Z
            ID_RSSI        = 60,  // RSSI
            ID_PERF1       = 61,  // Performance Metric 1
            ID_PERF2       = 62,  // Performance Metric 2
            ID_PERF3       = 63,  // Performance Metric 3
            ID_VOLTAGE     = 65,  // Voltage
            ID_CURRENT     = 66,  // Current
            ID_POWER       = 67,  // Power
            ID_ENERGY      = 68,  // Energy
            ID_SENSOR      = 69,  // Sensor Data (generic)
            ID_JSON        = 70,  // JSON Data
            ID_IMAGE       = 71,  // Image Data
            ID_GAS_M3      = 72,  // Gas Meter
            ID_WATER_M3    = 73,  // Water Meter
            ID_kWAh        = 74,  // Electric Meter (kilowatt-hours)
            ID_COUNT,             // The maximum number of ID (highest index + 1)
        };

        struct packet_t
        {
            byte Data[1024 + 256];
            u16  Size;
            u16  Capacity;
        };

        void packet_init(packet_t& pkt);
        void packet_write(packet_t& pkt, id_t id, u8 const* mac, u16 value);
        void packet_write(packet_t& pkt, id_t id, u8 const* mac, u8 const* data, u16 data_len);

        // Example:
        //    packet_t pkt;
        //    packet_init(pkt);
        //    u8 mac[6] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
        //    packet_write(pkt, ID_TEMPERATURE, mac, 25);  // Write a temperature value of 25
        //    packet_write(pkt, ID_PRESSURE, mac, 1013);    // Write a pressure value of 1013
        //    packet_write(pkt, ID_HUMIDITY, mac, 60);      // Write a humidity value of 60
        //    
        //    send_udp(pkt.Data, pkt.Size);  // Send the packet over UDP
        // 

        // The format of an image part received over the wire
        // Image data due to its size is split into many packets/parts for transmission
        // Max size of image data in a part is 1024 bytes
        struct image_descr_t
        {
            unsigned char  m_type;         // 0 = JPEG, 1 = PNG
            unsigned char  m_bpp;          // Bits per pixel
            unsigned short m_width;        // Width in pixels
            unsigned short m_height;       // Height in pixels
            unsigned short m_padding;      // Padding to align to 4 bytes
            unsigned int   m_block_count;  // The number of blocks for this image
            unsigned int   m_block_index;  // The index of this block
            unsigned int   m_data_offset;  // The offset of this block in the full image data
            unsigned int   m_data_size;    // The size of this image data block
            unsigned int   m_total_size;   // The total size of the image data
        };

        void packet_write(packet_t& pkt, id_t id, u8 const* mac, image_descr_t const& descr, u8 const* image_data, u16 data_len);

    }  // namespace npacket
}  // namespace ncore

#endif  // __ARDUINO_CORE_PACKET_H__
