#pragma once

#include <bakatoolspch.h>
#include <bakatools/container/data_stream.h>
#include "dir_entry.h"

namespace Bk {
    class File : public DirEntry
    {
        public:
            File(std::string path)
            : DirEntry(path) 
            {}

            File(std::filesystem::directory_entry ent)
            : DirEntry(ent) {}

            virtual ~File() {}

            int remove();
            void copy(std::string path, CopyOption opt = CopyOption::overwrite_existing) override;

            Type::DataStream read(u64 size = 0);
            bool write(Type::DataStream stream);

            BK_DIR_ENTRY_TYPE(regular)
    };
}