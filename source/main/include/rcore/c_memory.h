#ifndef __ARDUINO_CORE_MEMORY_H__
#define __ARDUINO_CORE_MEMORY_H__
#include "rcore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

#if defined(TARGET_ARDUINO)

#    include "Arduino.h"

namespace ncore
{
    namespace nmem
    {
        static inline void *memcpy(void *dst0, const void *src0, int_t length) { return ::memcpy(dst0, src0, length); }
        static inline void *memset(void *dest, u32 c, int_t n) { return ::memset(dest, c, n); }
        static inline void *memmove(void *inDest, const void *inSrc, int_t inLength) { return ::memmove(inDest, inSrc, inLength); }
        static inline s32   memcmp(const void *p1, const void *p2, int_t inLength) { return ::memcmp(p1, p2, inLength); }

        static inline void memswap(void *inLHS, void *inRHS, int_t inLength)
        {
            // Simple byte-wise swap
            u8 *lhs = (u8 *)inLHS;
            u8 *rhs = (u8 *)inRHS;
            for (int_t i = 0; i < inLength; ++i)
            {
                u8 temp = lhs[i];
                lhs[i]  = rhs[i];
                rhs[i]  = temp;
            }
            return inLHS;
        }
    }  // namespace nmem
}  // namespace ncore

#endif

#include "ccore/c_memory.h"

#endif