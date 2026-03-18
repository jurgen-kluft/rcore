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
        typedef u8    state_t;
        const state_t Off   = 0x10;
        const state_t On    = 0x20;
        const state_t Error = 0x30;

        enum eblock_id
        {
            BLOCK_ID_UNKNOWN = 0,  // Unknown block type
            BLOCK_ID_SENSOR  = 1,  // Sensor data block
            BLOCK_ID_IMAGE   = 2,  // Image data block
            BLOCK_ID_JSON    = 3,  // JSON Data
        };

        // The format of an image block received over the wire
        // Image data is split into many packets for transmission
        // Max size of image data in a block is 1024 bytes
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

        struct packet_t;

        struct image_block_t
        {
            struct header_t
            {
                unsigned char m_id;           // ID_IMAGE
                image_descr_t m_image_descr;  // The image block header descriptor
            };
            header_t* m_header;  // Pointer to the block header in the packet data

            void begin(packet_t* packet, image_descr_t const& info);  //
            void write(packet_t* packet, u8 const* data, u32 len);    // Write a block of data
            s32  finalize(packet_t* packet);                          // Finalize the block by writing the length and returning the total size of the block
        };

        struct sensor_value_t;

        struct sensor_block_t
        {
            typedef u8 id_t;
            enum
            {
                ID_UNKNOWN           = 0,   // Unknown
                ID_TEMPERATURE       = 1,   // Temperature
                ID_HUMIDITY          = 2,   // Humidity
                ID_PRESSURE          = 3,   // Pressure
                ID_LIGHT             = 4,   // Light
                ID_UV                = 5,   // UV
                ID_CO                = 6,   // Carbon Monoxide
                ID_CO2               = 7,   // Carbon Dioxide
                ID_HCHO              = 8,   // Formaldehyde
                ID_VOC               = 9,   // Volatile Organic Compounds
                ID_NOX               = 10,  // Nitrogen Oxides
                ID_PM005             = 11,  // Particulate Matter 0.5
                ID_PM010             = 12,  // Particulate Matter 1.0
                ID_PM025             = 13,  // Particulate Matter 2.5
                ID_PM040             = 14,  // Particulate Matter 4.0
                ID_PM100             = 15,  // Particulate Matter 10.0
                ID_NOISE             = 16,  // Noise
                ID_VIBRATION         = 17,  // Vibration
                ID_STATE             = 18,  // State
                ID_BATTERY           = 19,  // Battery
                ID_SWITCH1           = 21,  // On/Off, Open/Close (same as ID_SWITCH)
                ID_SWITCH2           = 22,  // On/Off, Open/Close
                ID_SWITCH3           = 23,  // On/Off, Open/Close
                ID_SWITCH4           = 24,  // On/Off, Open/Close
                ID_SWITCH5           = 25,  // On/Off, Open/Close
                ID_SWITCH6           = 26,  // On/Off, Open/Close
                ID_SWITCH7           = 27,  // On/Off, Open/Close
                ID_SWITCH8           = 28,  // On/Off, Open/Close
                ID_PRESENCE1         = 31,  // Presence1
                ID_PRESENCE2         = 32,  // Presence2
                ID_PRESENCE3         = 33,  // Presence3
                ID_DISTANCE1         = 34,  // Distance1
                ID_DISTANCE2         = 35,  // Distance2
                ID_DISTANCE3         = 36,  // Distance3
                ID_PX                = 37,  // X
                ID_PY                = 38,  // Y
                ID_PZ                = 39,  // Z
                ID_RSSI              = 40,  // RSSI
                ID_PERF1             = 41,  // Performance Metric 1
                ID_PERF2             = 42,  // Performance Metric 2
                ID_PERF3             = 43,  // Performance Metric 3
                ID_VOLTAGE           = 45,  // Voltage
                ID_CURRENT           = 46,  // Current
                ID_POWER             = 47,  // Power
                ID_ENERGY            = 48,  // Energy
                ID_GAS_METER         = 52,  // Gas Meter
                ID_WATER_METER       = 53,  // Water Meter
                ID_ELECTRICITY_METER = 54,  // Electric Meter
                ID_SENSORCOUNT,             // The maximum number of sensor types (highest index + 1)
            };

            struct header_t
            {
                u8 m_id;            // ID_SENSOR
                u8 m_sensor_count;  // The total number of sensor values in this block
            };
            header_t* m_header;  // The block header

            void begin(packet_t* packet);                               //
            void write(packet_t* packet, sensor_value_t const& value);  // Write a sensor value
            s32  finalize(packet_t* packet);                            // Finalize the block by writing the length and return the number of sensor values in this block
        };

        struct sensor_value_t
        {
            sensor_block_t::id_t m_id;     // Sensor ID
            u16                  m_value;  // Sensor value
        };

        struct packet_t
        {
            byte Data[1024 + 256 - 4];
            u16  Size;
            u16  Capacity;
            enum
            {                          // Packet header
                HeaderSize   = 2 + 6,  // length, mac
                LengthOffset = 0,
                MacOffset    = 2,
                BlockOffset  = 8,
            };
        };

        void packet_set_mac(packet_t& pkt, u8 const* mac);

    }  // namespace npacket
}  // namespace ncore

#endif  // __ARDUINO_CORE_PACKET_H__
