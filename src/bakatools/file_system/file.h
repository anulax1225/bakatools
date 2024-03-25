#pragma once

#include <bakatoolspch.h>
#include "dir_entry.h"

namespace Bk::Tools {
    class File : public DirEntry
    {
        public:
            File(std::string path)
            : DirEntry(path) 
            {}

            File(std::filesystem::directory_entry ent)
            : DirEntry(ent) {}

            virtual ~File() {}

            int remove() override;
            void copy(std::string path, CopyOption opt = CopyOption::overwrite_existing) override;

            BK_DIR_ENTRY_TYPE(regular)
    };
}