#ifndef __RCORE_STATE_H__
#define __RCORE_STATE_H__
#include "rcore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

#include "rcore/c_network.secret.h"

namespace ncore
{
    struct state_t
    {
        enum
        {
            FLAG_PSRAM = 0x00000001,
        };

        bool has_psram() const { return (Flags & FLAG_PSRAM) != 0; }

        void reset()
        {
            Flags               = 0;
            TimeMs              = 0;
        }

        u16           Flags;
        u64           TimeMs;
    };

}  // namespace ncore

#endif  // __RCORE_STATE_H__
