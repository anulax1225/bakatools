#include "dir_entry.h"

namespace Bk {
    std::string DirEntry::path()
    {
        return this->ent.path().string();
    }

    std::string DirEntry::absolute_path()
    {
        return std::filesystem::absolute(ent.path());
    }

    std::string DirEntry::relative_path()
    {
        return ent.path().relative_path().string();
    }

    std::string DirEntry::name()
    {
        return ent.path().filename();
    }

    uintmax_t DirEntry::size()
    {
        return ent.file_size();
    }

    TimePoint<Bk::FileClock, Bk::Second> DirEntry::last_write()
    {
        return TimePoint<Bk::FileClock, Bk::Second>(ent.last_write_time());
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

    bool DirEntry::move(std::string name)
    {
        std::filesystem::directory_entry new_path(ent.path().parent_path()/name);
        if (exists() && new_path.exists()) 
        {
            std::filesystem::rename(ent.path(), new_path.path()/name());
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