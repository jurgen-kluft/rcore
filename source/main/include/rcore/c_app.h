#ifndef __ARDUINO_CORE_APP_H__
#define __ARDUINO_CORE_APP_H__
#include "rcore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

#include "rcore/c_state.h"
#include "rcore/c_deepsleep.h"

namespace ncore
{
    namespace napp
    {
        void wakeup(state_t* state, nwakeup::reason_t reason);
        void presetup(state_t* state);
        void setup(state_t* state);
        void tick(state_t* state);
    }  // namespace napp
}  // namespace ncore

#endif  // __ARDUINO_CORE_APP_H__
