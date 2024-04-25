#pragma once

#include <bakatoolspch.h>
#include "dir_entry.h"

namespace Bk {
    class Directory : public DirEntry
    {
        public:
            Directory(std::string path)
            : DirEntry(path) {}

            Directory(std::filesystem::directory_entry ent)
            : DirEntry(ent) {}

            virtual ~Directory() {}

            int remove() override;
            void copy(std::string path, CopyOption opt = CopyOption::recursive) override;

            std::vector<DirEntry> entries();
            std::vector<DirEntry> r_entries();

            template<typename E>
            std::vector<E> entries()
            {
                std::vector<E> entries;
                for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(ent.path()))
                    if (E::get_type() == entry.status().type()) entries.push_back(E(entry));
                return entries;
            }

            template<typename E>
            std::vector<E> r_entries()
            {
                std::vector<E> entries;
                for (std::filesystem::directory_entry entry : std::filesystem::recursive_directory_iterator(ent.path()))
                    if (E::get_type() == entry.status().type()) entries.push_back(E(entry));
                return entries;
            }

            static std::string current();

            BK_DIR_ENTRY_TYPE(directory)
    };
}