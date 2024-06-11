#include "directory.h"

namespace Bk {
    Directory Directory::create(std::string path)
    {
        std::filesystem::create_directory(path);
        return Directory(path);
    }

    std::string Directory::current()
    {
        return std::filesystem::current_path();
    }

    Directory Directory::remove()
    {
        std::filesystem::remove_all(ent.path());
        return Directory(path());
    }

    void Directory::copy(std::string path, CopyOption opt)
    {
        if (exists()) std::filesystem::copy(ent.path(), path, opt);
    }

    std::vector<DirEntry> Directory::entries()
    {
        std::vector<DirEntry> entries;
        for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(ent.path()))
            entries.push_back(DirEntry(entry));
        return entries;
    }

    std::vector<DirEntry> Directory::r_entries()
    {
        std::vector<DirEntry> entries;
        for (std::filesystem::directory_entry entry : std::filesystem::recursive_directory_iterator(ent.path()))
            entries.push_back(DirEntry(entry));
        return entries;
    }
}