#include "rcore/c_eeprom.h"
#include "rcore/c_serial.h"
#include "ccore/c_memory.h"

#ifdef TARGET_ARDUINO

#    include "Arduino.h"
#    include "EEPROM.h"

namespace ncore
{
    namespace neeprom
    {
        // CRC32 implementation based on the FNV-1a hash algorithm, which 
        // is simple and efficient for small data sizes.
        u32 crc32(const byte* data, s32 length)
        {
            u32 hash = 2166136261U;  // FNV offset basis
            for (s32 i = 0; i < length; i++)
            {
                hash ^= data[i];    // XOR the byte first (the "1a" variation)
                hash *= 16777619U;  // Multiply by the FNV prime
            }
            return hash;
        }

        void save(byte const* data, s32 size)
        {
            EEPROM.begin(size);
            for (s32 i = 0; i < size; i++)
                EEPROM.write(i, data[i]);
            EEPROM.commit();
            EEPROM.end();
        }

        bool load(byte* data, s32 size)
        {
            EEPROM.begin(size);
            for (s32 i = 0; i < size; i++)
                data[i] = EEPROM.read(i);
            EEPROM.end();
            return true;
        }

    }  // namespace neeprom
}  // namespace ncore

#else

namespace ncore
{
    namespace neeprom
    {
        u32  crc32(const byte* data, s32 length) { return 0; }
        bool load(byte* data, s32 size) { return false; }
        void save(byte const* data, s32 size) {}

    }  // namespace neeprom
}  // namespace ncore

#endif
