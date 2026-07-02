#ifndef __ARDUINO_CORE_SYSTEM_H__
#define __ARDUINO_CORE_SYSTEM_H__
#include "rcore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

namespace ncore
{
    struct str_t;

    namespace nsystem
    {
        void get_unique_id(str_t& str);  // get a unique ID for this device (e.g. chip ID or MAC address)

        void* malloc(u32 size);  // allocate memory from the heap
        void* calloc(u32 size);  // allocate memory from the heap and initialize it to zero
        void  free(void* ptr);   // free memory allocated from the heap

        template <typename T>
        T* allocate(u32 count = 1)
        { return static_cast<T*>(malloc(sizeof(T) * count)); }

        template <typename T>
        T* callocate(u32 count = 1)
        { return static_cast<T*>(calloc(sizeof(T) * count)); }

        template <typename T>
        void deallocate(T* ptr)
        { free(static_cast<void*>(ptr)); }

        template <typename T>
        T* construct()
        {
            T* ptr = allocate<T>();
            if (ptr)
            {
                return new (ptr) T();
            }
            return ptr;
        }

        s32 free_heap();  // get free heap size in bytes

        bool  init_psram();                                  // initialize PSRAM (if available)
        bool  has_psram();                                   // check if PSRAM is available
        s32   total_psram();                                 // get total PSRAM size in bytes
        s32   free_psram();                                  // get free PSRAM size in bytes
        byte* alloc_psram(u32 size);                         // allocate memory from PSRAM
        byte* alloc_psram_aligned(u32 size, u32 alignment);  // allocate memory from PSRAM
        void  dealloc_psram(byte* ptr);                      // free memory allocated from PSRAM

    }  // namespace nsystem
}  // namespace ncore

#endif  // __ARDUINO_CORE_SYSTEM_H__