#include "rcore/c_log.h"
#include "rcore/c_str.h"
#include "ccore/c_printf.h"

#ifdef TARGET_ARDUINO
#    include "Arduino.h"
#    include "rcore/c_logC.h"

namespace ncore
{
    namespace nlog
    {
        static nlevel::value_t gLogLevel = nlevel::All;

        void               set_level(nlevel::value_t level) { gLogLevel = level; }
        static inline bool is_level_active(nlevel::value_t level) { return (gLogLevel & level) != 0; }

        void flush(str_t& str)
        {
            if (str.m_end > 0 && str.m_ascii != nullptr)
            {
                str.m_ascii[str.m_end] = 0;
                str.m_ascii[str.m_eos] = 0;
                log_i("[%s] %s", "LOG", str.m_ascii);
                str.m_ascii[0] = 0;
                str.m_end      = 0;
            }
        }

        void log_fatal(const char* tag, const char* msg)
        {
            if (is_level_active(nlevel::Fatal) && msg != nullptr)
            {
                log_e("[%s] %s", tag, msg);
            }
        }

        void log_fatalf(const char* tag, const char* msg, va_list_t valist)
        {
            if (is_level_active(nlevel::Fatal) && msg != nullptr)
            {
                char str[256];
                str[0]               = 0;
                str[sizeof(str) - 1] = 0;
                const size_t n       = sizeof(str) - 1;
                const s32    len     = ncore::snprintf_(str, n, msg, valist.argv(), (i32)valist.argc());
                if (len < 0)
                {
                    LOG_ERROR("LOG", "Error formatting string");
                    return;
                }
                log_e("[%s] %s", tag, str);
            }
            return;
        }

        void log_error(const char* tag, const char* msg)
        {
            if (is_level_active(nlevel::Error) && msg != nullptr)
            {
                log_e("[%s] %s", tag, msg);
            }
        }

        void log_errorf(const char* tag, const char* msg, va_list_t valist)
        {
            if (is_level_active(nlevel::Error) && msg != nullptr)
            {
                char str[256];
                str[0]               = 0;
                str[sizeof(str) - 1] = 0;
                const size_t n       = sizeof(str) - 1;
                const s32    len     = ncore::snprintf_(str, n, msg, valist.argv(), (i32)valist.argc());
                if (len < 0)
                {
                    LOG_ERROR("LOG", "Error formatting string");
                    return;
                }

                log_e("[%s] %s", tag, str);
            }
            return;
        }

        void log_warn(const char* tag, const char* msg)
        {
            if (is_level_active(nlevel::Warn) && msg != nullptr)
            {
                log_w("[%s] %s", tag, msg);
            }
        }

        void log_warnf(const char* tag, const char* msg, va_list_t valist)
        {
            if (is_level_active(nlevel::Warn) && msg != nullptr)
            {
                char str[256];
                str[0]               = 0;
                str[sizeof(str) - 1] = 0;
                const size_t n       = sizeof(str) - 1;
                const s32    len     = ncore::snprintf_(str, n, msg, valist.argv(), (i32)valist.argc());
                if (len < 0)
                {
                    LOG_WARNING("LOG", "Error formatting string");
                    return;
                }

                log_w("[%s] %s", tag, str);
            }
        }

        void log_info(const char* tag, const char* msg)
        {
            if (is_level_active(nlevel::Info) && msg != nullptr)
            {
                log_i("[%s] %s", tag, msg);
            }
        }

        void log_infof(const char* tag, const char* msg, va_list_t valist)
        {
            if (is_level_active(nlevel::Info) && msg != nullptr)
            {
                char str[256];
                str[0]               = 0;
                str[sizeof(str) - 1] = 0;
                const size_t n       = sizeof(str) - 1;
                const s32    len     = ncore::snprintf_(str, n, msg, valist.argv(), (i32)valist.argc());
                if (len < 0)
                {
                    LOG_ERROR("LOG", "Error formatting string");
                    return;
                }

                log_i("[%s] %s", tag, str);
            }
        }

        void log_debug(const char* tag, const char* msg)
        {
            if (is_level_active(nlevel::Debug) && msg != nullptr)
            {
                log_d("[%s] %s", tag, msg);
            }
        }

        void log_debugf(const char* tag, const char* msg, va_list_t valist)
        {
            if (is_level_active(nlevel::Debug) && msg != nullptr)
            {
                char str[256];
                str[0]               = 0;
                str[sizeof(str) - 1] = 0;
                const size_t n       = sizeof(str) - 1;
                const s32    len     = ncore::snprintf_(str, n, msg, valist.argv(), (i32)valist.argc());
                if (len < 0)
                {
                    LOG_ERROR("LOG", "Error formatting string");
                    return;
                }

                log_d("[%s] %s", tag, str);
            }
        }

