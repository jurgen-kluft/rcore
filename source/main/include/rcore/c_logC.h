#ifndef __RCORE_LOG_C_H__
#define __RCORE_LOG_C_H__

#include "esp32-hal-log.h"

#define LOG_INFO(tag, format, ...)    log_i("[%s] " format, tag, ##__VA_ARGS__)
#define LOG_WARNING(tag, format, ...) log_w("[%s] " format, tag, ##__VA_ARGS__)
#define LOG_DEBUG(tag, format, ...)   log_d("[%s] " format, tag, ##__VA_ARGS__)
#define LOG_ERROR(tag, format, ...)   log_e("[%s] " format, tag, ##__VA_ARGS__)
#define LOG_FATAL(tag, format, ...)   log_e("[%s] " format, tag, ##__VA_ARGS__)

#define ON_ERROR_RETURN(x, log_tag, format, ...)           \
    do                                                     \
    {                                                      \
        esp_err_t err_rc_ = (x);                           \
        if (unlikely(err_rc_ != ESP_OK))                   \
        {                                                  \
            log_e("[%s] " format, log_tag, ##__VA_ARGS__); \
            return err_rc_;                                \
        }                                                  \
    } while (0)

#define ON_ERROR_GOTO(x, goto_tag, log_tag, format, ...)   \
    do                                                     \
    {                                                      \
        esp_err_t err_rc_ = (x);                           \
        if (unlikely(err_rc_ != ESP_OK))                   \
        {                                                  \
            log_e("[%s] " format, log_tag, ##__VA_ARGS__); \
            goto goto_tag;                                 \
        }                                                  \
    } while (0)

#define ON_FALSE_RETURN(a, err_code, log_tag, format, ...) \
    do                                                     \
    {                                                      \
        if (unlikely(!(a)))                                \
        {                                                  \
            log_e("[%s] " format, log_tag, ##__VA_ARGS__); \
            return err_code;                               \
        }                                                  \
    } while (0)

#define ON_FALSE_GOTO(a, err_code, goto_tag, log_tag, format, ...) \
    do                                                             \
    {                                                              \
        if (unlikely(!(a)))                                        \
        {                                                          \
            log_e("[%s] " format, log_tag, ##__VA_ARGS__);         \
            goto goto_tag;                                         \
        }                                                          \
    } while (0)

#endif  // __RCORE_LOG_C_H__
