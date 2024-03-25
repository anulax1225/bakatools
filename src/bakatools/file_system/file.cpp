#include "file.h"

namespace Bk::Tools {
    int File::remove()
    {
        return std::filesystem::remove(ent.path());
    }

    void File::copy(std::string path, CopyOption opt)
    {
        if (exists()) std::filesystem::copy_file(ent.path(), path, opt);
    }
}