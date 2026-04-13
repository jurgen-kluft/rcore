#include "rcore/c_packet.h"

namespace ncore
{
    namespace npacket
    {
        void packet_init(packet_t& pkt)
        {
            pkt.Size     = 0;
            pkt.Capacity = sizeof(pkt.Data);
        }

        // A Value is structured as:
        // - 2 bytes for the ID
        // - 6 bytes for the MAC address
        // - 2 bytes for the data length
        // - N bytes for the data (N is the data length)

        void packet_write_u16(packet_t& pkt, u16 value)
        {
            if (pkt.Size + 2 > pkt.Capacity)
                return;  // Not enough space in packet
            // Write in little-endian format
            pkt.Data[pkt.Size++] = value & 0xFF;
            pkt.Data[pkt.Size++] = (value >> 8) & 0xFF;
        }

        void packet_write_bytes(packet_t& pkt, u8 const* data, u16 data_len)
        {
            if (pkt.Size + data_len > pkt.Capacity)
                return;  // Not enough space in packet
            for (int i = 0; i < data_len; i++)
                pkt.Data[pkt.Size++] = data[i];
        }

        void packet_write_value(packet_t& pkt, u16 value)
        {
            packet_write_u16(pkt, 2);
            packet_write_u16(pkt, value);
        }

        void packet_write_value(packet_t& pkt, u8 const* data, u16 data_len)
        {
            if (pkt.Size + 2 + data_len > pkt.Capacity)
                return;  // Not enough space in packet
            packet_write_u16(pkt, data_len);
            packet_write_bytes(pkt, data, data_len);
        }

        void packet_write(packet_t& pkt, id_t id, u8 const* mac, u16 value)
        {
            if (pkt.Size + 2 + 6 + 2 + 2 > pkt.Capacity)
                return;  // Not enough space in packet
            packet_write_u16(pkt, id);
            packet_write_bytes(pkt, mac, 6);
            packet_write_value(pkt, value);
        }

        void packet_write(packet_t& pkt, id_t id, u8 const* mac, u8 const* data, u16 data_len)
        {
            if (pkt.Size + 2 + 6 + 2 + data_len > pkt.Capacity)
                return;  // Not enough space in packet
            packet_write_u16(pkt, id);
            packet_write_bytes(pkt, mac, 6);
            packet_write_value(pkt, data, data_len);
        }

        void packet_write(packet_t& pkt, id_t id, u8 const* mac, image_descr_t const& descr, u8 const* image_data, u16 data_len)
        {
            if (pkt.Size + 2 + 6 + 2 + sizeof(image_descr_t) + data_len > pkt.Capacity)
                return;  // Not enough space in packet
            packet_write_u16(pkt, id);
            packet_write_bytes(pkt, mac, 6);
            packet_write_u16(pkt, sizeof(image_descr_t) + data_len);
            packet_write_bytes(pkt, (u8 const*)&descr, sizeof(image_descr_t));
            packet_write_bytes(pkt, image_data, data_len);
        }
    }  // namespace npacket
}  // namespace ncore