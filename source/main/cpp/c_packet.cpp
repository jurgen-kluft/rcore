#include "rcore/c_packet.h"

namespace ncore
{
    namespace npacket
    {
        const u8 c_packet_version = 1;

        static void  packet_begin(packet_t& pkt);           // User has to fill in MAC address manually
        static void* packet_alloc(packet_t& pkt, u32 len);  // Allocate raw data in the packet (returns pointer to the start of the data in the packet)
        static s32   packet_finalize(packet_t& pkt);        // Finalize the packet and return the size of the body (excluding the header)

        void image_block_t::begin(packet_t* packet, image_descr_t const& descr)
        {
            packet_begin(*packet);                                                         // Initialize the packet with the provided MAC address
            m_header                = (header_t*)packet_alloc(*packet, sizeof(header_t));  // Write the block header to the packet
            m_header->m_id          = BLOCK_ID_IMAGE;                                      // Block ID for image data
            m_header->m_image_descr = descr;                                               // Copy the image descriptor information
        }

        void image_block_t::write(packet_t* packet, u8 const* data, u32 len)
        {
            u8* ptr = (u8*)packet_alloc(*packet, len);   // Allocate space for the image data block
            for (u32 i = 0; i < len; i++)                //
                ptr[i] = data[i];                        // Copy the image data to the packet
            m_header->m_image_descr.m_data_size += len;  // Increment the total size of the image data in this block
        }

        s32 image_block_t::finalize(packet_t* packet)
        {
            return packet_finalize(*packet);  // Finalize the packet and return size of the body (excluding the header)
        }

        void sensor_block_t::begin(packet_t* packet)
        {
            packet_begin(*packet);                                                          // Initialize the packet with the provided MAC address
            m_header                 = (header_t*)packet_alloc(*packet, sizeof(header_t));  // Write the block header to the packet
            m_header->m_id           = BLOCK_ID_SENSOR;                                     // ID for sensor block
            m_header->m_sensor_count = 0;                                                   // Initialize sensor count to 0
        }

        void sensor_block_t::write(packet_t* packet, sensor_value_t const& sensor)
        {
            u8* ptr = (u8*)packet_alloc(*packet, sizeof(sensor.m_id) + sizeof(sensor.m_value));  // Allocate space for the sensor ID and value
            ptr[0]  = sensor.m_id;                                                               // Write the sensor ID to the packet
            ptr[1]  = (u8)(sensor.m_value >> 8);                                                 // Write the high byte of the sensor value to the packet
            ptr[2]  = (u8)(sensor.m_value & 0xFF);                                               // Write the low byte of the sensor value to the packet
            m_header->m_sensor_count++;                                                          // Increment the sensor count
        }

        s32 sensor_block_t::finalize(packet_t* packet)
        {
            packet_finalize(*packet);         // Finalize the packet and return size of the body (excluding the header)
            return m_header->m_sensor_count;  // Return the number of sensor values in this block
        }

        void packet_begin(packet_t& pkt)
        {
            pkt.Size             = 0;                     //
            pkt.Capacity         = sizeof(pkt.Data);      // Maximum size of the packet
            pkt.Data[pkt.Size++] = 0;                     // Placeholder for length (will be set in finalize)
            pkt.Data[pkt.Size++] = 0;                     // Placeholder for length (will be set in finalize)
            pkt.Size             = packet_t::HeaderSize;  // Set size to header size, user has to fill in MAC address manually
        }

        void packet_set_mac(packet_t& pkt, u8 const* mac)
        {
            for (s32 i = 0; i < 6; i++)
                pkt.Data[packet_t::MacOffset + i] = mac[i];  // MAC address
        }

        void* packet_alloc(packet_t& pkt, u32 len)
        {
            void* ptr = &pkt.Data[pkt.Size];  // Pointer to the start of the data in the packet
            pkt.Size += len;                  // Increment the size of the packet by the length of the data
            return ptr;
        }

        s32 packet_finalize(packet_t& pkt)
        {
            if ((pkt.Size & 0x1) == 1)
                pkt.Data[pkt.Size++] = 0;                              // Padding to align packet size to 2 bytes
            pkt.Data[packet_t::LengthOffset] = (u8)(pkt.Size >> 8);    // Set the length (number of words) of the packet
            pkt.Data[packet_t::LengthOffset] = (u8)(pkt.Size & 0xFF);  // Set the length (number of words) of the packet
            return pkt.Size - packet_t::HeaderSize;                    // Return the size of the body (excluding the header)
        }

    }  // namespace npacket
}  // namespace ncore