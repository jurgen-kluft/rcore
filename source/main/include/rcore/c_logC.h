#ifndef __RCORE_LOG_C_H__
#define __RCORE_LOG_C_H__

#ifdef TARGET_ESP32

#    define LOG_INFO(tag, format, ...)
#    define LOG_WARNING(tag, format, ...)
#    define LOG_DEBUG(tag, format, ...)
#    define LOG_ERROR(tag, format, ...)
#    define LOG_FATAL(tag, format, ...)

#    define ON_ERROR_RETURN(x, log_tag, format, ...)               \
        do                                                         \
        {                                                          \
            esp_err_t err_rc_ = (x);                               \
            if (unlikely(err_rc_ != ESP_OK))                       \
            {                                                      \
                LOG_ERROR("[%s] " format, log_tag, ##__VA_ARGS__); \
                return err_rc_;                                    \
            }                                                      \
        } while (0)

#    define ON_ERROR_GOTO(x, goto_tag, log_tag, format, ...)       \
        do                                                         \
        {                                                          \
            esp_err_t err_rc_ = (x);                               \
            if (unlikely(err_rc_ != ESP_OK))                       \
            {                                                      \
                LOG_ERROR("[%s] " format, log_tag, ##__VA_ARGS__); \
                goto goto_tag;                                     \
            }                                                      \
        } while (0)

#    define ON_FALSE_RETURN(a, err_code, log_tag, format, ...)     \
        do                                                         \
        {                                                          \
            if (unlikely(!(a)))                                    \
            {                                                      \
                LOG_ERROR("[%s] " format, log_tag, ##__VA_ARGS__); \
                return err_code;                                   \
            }                                                      \
        } while (0)

#    define ON_FALSE_GOTO(a, err_code, goto_tag, log_tag, format, ...) \
        do                                                             \
        {                                                              \
            if (unlikely(!(a)))                                        \
            {                                                          \
                LOG_ERROR("[%s] " format, log_tag, ##__VA_ARGS__);     \
                goto goto_tag;                                         \
            }                                                          \
        } while (0)

#endif  // TARGET_ESP32

#ifdef TARGET_ESP8266

#    define LOG_INFO(tag, format, ...)
#    define LOG_WARNING(tag, format, ...)
#    define LOG_DEBUG(tag, format, ...)
#    define LOG_ERROR(tag, format, ...)
#    define LOG_FATAL(tag, format, ...)

#    define ON_ERROR_RETURN(x, log_tag, format, ...)               \
        do                                                         \
        {                                                          \
            esp_err_t err_rc_ = (x);                               \
            if (unlikely(err_rc_ != ESP_OK))                       \
            {                                                      \
                LOG_ERROR("[%s] " format, log_tag, ##__VA_ARGS__); \
                return err_rc_;                                    \
            }                                                      \
        } while (0)

#    define ON_ERROR_GOTO(x, goto_tag, log_tag, format, ...)       \
        do                                                         \
        {                                                          \
            esp_err_t err_rc_ = (x);                               \
            if (unlikely(err_rc_ != ESP_OK))                       \
            {                                                      \
                LOG_ERROR("[%s] " format, log_tag, ##__VA_ARGS__); \
                goto goto_tag;                                     \
            }                                                      \
        } while (0)

#    define ON_FALSE_RETURN(a, err_code, log_tag, format, ...)     \
        do                                                         \
        {                                                          \
            if (unlikely(!(a)))                                    \
            {                                                      \
                LOG_ERROR("[%s] " format, log_tag, ##__VA_ARGS__); \
                return err_code;                                   \
            }                                                      \
        } while (0)

#    define ON_FALSE_GOTO(a, err_code, goto_tag, log_tag, format, ...) \
        do                                                             \
        {                                                              \
            if (unlikely(!(a)))                                        \
            {                                                          \
                LOG_ERROR("[%s] " format, log_tag, ##__VA_ARGS__);     \
                goto goto_tag;                                         \
            }                                                          \
        } while (0)

#endif

#endif  // __RCORE_LOG_C_H__
