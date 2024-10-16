#pragma once

#include <bakatoolspch.h>
#include <bits/chrono.h>
#include <chrono>

namespace Bk 
{
    #define BK_DIR_ENTRY_TYPE(type) const char* type_name() override { return BK_STRINGIFY(type); }\
                                    static FileType get_type() { return FileType::type; }

    using FileType = std::filesystem::file_type;
    using FilePerms = std::filesystem::perms;
    using FileStatus = std::filesystem::file_status;
    using CopyOption = std::filesystem::copy_options;

    class DirEntry 
    {
        public:
            DirEntry(std::string path)
            {
                std::filesystem::path p(path);
                ent = std::filesystem::directory_entry(p);
            }

            DirEntry(std::filesystem::directory_entry ent)
            : ent(ent) {}

            virtual ~DirEntry() {}
            
            std::string path();
            std::string absolute_path();
            std::string relative_path();
            std::string name();

            uintmax_t size();
            std::chrono::time_point<std::filesystem::__file_clock> last_write();
            bool exists();
            FilePerms perms();
            uintmax_t hard_links();
            
            bool move(std::string path);
            bool rename(std::string name);
            virtual void copy(std::string path, CopyOption opt) {}


            virtual const char* type_name() { return "dir_entry"; }
            FileType type();
            bool is(FileType type);
            static FileType get_type() { return FileType::unknown; }

        protected:
            std::filesystem::directory_entry ent;
    };
}