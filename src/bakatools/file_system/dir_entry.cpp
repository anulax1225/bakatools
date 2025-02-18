#include "dir_entry.h"
#ifdef BK_PLATFORM_LINUX
    #include <bits/chrono.h>
#endif
#include <chrono>

namespace Bk 
{
    std::string DirEntry::path()
    {
        return this->ent.path().string();
    }

    std::string DirEntry::absolute_path()
    {
        return std::filesystem::absolute(ent.path()).string();
    }

    std::string DirEntry::relative_path()
    {
        return ent.path().relative_path().string();
    }

    std::string DirEntry::name()
    {
        return ent.path().filename().string();
    }

    u64 DirEntry::size()
    {
        return ent.file_size();
    }

    std::filesystem::file_time_type DirEntry::last_write()
    {
        return ent.last_write_time();
    }

    bool DirEntry::exists()
    {
        return ent.exists();
    }

    bool DirEntry::is(FileType type)
    {
        return this->type() == type;
    }

    FileType DirEntry::type()
    {
        return ent.status().type();
    }

    FilePerms DirEntry::perms()
    {
        return ent.status().permissions();
    }

    uintmax_t DirEntry::hard_links()
    {
        return ent.hard_link_count();
    }

    bool DirEntry::move(std::string path)
    {
        std::filesystem::directory_entry new_path(path);
        if (exists() && new_path.exists()) 
        {
            std::filesystem::rename(ent.path(), new_path.path());
            ent = std::filesystem::directory_entry(new_path.path());
            return true;
        }
        return false;
    }

    bool DirEntry::rename(std::string name)
    {
        if (exists()) 
        {
            std::filesystem::path new_path = ent.path().parent_path()/name;
            std::filesystem::rename(ent.path(), new_path);
            ent = std::filesystem::directory_entry(new_path);
            return true;
        }
        return false;
    }
}