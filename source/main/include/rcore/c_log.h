#ifndef __RCORE_LOG_H__
#define __RCORE_LOG_H__
#include "rcore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

#include "ccore/c_va_list.h"

namespace ncore
{
    namespace nlog
    {
        namespace nlevel
        {
            typedef u8 value_t;

            const value_t Off   = 0;
            const value_t Fatal = 1;
            const value_t Error = 2;
            const value_t Warn  = 4;
            const value_t Info  = 8;
            const value_t Debug = 16;
            const value_t Trace = 32;
            const value_t All   = Fatal | Error | Warn | Info | Debug | Trace;
        }  // namespace nlevel

        void set_level(nlevel::value_t level);

        void print(const char* msg);
        void println(const char* msg);
        void println();

        void log_fatal(const char* tag, const char* msg);
        void log_fatalf(const char* tag, const char* msg, va_list_t valist);
        void log_error(const char* tag, const char* msg);
        void log_errorf(const char* tag, const char* msg, va_list_t valist);
        void log_warn(const char* tag, const char* msg);
        void log_warnf(const char* tag, const char* msg, va_list_t valist);
        void log_info(const char* tag, const char* msg);
        void log_infof(const char* tag, const char* msg, va_list_t valist);
        void log_debug(const char* tag, const char* msg);
        void log_debugf(const char* tag, const char* msg, va_list_t valist);
        void log_trace(const char* tag, const char* msg);
        void log_tracef(const char* tag, const char* msg, va_list_t valist);

        template <typename... Args>
        inline void printv(const char* format, Args&&... _args)
        {
            const char* argv[] = {_args...};
            const i32  argc   = sizeof(argv) / sizeof(argv[0]);
            for (i32 i = 0; i < argc; ++i)
                print(argv[i]);
        }

        template <typename... Args>
        inline void printvln(const char* format, Args&&... _args)
        {
            const char* argv[] = {_args...};
            const i32  argc   = sizeof(argv) / sizeof(argv[0]);
            for (i32 i = 0; i < argc; ++i)
                print(argv[i]);
            println();
        }

        void __printf(const char* format, const va_t* args, i32 argc);
        
        template <typename... Args>
        inline void printf(const char* format, Args&&... _args)
        {
            const va_t argv[] = {_args...};
            const i32  argc   = sizeof(argv) / sizeof(argv[0]);
            __printf(format, argv, argc);
        }
        
        template <typename... Args>
        inline void printfln(const char* format, Args&&... _args)
        {
            const va_t argv[] = {_args...};
            const i32  argc   = sizeof(argv) / sizeof(argv[0]);
            __printf(format, argv, argc);
            println();
        }

        // IP
        void print_ip(const u8* ip);
        inline void println_ip(const u8* ip)
        {
            print_ip(ip);
            println();
        }

        // Mac
        void print_mac(const u8* mac);
        inline void println_mac(const u8* mac)
        {
            print_mac(mac);
            println();
        }

    }  // namespace nlog

}  // namespace ncore

#endif  // __RCORE_LOG_H__
