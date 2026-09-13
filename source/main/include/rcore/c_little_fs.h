#ifndef __RCORE_LITTLE_FS_H__
#define __RCORE_LITTLE_FS_H__
#include "rcore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

namespace ncore
{
    namespace nlittlefs
    {
        bool initialize();

        typedef bool (*scanner_handle_fn)(void* ctx, bool is_dir, void* user_ctx);
        void        scanner_scan(void* user_ctx, scanner_handle_fn handle_cb);
        const char* scanner_filename(void* ctx);
        bool        scanner_fileload(void* ctx, u8* destination, u32 capacity, u32& out_file_size);

        void file_save(const char* filename, const u8* source, u32 size);

    }  // namespace nlittlefs
}  // namespace ncore
#endif  // __RCORE_LITTLE_FS_H__