        void log_trace(const char* tag, const char* msg)
        {
            if (is_level_active(nlevel::Trace) && msg != nullptr)
            {
                log_v("[%s] %s", tag, msg);
            }
        }

        void log_tracef(const char* tag, const char* msg, va_list_t valist)
        {
            if (is_level_active(nlevel::Trace) && msg != nullptr)
            {
                char str[256];
                str[0]               = 0;
                str[sizeof(str) - 1] = 0;
                const size_t n       = sizeof(str) - 1;
                const s32    len     = ncore::snprintf_(str, n, msg, valist.argv(), (i32)valist.argc());
                if (len < 0)
                {
                    LOG_ERROR("LOG", "Error formatting string");
                    return;
                }

                log_v("[%s] %s", tag, str);
            }
        }

        void print(const char* msg)
        {
            if (msg != nullptr)
                log_i("[%s] %s", "LOG", msg);
        }

        void println(const char* msg)
        {
            if (msg != nullptr)
                log_i("[%s] %s", "LOG", msg);
        }

        void println() { log_i("[%s] %s", "LOG", ""); }

        void print_ip(const u8* ip)
        {
            if (ip != nullptr)
            {
                char str_buffer[128];
                str_buffer[0]                      = 0;
                str_buffer[sizeof(str_buffer) - 1] = 0;
                str_t str                          = {str_buffer, str_buffer, 0, 0, (s16)sizeof(str_buffer) - 1};
                for (i32 i = 0; i < 4; ++i)
                {
                    if (i > 0)
                        str_append(str, ".");
                    to_str(str, (byte)ip[i], 10);
                }
                flush(str);
            }
        }

        void print_mac(const u8* mac)
        {
            if (mac != NULL)
            {
                char str_buffer[128];
                str_buffer[0]                      = 0;
                str_buffer[sizeof(str_buffer) - 1] = 0;
                str_t str                          = {str_buffer, str_buffer, 0, 0, (s16)sizeof(str_buffer) - 1};
                for (i32 i = 0; i < 6; ++i)
                {
                    if (i > 0)
                        str_append(str, ":");
                    to_str(str, (byte)mac[i], 2, 16);
                }
                flush(str);
            }
        }

        void __printf(const char* format, const va_t* args, i32 argc)
        {
            char str[256];
            str[0]               = 0;
            str[sizeof(str) - 1] = 0;
            const size_t n       = sizeof(str) - 1;
            const s32    len     = ncore::snprintf_(str, n, format, args, argc);
            if (len < 0)
            {
                //Serial.println("[LOG] Error formatting string");
                log_e("[%s] %s", "LOG", "Error formatting string");
                return;
            }
            log_i("[%s] %s", "LOG", str);
            return;
        }

    }  // namespace nlog

}  // namespace ncore

#else

namespace ncore
{
    namespace nlog
    {
        void set_level(nlevel::value_t level) { CC_UNUSED(level); }
        void print(const char* msg) { CC_UNUSED(msg); }
        void println(const char* msg) { CC_UNUSED(msg); }
        void println() {}

        void __printf(const char* format, const va_t* args, i32 argc)
        {
            CC_UNUSED(format);
            CC_UNUSED(args);
            CC_UNUSED(argc);
        }

        void log_fatal(const char* tag, const char* msg)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
        }
        void log_error(const char* tag, const char* msg)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
        }
        void log_warn(const char* tag, const char* msg)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
        }
        void log_info(const char* tag, const char* msg)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
        }
        void log_debug(const char* tag, const char* msg)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
        }
        void log_trace(const char* tag, const char* msg)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
        }

        void log_fatalf(const char* tag, const char* msg, va_list_t valist)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
            CC_UNUSED(valist);
        }
        void log_errorf(const char* tag, const char* msg, va_list_t valist)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
            CC_UNUSED(valist);
        }
        void log_warnf(const char* tag, const char* msg, va_list_t valist)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
            CC_UNUSED(valist);
        }
        void log_infof(const char* tag, const char* msg, va_list_t valist)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
            CC_UNUSED(valist);
        }
        void log_debugf(const char* tag, const char* msg, va_list_t valist)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
            CC_UNUSED(valist);
        }
        void log_tracef(const char* tag, const char* msg, va_list_t valist)
        {
            CC_UNUSED(tag);
            CC_UNUSED(msg);
            CC_UNUSED(valist);
        }

        // Mac
        void print_mac(const u8* mac) { CC_UNUSED(mac); }

    }  // namespace nlog

}  // namespace ncore

#endif
