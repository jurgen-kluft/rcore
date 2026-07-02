#include "rcore/c_str.h"
#include "rcore/c_system.h"
#include "ccore/c_memory.h"

#ifdef TARGET_ARDUINO
#    include "Arduino.h"
#    ifdef TARGET_ESP32
#        include "esp32-hal-psram.h"
#    endif
#else
#    include <unistd.h>
#    include <sys/mman.h>
#endif

namespace ncore
{
    namespace nsystem
    {
        // get a unique ID for this device (e.g. chip ID or MAC address)
        void get_unique_id(str_t& str)
        {
#ifdef TARGET_ESP32
            // For ESP32, we can use the MAC address as a unique ID
            uint64_t chipid = ESP.getEfuseMac();
#else
#    ifdef TARGET_ESP8266
            uint64_t chipid = ESP.getChipId();
            chipid <<= 24;
            chipid |= ESP.getFlashChipId();
#    else
            // For non-ESP32 platforms, we can use a placeholder unique ID
            u64 chipid = 0x123456789ABC;  // Placeholder unique ID
#    endif
#endif
            to_str(str, (u32)(chipid >> 16), 16);
            to_str(str, (u32)(chipid & 0xFFFF), 16);
        }

        void* malloc(u32 size)
        {
#ifdef TARGET_ARDUINO
            return ::malloc(size);
#else
            // standard C++ malloc
            return ::malloc(size);
#endif
        }

        void* calloc(u32 size)
        {
            void* ptr = malloc(size);
            if (ptr)
            {
                g_memclr(ptr, size);
            }
            return ptr;
        }

        void free(void* ptr)
        {
#ifdef TARGET_ARDUINO
            ::free(ptr);
#else
            // standard C++ free
            ::free(ptr);
#endif
        }

        s32 free_heap()
        {
#ifdef TARGET_ARDUINO
            return (s32)ESP.getFreeHeap();
#else
            // standard C++ free heap size
            return (s32)(0);  // Placeholder for non-ESP32 platforms
#endif
        }

        bool init_psram()
        {
#ifdef TARGET_ESP32
            return psramInit();
#else
            return true;
#endif
        }

        bool has_psram()
        {
#ifdef TARGET_ESP32
            return psramFound();
#else
            return false;
#endif
        }

        s32 total_psram()
        {
#ifdef TARGET_ESP32
            return (s32)ESP.getPsramSize();
#else
            return (s32)(0);  // Assume 0 for non-ESP32 platforms
#endif
        }
        s32 free_psram()
        {
#ifdef TARGET_ESP32
            return (s32)ESP.getFreePsram();
#else
            return (s32)(0);  // Assume 0 for non-ESP32 platforms
#endif
        }

        byte* alloc_psram(u32 size)
        {
#ifdef TARGET_ESP32
            return (byte*)heap_caps_aligned_alloc(16, size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
#else
            return nullptr;  // PSRAM not available on non-ESP32 platforms
#endif
        }

        byte* alloc_psram_aligned(u32 size, u32 alignment)
        {
#ifdef TARGET_ESP32
            return (byte*)heap_caps_aligned_alloc(alignment, size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
#else
            return nullptr;  // PSRAM not available on non-ESP32 platforms
#endif
        }

        void dealloc_psram(byte* ptr)
        {
#ifdef TARGET_ESP32
            heap_caps_aligned_free(ptr);
#endif
        }

    }  // namespace nsystem
}  // namespace ncore
