#include "rcore/c_little_fs.h"

#include "Arduino.h"

#include "FS.h"
#include "LittleFS.h"

namespace ncore
{
    namespace nlittlefs
    {

        struct scan_context_t
        {
            i32       scan_stack_top      = 0;
            const i32 scan_stack_capacity = 8;
            File      scan_stack[8];
            File      current;
        };

        const char* scanner_filename(void* ctx)
        {
            scan_context_t* scan_ctx = (scan_context_t*)(ctx);
            return scan_ctx->current.name();
        }

        bool scanner_fileload(void* ctx, u8* destination, u32 capacity, u32& out_file_size)
        {
            scan_context_t* scan_ctx = (scan_context_t*)(ctx);
            File&           file     = scan_ctx->current;

            const u32 file_size = file.size();
            if (file_size > capacity)
                return false;
            file.read(destination, file_size);
            out_file_size = file_size;
            return true;
        }

        bool initialize()
        {
            if (!LittleFS.begin())
            {
                return false;
            }
            return true;
        }

        void scanner_scan(void* user_ctx, scanner_handle_fn handle_cb)
        {
            // Scan files for the availability of:
            // - sprite_pack.bin
            // - font_pack.bin
            // - palette_pack.bin
            // - script.bin

            const char* dirname   = "/";
            File        main_root = LittleFS.open(dirname);
            if (!main_root)
            {
                nlog::log_warning("LITTLE-FS", "Failed to open directory");
                return;
            }
            if (!main_root.isDirectory())
            {
                nlog::log_warning("LITTLE-FS", "Not a directory");
                return;
            }

            scan_context_t scanner;

            // Initialize the scan by opening the first file in the root directory and
            // adding it to the scan stack.
            scanner.scan_stack[scanner.scan_stack_top++] = main_root;

            while (scanner.scan_stack_top > 0)
            {
                scanner.scan_stack_top -= 1;

                File root       = scanner.scan_stack[scanner.scan_stack_top];
                scanner.current = root.openNextFile();
                while (scanner.current)
                {
                    if (scanner.current.isDirectory())
                    {
                        if (handle_cb(&scanner, true, user_ctx))
                        {
                            if (scanner.scan_stack_top < scanner.scan_stack_capacity)
                            {
                                scanner.scan_stack[scanner.scan_stack_top++] = scanner.current;
                            }
                        }
                    }
                    else
                    {
                        if (handle_cb(&scanner, false, user_ctx)) {
                            // Handle the file as needed
                        }

                        // if (nascii::compare(file.name(), "sprite_pack.bin") == 0)
                        // {
                        //     app_data->m_sprite_pack_size   = s_load_file(file, (u8*)app_data->m_sprite_pack, app_data->m_sprite_pack_capacity);
                        //     app_data->m_sprite_pack_source = EDATA_SOURCE_LITTLE_FS;
                        // }
                        // else if (nascii::compare(file.name(), "font_pack.bin") == 0)
                        // {
                        //     app_data->m_font_pack_size   = s_load_file(file, (u8*)app_data->m_font_pack, app_data->m_font_pack_capacity);
                        //     app_data->m_font_pack_source = EDATA_SOURCE_LITTLE_FS;
                        // }
                        // else if (nascii::compare(file.name(), "palette_pack.bin") == 0)
                        // {
                        //     app_data->m_palette_pack_size   = s_load_file(file, (u8*)app_data->m_palette_pack, app_data->m_palette_pack_capacity);
                        //     app_data->m_palette_pack_source = EDATA_SOURCE_LITTLE_FS;
                        // }
                        // else if (nascii::compare(file.name(), "script.bin") == 0)
                        // {
                        //     app_data->m_script_binary_size   = s_load_file(file, (u8*)app_data->m_script_binary, app_data->m_script_binary_capacity);
                        //     app_data->m_script_binary_source = EDATA_SOURCE_LITTLE_FS;
                        // }
                    }
                    scanner.current = root.openNextFile();  // Closes previous file automatically and moves forward
                }
            }
        }

        void file_save(const char* filename, const u8* source, u32 size)
        {
            const char* dirname   = "/";
            File        main_root = LittleFS.open(dirname);

            File file = main_root.open(filename, "w");
            if (file)
            {
                file.write(source, size);
                file.close();
            }
        }


    }  // namespace nlittlefs

}  // namespace ncore
